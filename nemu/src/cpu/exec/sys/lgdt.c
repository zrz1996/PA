#include "cpu/exec/helper.h"

make_helper(lgdt) {
	uint16_t limit = instr_fetch(eip + 1, 2);
	uint32_t base = instr_fetch(eip + 3, 4);
	printf("%x %x\n", base , limit);
	cpu.gdtr = (((uint64_t)base) << 16) | limit;
	print_asm("lgdt");
	return 7;
}

