#include "cpu/exec/template-start.h"
#include "../alu.h"

#define instr neg

static void do_execute() {
	cpu.cf = 0;
	DATA_TYPE result = alu(0, op_src->val, 1, 1);
	OPERAND_W(op_src, result);
	print_asm_template1();
}

make_instr_helper(rm)

#include "cpu/exec/template-end.h"
