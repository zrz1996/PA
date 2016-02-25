#include "cpu/exec/template-start.h"

#define instr and

static void do_execute () {
	//op_src->val = signExtend(op_src->val, 1);
	DATA_TYPE result = op_dest->val & op_src->val;
	OPERAND_W(op_dest, result);
	cpu.cf = 0;
	alu(result, 0, 1, 0);
	snprintf(op_src->str, OP_STR_SIZE, "$0x%x", op_src->val);
	print_asm_template2();
}

make_instr_helper(i2a)
make_instr_helper(i2rm)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(si2rm)
#endif
make_instr_helper(r2rm)
make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
