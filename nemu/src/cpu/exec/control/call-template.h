#include "cpu/exec/template-start.h"

#define instr call

static void do_execute()
{
	REG(R_ESP) -= DATA_BYTE;
	MEM_W(REG(R_ESP), cpu.eip + DATA_BYTE + 1);
	cpu.eip += op_src->val;
	#if DATA_BYTE == 2
		cpu.eip &= 0x0000ffff;
	#endif
	print_asm_template1();
}
make_instr_helper(i)
#include "cpu/exec/template-end.h"
