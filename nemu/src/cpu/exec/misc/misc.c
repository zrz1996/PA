#include "cpu/exec/helper.h"
#include "cpu/decode/modrm.h"
#include "../../lib-common/x86-inc/mmu.h"
make_helper(nop) {
	print_asm("nop");
	return 1;
}

make_helper(int3) {
	void do_int3();
	do_int3();
	print_asm("int3");

	return 1;
}

make_helper(lea) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	int len = load_addr(eip + 1, &m, op_src);
	reg_l(m.reg) = op_src->addr;

	print_asm("leal %s,%%%s", op_src->str, regsl[m.reg]);
	return 1 + len;
}
make_helper(clc) {
	cpu.cf = 0;
	print_asm("clc");
	return 1;
}
make_helper(cli) {
	cpu._if_ = 0;
	print_asm("clc");
	return 1;
}
make_helper(stc) {
	cpu.cf = 1;
	print_asm("stc");
	return 1;
}

make_helper(int_i) {
	void raise_intr(uint8_t NO);
	uint8_t no = instr_fetch(eip + 1, 1);
	cpu.eip += 2;
	raise_intr(no);
	printf("%x\n", cpu.eip);
	print_asm("int 0x%x", no);
	return 0;
}

make_helper(iret) {
	cpu.eip = swaddr_read(cpu.esp, 4, 2);
	cpu.esp += 4;
	cpu.cs = (uint16_t)swaddr_read(cpu.esp, 4, 2);
	cpu.esp += 4;
	cpu.eflags = swaddr_read(cpu.esp, 4, 2);
	cpu.esp += 4;
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
	if (temp.SD.granularity)
		cpu.seglimit[1] <<= 12;
	print_asm("iret");
	return 1;
}
