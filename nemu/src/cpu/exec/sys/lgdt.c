#include "cpu/exec/helper.h"

make_helper(lgdt) {
	uint32_t limit = decode_i_w(eip + 1);
	uint32_t base = decode_i_l(eip + 3);
	cpu.gdtr = (((uint64_t)base) << 16) | limit;
	print_asm("lgdt");
	return 7;
}

