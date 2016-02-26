#include "cpu/exec/template-start.h"

#define instr shld

#if DATA_BYTE == 2 || DATA_BYTE == 4
static void do_execute () {
	DATA_TYPE in = op_dest->val;
	DATA_TYPE out = op_src2->val;

	uint8_t count = op_src->val;
	count &= 0x1f;
	/*
	while(count != 0) {
		out <<= 1;
		out |= (in & 1) << ((DATA_BYTE << 3) - 1);
		in <<= 1;
		count --;
	}
	*/
	int size = DATA_BYTE << 3;
	int i;
	for (i = size - 1; i >= count; i--)
	{

		uint32_t temp = ((out >> (i - count)) & 1) << i;
		out |= temp;
		out &= temp;
	}
	for (i = count - 1; i >= 0; i--)
	{
		uint32_t temp = (in >> (i - count + size) & 1) << i;
		out |= temp;
		out &= temp;
	}
	OPERAND_W(op_src2, out);
	printf("%x\n", op_src2->val);
	print_asm("shld" str(SUFFIX) " %s,%s,%s", op_src->str, op_dest->str, op_src2->str);
}


make_helper(concat(shld_i_, SUFFIX)) {
	int len = concat(decode_si_rm2r_, SUFFIX) (eip + 1);  /* use decode_si_rm2r to read 1 byte immediate */
	op_dest->val = REG(op_dest->reg);
	do_execute();
	return len + 1;
}

make_helper(concat(shld_r2rm_cl_, SUFFIX)) {
	int len = concat(decode_rm2r_, SUFFIX)(eip + 1);
	*(op_src2) = *(op_src);
	op_src->type = OP_TYPE_REG;
	op_src->reg = R_CL;
	op_src->val = reg_b(R_CL);
#ifdef DEBUG
	sprintf(op_src->str, "%%cl");
#endif
	do_execute();
	return len + 1;
}
#endif

#include "cpu/exec/template-end.h"
