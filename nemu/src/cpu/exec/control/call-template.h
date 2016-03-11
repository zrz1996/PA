#include "cpu/exec/template-start.h"

#define instr call

static void do_execute()
{
	reg_l(R_ESP) -= DATA_BYTE;
	MEM_W(reg_l(R_ESP), cpu.eip + DATA_BYTE + 1, 2);
	cpu.eip += op_src->val;
	#if DATA_BYTE == 2
		cpu.eip &= 0x0000ffff;
	#endif
	print_asm_template1();
}
make_instr_helper(i)

make_helper(concat(call_rm_, SUFFIX)) {
	int len = concat(decode_rm_, SUFFIX)(eip + 1);
	reg_l(R_ESP) -= DATA_BYTE;
	MEM_W(reg_l(R_ESP), cpu.eip + len + 1, 2);
	cpu.eip = op_src->val - len - 1;
	#if DATA_BYTE == 2
		cpu.eip &= 0x0000ffff;
	#endif
	print_asm_template1();
	return len + 1;
}

#include "cpu/exec/template-end.h"
