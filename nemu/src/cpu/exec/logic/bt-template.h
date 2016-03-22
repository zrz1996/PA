#include "cpu/exec/template-start.h"
#define instr bt

static void do_execute () {
	if (op_dest->type == OP_TYPE_REG)
	{
		uint32_t offset = op_src->val % (DATA_BYTE * 8);
		cpu.cf = (op_dest->val >> offset) & 1;
	}
	else
	{
		uint32_t addr = op_src->val / (DATA_BYTE * 8) + op_dest->addr;
		uint32_t offset = op_src->val % (DATA_BYTE * 8);
		cpu.cf = (swaddr_read(addr, DATA_BYTE, op_dest->sreg) >> offset) & 1;
	}
	print_asm_template2();
}

make_instr_helper(r2rm)

/*
make_helper(bt_i2rm)
{
	uint32_t len, sz;
	if (ops_decoded.is_data_size_16)
	{
   		len = decode_rm_w(eip + 1);
		sz = 2;
	}
	else
	{
		len = decode_rm_l(eip + 1);
		sz = 4;
	}
	uint32_t offset = swaddr_read(eip + len + 1, 1, 1);
	if (op_src->type == OP_TYPE_REG)
	{
		offset = offset % (sz * 8);
		cpu.cf = (op_src->val >> offset) & 1;
	}
	else
	{
		uint32_t addr = offset / (sz * 8) + op_src->addr;
		offset = op_src->val % (sz * 8);
		cpu.cf = swaddr_read(addr, sz, op_src->sreg);
	}
	return len + 2;
}
*/

#include "cpu/exec/template-end.h"
