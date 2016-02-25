#include "cpu/exec/helper.h"

make_helper(cld) {
	cpu.df = 0;
	print_asm("cld");
	return 1;
}

