#include "cpu/exec/template-start.h"

#define instr jbe
static void do_execute()
{
	if (cpu.cf == 1 && cpu.zf == 1)
		cpu.eip += op_src->val;
	printf("%d %d\n", cpu.eip, op_src->val);
	print_asm_template1();
}
make_instr_helper(i)
#include "cpu/exec/template-end.h"
