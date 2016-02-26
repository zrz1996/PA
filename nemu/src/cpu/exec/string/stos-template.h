#include "cpu/exec/template-start.h"

#define instr stos

make_helper(concat(stos_, SUFFIX)) {
	DATA_TYPE temp = reg_l(R_ESI);
	swaddr_write(reg_l(R_EDI), DATA_BYTE, temp);
	if (cpu.df == 0)
	{
		reg_l(R_EDI) += DATA_BYTE;
	}
	else
	{
		reg_l(R_EDI) -= DATA_BYTE;
	}
	print_asm("stos");
	return 1;
}


#include "cpu/exec/template-end.h"
