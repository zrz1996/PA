#include "cpu/exec/template-start.h"
#include "../alu.h"
#define instr add
static void do_execute () {
	cpu.cf = 0;
	DATA_TYPE result = alu(op_dest->val, op_src->val, 1, 0);
	OPERAND_W(op_dest, result);
	print_asm_template2();
}

make_instr_helper(i2rm)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(si2rm)
#endif
make_instr_helper(r2rm)
make_instr_helper(rm2r)

make_helper(concat(add_i2a_, SUFFIX)) {
	concat(decode_i_, SUFFIX)(eip + 1);
	op_dest->type = OP_TYPE_REG;
	op_dest->reg = R_EAX;
	op_dest->val = REG(R_EAX);
	snprintf(op_dest->str, OP_STR_SIZE, "%%%s", REG_NAME(R_EAX));
	do_execute();
	return 2;
}
#include "cpu/exec/template-end.h"
