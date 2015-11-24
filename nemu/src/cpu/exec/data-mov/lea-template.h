#include "cpu/exec/template-start.h"

#define instr lea

static void do_execute() {
	uint32_t tmp = MEM_R(op_src->val);
	#if DATA_BYTE == 2
		tmp &= 0xffff;
	#endif
	OPERAND_W(op_dest, tmp);
	print_asm_template2();
}

make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
