#include "cpu/exec/helper.h"

/*
#define DATA_BYTE 4
#include "ret-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "ret-template.h"
#undef DATA_BYTE
*/

make_helper(ret) {
	cpu.eip = swaddr_read(reg_l(R_ESP), 4) - 1;
	reg_l(R_ESP) += 4;
	print_asm("ret");
	return 1;
}

make_helper(ret_i_w) {
	decode_i_w(cpu.eip + 1);
	cpu.eip = swaddr_read(reg_l(R_ESP), 4) - 3;
	reg_l(R_ESP) += 4 + op_src->val;
	print_asm("ret %s", op_src->str);
	return 3;
}

