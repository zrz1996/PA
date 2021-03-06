#include "cpu/exec/template-start.h"

#define instr cltq

make_helper(cltq) {
	if (ops_decoded.is_data_size_16)
	{
		if ((int16_t)reg_w(R_EAX) < 0)
			reg_w(R_EDX) = 0xffff;
		else
			reg_w(R_EDX) = 0;
		print_asm("cwtd");
	}
	else
	{
		if ((int32_t)reg_l(R_EAX) < 0)
			reg_l(R_EDX) = 0xffffffff;
		else
			reg_l(R_EDX) = 0;
		print_asm("cltq");
	}
	return 1;
}


#include "cpu/exec/template-end.h"
