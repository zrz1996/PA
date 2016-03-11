#include "cpu/exec/helper.h"
#include "nemu.h"
#include "../../lib-common/x86-inc/mmu.h"

#define DATA_BYTE 1
#include "mov-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "mov-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "mov-template.h"
#undef DATA_BYTE

/* for instruction encoding overloading */

make_helper_v(mov_i2r)
make_helper_v(mov_i2rm)
make_helper_v(mov_r2rm)
make_helper_v(mov_rm2r)
make_helper_v(mov_a2moffs)
make_helper_v(mov_moffs2a)

make_helper(mov_c2r)
{
	uint32_t len = decode_rm_l(eip + 1);
	reg_l(op_src->reg) = cpu.cr0.val;
	print_asm("mov" " CR0,%s", op_src->str);
	return len + 1;
}

make_helper(mov_r2c)
{
	uint32_t len = decode_rm_l(eip + 1);
	cpu.cr0.val = reg_l(op_src->reg);
	print_asm("mov" " %s,CR0", op_src->str);
	return len + 1;
}
make_helper(mov_rm2sr)
{
	uint8_t modrm = instr_fetch(eip + 1, 1);
	uint8_t rn = modrm & 0x7;
	uint8_t sn = (modrm >> 3) & 0x3;
	cpu.segreg[sn] = reg_w(rn);
	uint32_t gdt_addr = cpu.gdtr >> 16;
	uint32_t index = (cpu.cs >> 3) << 3;
	gdt_addr += index;
	union {
		uint64_t gdt;
		SegDesc SD;
	}temp;
	temp.gdt = ((uint64_t)lnaddr_read(gdt_addr + 4, 4) << 32) | lnaddr_read(gdt_addr, 4);
	cpu.segbase[sn] = (temp.SD.base_31_24 << 24) + (temp.SD.base_23_16 << 16) + (temp.SD.base_15_0);
	cpu.seglimit[sn] = (temp.SD.limit_19_16 << 16) + temp.SD.limit_15_0;
	print_asm("mov" " %s,%s", regsw[rn], segname[sn]);
	return 2;
}
