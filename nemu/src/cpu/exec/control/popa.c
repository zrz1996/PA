#include "cpu/exec/helper.h"

/* for instruction encoding overloading */

make_helper(popa)
{
	int len = 4;
	if (ops_decoded.is_data_size_16)
		len = 2;
	uint32_t temp = cpu.esp;
	int i;
	if (len == 2)
	{
		for (i = 7; i >= 0; i--)
		{
			cpu.gpr[i]._16 = swaddr_read(temp, len, 2);
			temp += len;
		}
	}
	else
	{
		for (i = 7; i >= 0; i--)
		{
			cpu.gpr[i]._32 = swaddr_read(temp, len, 2);
			temp += len;
		}
	}
	cpu.esp = temp;
	if (len == 2)
		print_asm("popa");
	else
		print_asm("popad");
	return 1;
}
