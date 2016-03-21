#include "cpu/exec/helper.h"
void pio_write(ioaddr_t addr, size_t len, uint32_t data);
make_helper(out_a2i) {
	uint32_t len = decode_i_b(eip + 1);
	if (ops_decoded.opcode == 0xe6)
	{
		pio_write(op_src->val, 1, reg_b(R_EAX));
		print_asm("out" " %%al,(0x%x)", op_src->val);
	}
	else
	{
		if (ops_decoded.is_data_size_16)
		{
			pio_write(op_src->val, 2, reg_w(R_EAX));
			print_asm("out" " %%ax,(0x%x)", op_src->val);
		}
		else
		{
			pio_write(op_src->val, 4, reg_l(R_EAX));
			print_asm("out" " %%eax,(0x%x)", op_src->val);
		}
	}
	return len + 1;
}
make_helper(out_a2d) {
	if (ops_decoded.opcode == 0xee)
	{
		pio_write(reg_w(R_DX), 1, reg_b(R_EAX));
		print_asm("out" " %%al,(%%dx)");
	}
	else
	{
		if (ops_decoded.is_data_size_16)
		{
			pio_write(reg_w(R_DX), 2, reg_w(R_EAX));
			print_asm("out" " %%ax,(%%dx)");
		}
		else
		{
			pio_write(reg_w(R_DX), 4, reg_l(R_EAX));
			print_asm("out" " %%eax,(%%dx)");
		}
	}
	return 1;
}
