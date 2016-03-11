#include "cpu/exec/template-start.h"

#define instr cmps

make_helper(concat(cmps_, SUFFIX)) {
	DATA_TYPE temp_s = swaddr_read(reg_l(R_ESI), DATA_BYTE, 3);
	DATA_TYPE temp_d = swaddr_read(reg_l(R_EDI), DATA_BYTE, 2);
	cpu.cf = 0;
	alu(temp_s, temp_d, 1, 1);
	if (cpu.df == 0)
	{
		reg_l(R_ESI) += DATA_BYTE;
		reg_l(R_EDI) += DATA_BYTE;
	}
	else
	{
		reg_l(R_ESI) -= DATA_BYTE;
		reg_l(R_EDI) -= DATA_BYTE;
	}
	print_asm(str(concat(cmps, SUFFIX)));
	return 1;
}


#include "cpu/exec/template-end.h"
