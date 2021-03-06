#include "cpu/exec/template-start.h"

#define instr jmp
static void do_execute()
{
	if (ops_decoded.opcode == 0xff)
	{
		cpu.eip = op_src->val;
	}
	else
		cpu.eip += (int32_t)((DATA_TYPE_S)op_src->val);
	if (DATA_BYTE == 2)
		cpu.eip &= 0x0000ffff;
	print_asm_template1();
}
make_instr_helper(i)
//make_instr_helper(rm)
/*
make_helper(concat(jmp_i_, SUFFIX)) {
	concat(decode_i_, SUFFIX)(eip + 1);
	cpu.eip += op_src->val;
	if (DATA_BYTE == 2)
		cpu.eip &= 0x0000ffff;
	print_asm_template1();
	return 0;
}
*/
make_helper(concat(jmp_rm_, SUFFIX)) {
	concat(decode_rm_, SUFFIX)(eip + 1);
	cpu.eip = op_src->val;
	if (DATA_BYTE == 2)
		cpu.eip &= 0x0000ffff;
	print_asm_template1();
	return 0;
}
#include "cpu/exec/template-end.h"
