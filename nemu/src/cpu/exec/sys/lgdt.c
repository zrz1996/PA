#include "cpu/exec/helper.h"

make_helper(lgdt) {
	int i;
	for (i = 0; i < 6; i++)
		printf("%x ", instr_fetch(eip + 1 + i, 1));
	printf("\n");
	uint16_t limit = instr_fetch(eip + 1, 2);
	uint32_t base = instr_fetch(eip + 3, 4);
	cpu.gdtr = (((uint64_t)base) << 16) | limit;
	print_asm("lgdt");
	return 7;
}

