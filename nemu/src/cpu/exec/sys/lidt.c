#include "cpu/exec/helper.h"

make_helper(lidt) {
	uint32_t len = decode_rm_l(eip + 1);
	uint32_t addr = op_src->addr;
	uint16_t limit = lnaddr_read(addr, 2);
	uint32_t base = lnaddr_read(addr + 2, 4);
	cpu.idtr = (((uint64_t)base) << 16) | limit;
	print_asm("lidt" " 0x%x", addr);
	return len + 1;
}

