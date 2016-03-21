#include "cpu/exec/helper.h"

make_helper(hlt) {
	if (!cpu.INTR)
		cpu.eip--;
	print_asm("hlt");
	return 1;
}

