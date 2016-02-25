#include "cpu/exec/template-start.h"

#define instr movs

make_helper(concat(movs_, SUFFIX)) {
	DATA_TYPE temp = swaddr_read(REG(R_ESI), DATA_BYTE);
	swaddr_write(REG(R_EDI), DATA_BYTE, temp);
	if (cpu.df == 0)
	{
		REG(R_ESI) += DATA_BYTE;
		REG(R_EDI) += DATA_BYTE;
	}
	else
	{
		REG(R_ESI) -= DATA_BYTE;
		REG(R_EDI) -= DATA_BYTE;
	}
	print_asm("movs");
	return 1;
}


#include "cpu/exec/template-end.h"
