#include "cpu/exec/helper.h"

make_helper(lgdt) {
	uint16_t limit = instr_fetch(eip, 2);
	uint32_t base = instr_fetch(eip + 2, 4);
	cpu.gdtr = (((uint64_t)base) << 16) | limit;
	print_asm("lgdt" " 0x%x", base);
	return 6;
}

