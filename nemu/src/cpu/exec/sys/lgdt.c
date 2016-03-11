#include "cpu/exec/helper.h"

make_helper(lgdt) {
	uint32_t len = decode_rm_l(eip + 1);
	uint32_t addr = op_src->val;
	printf("%x\n", addr);
	uint16_t limit = lnaddr_read(addr, 2);
	uint32_t base = lnaddr_read(addr + 2, 4);
	cpu.gdtr = (((uint64_t)base) << 16) | limit;
	print_asm("lgdt" " 0x%x", base);
	return len + 1;
}

