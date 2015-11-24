#include "cpu/exec/template-start.h"

#define instr jbe
static void do_execute()
{
	if (cpu.cf == 1 || cpu.zf == 1)
	{
		int tmp = op_src->val;
		#if DATA_BYTE == 1
			tmp = (int32_t)((int8_t)tmp);
		#endif
		cpu.eip += tmp;
	}
	print_asm_template1();
}
make_instr_helper(i)
#include "cpu/exec/template-end.h"
