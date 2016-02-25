#include "cpu/exec/template-start.h"

/*
#define instr ret
make_helper(ret) {
	cpu.eip = MEM_R(REG(R_ESP));
	REG(R_ESP) += 4;
	print_asm("ret");
	return 0;
}
*/
#include "cpu/exec/template-end.h"
