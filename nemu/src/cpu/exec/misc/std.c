#include "cpu/exec/helper.h"

make_helper(std) {
	cpu.df = 1;
	print_asm("std");
	return 1;
}

