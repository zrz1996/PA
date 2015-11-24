#include "cpu/exec/template-start.h"
#include "../alu.h"
#define instr cmp
static void do_execute () {
	cpu.cf = 0;
	alu(op_dest->val, op_src->val, 1, 1);
	print_asm_template2();
}

make_instr_helper(i2rm)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(si2rm)
#endif
make_instr_helper(r2rm)
make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"