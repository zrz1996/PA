#include "cpu/exec/template-start.h"

#define instr movs

make_helper(concat(movs_, SUFFIX)) {
	DATA_TYPE temp = swaddr_read(reg_l(R_ESI), DATA_BYTE);
	printf("%x\n", temp);
	swaddr_write(reg_l(R_EDI), DATA_BYTE, temp);
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
	print_asm("movs");
	return 1;
}


#include "cpu/exec/template-end.h"
