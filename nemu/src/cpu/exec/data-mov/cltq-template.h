#include "cpu/exec/template-start.h"

#define instr cltq

make_helper(cltq) {
	if (DATA_BYTE == 2)
	{
		if (reg_w(R_EAX) < 0)
			reg_w(R_EDX) = 0xffff;
		else
			reg_w(R_EDX) = 0;
	}
	else
	{
		if (reg_l(R_EAX) < 0)
			reg_l(R_EDX) = 0xffffffff;
		else
			reg_l(R_EDX) = 0;
		printf("%d\n", reg_l(R_EAX) < 0);
	}
	print_asm("cltq");
	return 1;
}


#include "cpu/exec/template-end.h"
