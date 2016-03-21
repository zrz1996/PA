#include "monitor/monitor.h"
#include "monitor/watchpoint.h"
#include "cpu/helper.h"
#include <setjmp.h>
#include "device/i8259.h"

/* The assembly code of instructions executed is only output to the screen
 * when the number of instructions executed is less than this value.
 * This is useful when you use the ``si'' command.
 * You can modify this value as you want.
 */
#define MAX_INSTR_TO_PRINT 10

int nemu_state = STOP;

int exec(swaddr_t);

char assembly[80];
char asm_buf[128];

/* Used with exception handling. */
jmp_buf jbuf;

void print_bin_instr(swaddr_t eip, int len, uint32_t base) {
	int i;
	int l = sprintf(asm_buf, "%8x:   ", eip);
	for(i = 0; i < len; i ++) {
		l += sprintf(asm_buf + l, "%02x ", lnaddr_read(eip + i + base, 1));
	}
	sprintf(asm_buf + l, "%*.s", 50 - (12 + 3 * len), "");
}

/* This function will be called when an `int3' instruction is being executed. */
void do_int3() {
	printf("\nHit breakpoint at eip = 0x%08x\n", cpu.eip);
	nemu_state = STOP;
}

void raise_intr(uint8_t NO);
/* Simulate how the CPU works. */
void cpu_exec(volatile uint32_t n) {
	if(nemu_state == END) {
		printf("Program execution has ended. To restart the program, exit NEMU and run again.\n");
		return;
	}
	nemu_state = RUNNING;

#ifdef DEBUG
	volatile uint32_t n_temp = n;
#endif

	setjmp(jbuf);

	for(; n > 0; n --) {
#ifdef DEBUG
		swaddr_t eip_temp = cpu.eip;
		uint32_t base = (cpu.cr0.protect_enable) * cpu.segbase[1];
		if((n & 0xffff) == 0) {
			/* Output some dots while executing the program. */
			fputc('.', stderr);
		}
#endif

		/* Execute one instruction, including instruction fetch,
		 * instruction decode, and the actual execution. */
		int instr_len = exec(cpu.eip);
		cpu.eip += instr_len;
		if (cpu.eip == 0x80480a0)
			printf("E####");
#ifdef DEBUG
		print_bin_instr(eip_temp, instr_len, base);
		strcat(asm_buf, assembly);
		Log_write("%s\n", asm_buf);
		if(n_temp < MAX_INSTR_TO_PRINT) {
			printf("%s\n", asm_buf);
		}
#endif
		if (check_wp())
		{
			nemu_state = STOP;
			print_wp();
		}

		if(nemu_state != RUNNING) { return; }
#ifdef HAS_DEVICE
		if(cpu.INTR & cpu._if_) {
			uint32_t intr_no = i8259_query_intr();
			i8259_ack_intr();
			raise_intr(intr_no);
		}
#endif
	}

	if(nemu_state == RUNNING) { nemu_state = STOP; }
}
