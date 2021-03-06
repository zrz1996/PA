#include "cpu/exec/template-start.h"
#define instr test

static void do_execute () {
	//DATA_TYPE result = alu(op_dest->val, op_src->val, 0, 1);
	//OPERAND_W(op_dest, result);
	alu(op_dest->val, op_src->val, 0, 1);
	cpu.cf = cpu.of = 0;
	print_asm_template2();
}

make_instr_helper(r2rm)
make_instr_helper(i2rm)
make_instr_helper(i2a)

#include "cpu/exec/template-end.h"
