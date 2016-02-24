#include "cpu/exec/template-start.h"

#define instr pop

static void do_execute()
{
	DATA_TYPE temp = swaddr_read(reg_l(R_ESP), DATA_BYTE);
	OPERAND_W(op_src, temp);
	reg_l(R_ESP) += DATA_BYTE;
	print_asm_template1();
}
make_instr_helper(r)
make_instr_helper(rm)
#include "cpu/exec/template-end.h"
