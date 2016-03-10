#include "cpu/exec/helper.h"

make_helper(lgdt) {
	uint32_t len = decode_i_l(cpu.eip + 1);
	uint32_t addr = op_src->val;
	uint32_t limit = swaddr_read(addr, 2);
	uint32_t base = swaddr_read(addr + 2, 4);
	cpu.gdtr = ((uint64_t)base << 16) | limit;
	print_asm("lgdt");
	return len + 1;
}

