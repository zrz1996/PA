#include "cpu/exec/template-start.h"

#define instr jmp

static void do_execute()
{
	if (ops_decoded.opcode == 0xff)
	{
		printf("%d\n", op_src->val);
		cpu.eip = swaddr_read(op_src->val, 4);
		if (DATA_BYTE == 2)
			cpu.eip &= 0x0000ffff;
	}
	else
	{
		cpu.eip += op_src->val;
		if (DATA_BYTE == 2)
			cpu.eip &= 0x0000ffff;
	}
	print_asm_template1();
}
make_instr_helper(i)
make_instr_helper(rm)
#include "cpu/exec/template-end.h"
