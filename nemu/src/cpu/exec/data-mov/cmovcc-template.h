#include "cpu/exec/template-start.h"
#define instr cmove
static void do_execute()
{
	if (cpu.zf == 1)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}
make_instr_helper(rm2r)
#undef instr

#define instr cmovbe
static void do_execute()
{
	if (cpu.zf == 1 || cpu.cf == 1)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}
make_instr_helper(rm2r)
#undef instr

#define instr cmova
static void do_execute()
{
	if (cpu.zf == 0 && cpu.cf == 0)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}
make_instr_helper(rm2r)
#undef instr

#define instr cmovae
static void do_execute()
{
	if (cpu.cf == 0)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}
make_instr_helper(rm2r)
#undef instr

#define instr cmovb
static void do_execute()
{
	if (cpu.cf == 1)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}
make_instr_helper(rm2r)
#undef instr

#define instr cmovc
static void do_execute()
{
	if (cpu.cf == 1)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}
make_instr_helper(rm2r)
#undef instr

#define instr cmovcxz
static void do_execute()
{
	if (REG(R_CX) == 0)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}
make_instr_helper(rm2r)
#undef instr

#define instr cmovecxz
static void do_execute()
{
	if (REG(R_ECX))
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}
make_instr_helper(rm2r)
#undef instr

#define instr cmovz
static void do_execute()
{
	if (cpu.zf == 1)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}
make_instr_helper(rm2r)
#undef instr

#define instr cmovg
static void do_execute()
{
	if (cpu.zf == 0 && cpu.sf == cpu.of)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}
make_instr_helper(rm2r)
#undef instr

#define instr cmovge
static void do_execute()
{
	if (cpu.sf == cpu.of)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}
make_instr_helper(rm2r)
#undef instr

#define instr cmovl
static void do_execute()
{
	if (cpu.sf != cpu.of)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}
make_instr_helper(rm2r)
#undef instr

#define instr cmovle
static void do_execute()
{
	if (cpu.zf == 1 || cpu.sf != cpu.of)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}
make_instr_helper(rm2r)
#undef instr

#define instr cmovna
static void do_execute()
{
	if (cpu.zf == 1 || cpu.cf == 1)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}
make_instr_helper(rm2r)
#undef instr

#define instr cmovnae
static void do_execute()
{
	if (cpu.cf == 1)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}
make_instr_helper(rm2r)
#undef instr

#define instr cmovnb
static void do_execute()
{
	if (cpu.cf == 0)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}
make_instr_helper(rm2r)
#undef instr

#define instr cmovnbe
static void do_execute()
{
	if (cpu.zf == 0 && cpu.cf == 0)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}
make_instr_helper(rm2r)
#undef instr

#define instr cmovnc
static void do_execute()
{
	if (cpu.cf == 0)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}
make_instr_helper(rm2r)
#undef instr

#define instr cmovne
static void do_execute()
{
	if (cpu.zf == 0)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}
make_instr_helper(rm2r)
#undef instr

#define instr cmovng
static void do_execute()
{
	if (cpu.zf == 1 || cpu.sf != cpu.of)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}
make_instr_helper(rm2r)
#undef instr

#define instr cmovnge
static void do_execute()
{
	if (cpu.zf == 1 || cpu.sf != cpu.of)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}
make_instr_helper(rm2r)
#undef instr

#define instr cmovnl
static void do_execute()
{
	if (cpu.sf == cpu.of)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}
make_instr_helper(rm2r)
#undef instr

#define instr cmovnle
static void do_execute()
{
	if (cpu.zf == 0 || cpu.sf == cpu.of)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}
make_instr_helper(rm2r)
#undef instr

#define instr cmovno
static void do_execute()
{
	if (cpu.of == 0)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}
make_instr_helper(rm2r)
#undef instr

#define instr cmovnp
static void do_execute()
{
	if (cpu.pf == 0)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}
make_instr_helper(rm2r)
#undef instr

#define instr cmovns
static void do_execute()
{
	if (cpu.sf == 0)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}
make_instr_helper(rm2r)
#undef instr

#define instr cmovnz
static void do_execute()
{
	if (cpu.zf == 0)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}
make_instr_helper(rm2r)
#undef instr

#define instr cmovo
static void do_execute()
{
	if (cpu.of == 1)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}
make_instr_helper(rm2r)
#undef instr

#define instr cmovp
static void do_execute()
{
	if (cpu.pf == 1)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}
make_instr_helper(rm2r)
#undef instr

#define instr cmovpe
static void do_execute()
{
	if (cpu.pf == 1)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}
make_instr_helper(rm2r)
#undef instr

#define instr cmovpo
static void do_execute()
{
	if (cpu.pf == 0)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}
make_instr_helper(rm2r)
#undef instr

#define instr cmovs
static void do_execute()
{
	if (cpu.sf == 1)
		OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}
make_instr_helper(rm2r)
#undef instr

#include "cpu/exec/template-end.h"
