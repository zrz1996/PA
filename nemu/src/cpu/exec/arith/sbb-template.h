#include "cpu/exec/template-start.h"
#include "../alu.h"
#define instr sbb
static void do_execute () {
	DATA_TYPE result = alu(op_src->val, cpu.cf, 1, 0);
	cpu.cf = 0;
	result = alu(op_dest->val, result, 1, 1);
	OPERAND_W(op_dest, result);
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
