#include "cpu/exec/template-start.h"

#define instr cltq

make_helper(concat(cwtl_, SUFFIX)) {
	if (DATA_BYTE == 2)
	{
		reg_w(R_AX) = (int16_t)((int8_t)reg_b(R_AL));
	}
	else
	{
		reg_l(R_EAX) = (int32_t)((int16_t)reg_b(R_AX));
	}
	if (DATA_BYTE == 2)
		print_asm("cbtw");
	else
		print_asm("cwtl");
	return 1;
}


#include "cpu/exec/template-end.h"
