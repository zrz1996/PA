#include "cpu/exec/helper.h"

make_helper(lgdt) {
	uint32_t limit = lnaddr_read(eip + 1, 2);
	uint32_t base = lnaddr_read(eip + 3, 4);
	printf("%x %x\n", base , limit);
	cpu.gdtr = (((uint64_t)base) << 16) | limit;
	print_asm("lgdt");
	return 7;
}

