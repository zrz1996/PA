#include "cpu/exec/helper.h"

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
	reg_l(op_src->reg) = cpu.cr0;
	print_asm("mov" " CR0,%%%s", op_src->str);
	return len + 1;
}

make_helper(mov_r2c)
{
	printf("$$$$\n");
	uint32_t len = decode_rm_l(eip + 1);
	cpu.cr0 = reg_l(op_src->reg);
	print_asm("mov" " %%%s,CR0", op_src->str);
	return len + 1;
}
