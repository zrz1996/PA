#include "cpu/exec/template-start.h"

#define instr movsx

static void do_execute() {
	if (ops_decoded.opcode == 0x1be)
	{
		if (DATA_BYTE == 2)
		{
			if (op_src->type == 0)
				OPERAND_W(op_dest, (int16_t)((int8_t)reg_b(op_src->reg)));
			else
				OPERAND_W(op_dest, (int16_t)((int8_t)op_src->val));
		}
		else
		{
			if (op_src->type == 0)
				OPERAND_W(op_dest, (int32_t)((int8_t)reg_b(op_src->reg)));
			else
				OPERAND_W(op_dest, (int32_t)((int8_t)op_src->val));
		}
	}
	else
	{
		if (op_src->type == 0)
			OPERAND_W(op_dest, (int32_t)((int16_t)reg_w(op_src->reg)));
		else
			OPERAND_W(op_dest, (int32_t)((int16_t)op_src->val));
	}
	print_asm_template2();
}

make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
