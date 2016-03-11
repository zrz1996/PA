#include "cpu/exec/template-start.h"

#define instr push

static void do_execute()
{
	if (DATA_BYTE == 2)
		reg_l(R_ESP) -= 2;
	else
		reg_l(R_ESP) -= 4;
	swaddr_write(reg_l(R_ESP), DATA_BYTE == 2 ? 2 : 4, op_src->val, 2);
	print_asm_template1();
}
make_instr_helper(r)
make_instr_helper(rm)
make_instr_helper(i)
#include "cpu/exec/template-end.h"
