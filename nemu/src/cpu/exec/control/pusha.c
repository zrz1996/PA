#include "cpu/exec/helper.h"

/* for instruction encoding overloading */

make_helper(pusha)
{
	int len = 4;
	if (ops_decoded.is_data_size_16)
		len = 2;
	uint32_t temp = cpu.esp;
	int i;
	for (i = 0; i < 8; i++)
	{
		temp -= len;
		swaddr_write(temp, len, cpu.gpr[i]._32, 2);
	}
	cpu.esp = temp;
	if (len == 2)
		print_asm("pusha");
	else
		print_asm("pushad");
	return 1;
}
