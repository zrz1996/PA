#include "cpu/exec/template-start.h"
#include "../alu.h"
#define instr je
static void do_execute()
{
	if (cpu.zf == 1)
		cpu.eip += signExtend(op_src->val, DATA_BYTE);
	print_asm_template1();
}
make_instr_helper(i)
#undef instr

#define instr jbe
static void do_execute()
{
	if (cpu.zf == 1 || cpu.cf == 1)
		cpu.eip += signExtend(op_src->val, DATA_BYTE);
	print_asm_template1();
}
make_instr_helper(i)
#undef instr
#include "cpu/exec/template-end.h"
