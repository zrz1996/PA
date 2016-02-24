#include "cpu/exec/template-start.h"
#include "../alu.h"
#define instr cmp
static void do_execute () {
	DATA_TYPE result = op_src->val;
	if (ops_decoded.opcode == 0x83)
	{
		if (DATA_BYTE == 2)
			result = (int16_t)((int8_t)op_src->val);
		else
			result = (int32_t)((int8_t)op_src->val);
	}
	cpu.cf = 0;
	alu(op_dest->val, result, 1, 1);
	print_asm_template2();
}

make_instr_helper(i2rm)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(si2rm)
#endif
make_instr_helper(r2rm)
make_instr_helper(rm2r)

make_helper(concat(cmp_i2a_, SUFFIX)) {
	concat(decode_i_, SUFFIX)(eip + 1);
	op_dest->type = OP_TYPE_REG;
	op_dest->reg = R_EAX;
	op_dest->val = REG(R_EAX);
	snprintf(op_dest->str, OP_STR_SIZE, "%%%s", REG_NAME(R_EAX));
	do_execute();
	return 2;
}

#include "cpu/exec/template-end.h"
