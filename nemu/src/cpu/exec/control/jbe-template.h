#include "cpu/exec/template-start.h"
#include "../alu.h"
#define instr jbe
static void do_execute()
{
	if (cpu.cf == 1 || cpu.zf == 1)
	{
		cpu.eip += signExtend(op_src->val, DATA_BYTE);
	}
	print_asm_template1();
}
make_instr_helper(i)
#include "cpu/exec/template-end.h"
