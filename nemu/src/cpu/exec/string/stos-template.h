#include "cpu/exec/template-start.h"

#define instr stos

make_helper(concat(stos_, SUFFIX)) {
	DATA_TYPE temp = REG(R_EAX);
	swaddr_write(reg_l(R_EDI), DATA_BYTE, temp);
	if (cpu.df == 0)
	{
		reg_l(R_EDI) += DATA_BYTE;
	}
	else
	{
		reg_l(R_EDI) -= DATA_BYTE;
	}
	print_asm(str(concat(stos, SUFFIX)));
	return 1;
}


#include "cpu/exec/template-end.h"
