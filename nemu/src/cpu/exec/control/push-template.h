#include "cpu/exec/template-start.h"

#define instr push

static void do_execute()
{
	REG(R_ESP) -= DATA_BYTE;
	MEM_W(REG(R_ESP), op_src->val);
}
make_instr_helper(r)
#include "cpu/exec/template-end.h"
