#include "cpu/exec/template-start.h"

#define instr movsx

static void do_execute() {
	if (ops_decoded.opcode == 0xbe)
	{
		if (DATA_BYTE == 2)
			OPERAND_W(op_dest, (int16_t)((int8_t)op_src->val));
		else
			OPERAND_W(op_dest, (int32_t)((int8_t)op_src->val));
	}
	else
		OPERAND_W(op_dest, (int32_t)((int16_t)op_src->val));
	print_asm_template2();
}

make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
