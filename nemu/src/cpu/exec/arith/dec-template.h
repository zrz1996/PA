#include "cpu/exec/template-start.h"

#define instr dec

static void do_execute () {
	cpu.cf = 0;
	DATA_TYPE result = alu(op_src->val, 1, 1, 1);
	OPERAND_W(op_src, result);
	print_asm_template1();
}

make_instr_helper(rm)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(r)
#endif

#include "cpu/exec/template-end.h"
