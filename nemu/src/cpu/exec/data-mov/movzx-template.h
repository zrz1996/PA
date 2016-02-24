#include "cpu/exec/template-start.h"

#define instr movzx

static void do_execute() {
	if (ops_decoded.opcode == 0xb6)
	{
		if (DATA_BYTE == 2)
			OPERAND_W(op_dest, (uint16_t)((uint8_t)op_src->val));
		else
			OPERAND_W(op_dest, (uint32_t)((uint8_t)op_src->val));
	}
	else
		OPERAND_W(op_dest, (uint32_t)((uint16_t)op_src->val));
	print_asm_template2();
}

make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
