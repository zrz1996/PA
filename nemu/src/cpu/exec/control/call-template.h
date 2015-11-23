#include "cpu/exec/template-start.h"

#define instr call

static void do_execute()
{
	REG(R_ESP) -= DATA_BYTE;
	MEM_W(REG(R_ESP), cpu.eip);
	cpu.eip += op_src->val;
	print_asm_template1();
}
make_instr_helper(i)
#include "cpu/exec/template-end.h"
