#include "cpu/exec/template-start.h"

#define instr leave


make_helper(leave) {
	reg_l(R_ESP) = reg_l(R_EBP);
	if (ops_decoded.is_data_size_16)
	{
		reg_w(R_EBP) = swaddr_read(reg_l(R_ESP), 2, 2);
		reg_l(R_ESP) += 2;
	}
	else
	{
		reg_l(R_EBP) = swaddr_read(reg_l(R_ESP), 4, 2);
		reg_l(R_ESP) += 4;
	}
	print_asm("leave");
	return 1;
}


#include "cpu/exec/template-end.h"
