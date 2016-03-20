#include "common.h"
#include "nemu.h"
#include "../../lib-common/x86-inc/mmu.h"
#include <setjmp.h>
extern jmp_buf jbuf;
void raise_intr(uint8_t NO) {
	lnaddr_t idt_address = (cpu.idtr >> 16) + (NO << 3);
	uint64_t idt = ((uint64_t)lnaddr_read(idt_address + 4, 4) << 32) | lnaddr_read(idt_address, 4);
	assert((idt >> 47) & 1);
	/* push eflags, cs, eip */
	reg_l(R_ESP) -= 4;
	swaddr_write(reg_l(R_ESP), 4, cpu.eflags, 2);
	reg_l(R_ESP) -= 4;
	swaddr_write(reg_l(R_ESP), 4, cpu.cs, 2);
	reg_l(R_ESP) -= 4;
	swaddr_write(reg_l(R_ESP), 4, cpu.eip, 2);
	/* change cs */
	cpu.cs = (idt >> 16) & 0xffff;
	/* update cs buffer */
	uint32_t gdt_addr = cpu.gdtr >> 16;
	uint32_t index = (cpu.cs >> 3) << 3;
	gdt_addr += index;
	union {
	    uint64_t gdt;
	    SegDesc SD;
	}temp;
	temp.gdt = ((uint64_t)lnaddr_read(gdt_addr + 4, 4) << 32) | lnaddr_read(gdt_addr, 4);
	cpu.segbase[1] = (temp.SD.base_31_24 << 24) + (temp.SD.base_23_16 << 16) + (temp.SD.base_15_0);
	cpu.seglimit[1] = (temp.SD.limit_19_16 << 16) + temp.SD.limit_15_0;
	/* change eip */
	cpu.eip = (idt & 0xffff) | ((idt >> 32LL) & 0xffff0000);
	/* Jump back to cpu_exec() */
	longjmp(jbuf, 1);
}
