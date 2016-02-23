#include "cpu/exec/template-start.h"

#define instr push

static void do_execute()
{
	if (DATA_BYTE == 2)
		REG(R_ESP) -= 2;
	else
	{
		REG(R_ESP) -= 4;
		printf("%x\n", REG(R_ESP));
	}
	printf("%x %x\n", REG(R_ESP), op_src->val);
	MEM_W(REG(R_ESP), op_src->val);
	printf("%x\n", REG(R_ESP));
	print_asm_template1();
}
make_instr_helper(r)
make_instr_helper(rm)
make_instr_helper(i)
#include "cpu/exec/template-end.h"
