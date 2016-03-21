#include "cpu/exec/helper.h"
uint32_t pio_read(ioaddr_t addr, size_t len);
void pio_write(ioaddr_t addr, size_t len, uint32_t data);
make_helper(in_i2a) {
	uint32_t len = decode_i_b(eip + 1);
	if (ops_decoded.opcode == 0xe4)
	{
		reg_b(R_EAX) = pio_read(op_src->val, 1);
		print_asm("in" " (0x%x),%%al", op_src->val);
	}
	else
	{
		if (ops_decoded.is_data_size_16)
		{
			reg_w(R_EAX) = pio_read(op_src->val, 2);
			print_asm("in" " (0x%x),%%ax", op_src->val);
		}
		else
		{
			reg_l(R_EAX) = pio_read(op_src->val, 4);
			print_asm("in" " (0x%x),%%eax", op_src->val);
		}
	}
	return len + 1;
}
make_helper(in_d2a) {
	if (ops_decoded.opcode == 0xec)
	{
		reg_b(R_EAX) = pio_read(reg_w(R_DX), 1);
		print_asm("in" " (%%dx),%%al");
	}
	else
	{
		if (ops_decoded.is_data_size_16)
		{
			reg_w(R_EAX) = pio_read(reg_w(R_DX), 2);
			print_asm("in" " (%%dx),%%ax");
		}
		else
		{
			reg_l(R_EAX) = pio_read(reg_w(R_DX), 4);
			print_asm("in" " (%%dx),%%eax");
		}
	}
	return 1;
}
