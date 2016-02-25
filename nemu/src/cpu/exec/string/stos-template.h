#include "cpu/exec/template-start.h"

#define instr stos

make_helper(concat(stos_, SUFFIX)) {
	DATA_TYPE temp = REG(R_ESI);
	swaddr_write(REG(R_EDI), DATA_BYTE, temp);
	if (cpu.df == 0)
	{
		REG(R_EDI) += DATA_BYTE;
	}
	else
	{
		REG(R_EDI) -= DATA_BYTE;
	}
	print_asm("stos");
	return 1;
}


#include "cpu/exec/template-end.h"
