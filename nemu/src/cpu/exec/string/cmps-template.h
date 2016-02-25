#include "cpu/exec/template-start.h"

#define instr cmps

make_helper(concat(cmps_, SUFFIX)) {
	DATA_TYPE temp_s = swaddr_read(REG(R_ESI), DATA_BYTE);
	DATA_TYPE temp_d = swaddr_read(REG(R_EDI), DATA_BYTE);
	cpu.cf = 0;
	alu(temp_s, temp_d, 1, 1);
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
	print_asm("cmps");
	return 1;
}


#include "cpu/exec/template-end.h"
