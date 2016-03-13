#include "cpu/exec/template-start.h"
#include "../alu.h"

#define instr sete
static void do_execute()
{
	if (cpu.zf == 1)
		OPERAND_W(op_src, 1);
	else
		OPERAND_W(op_src, 0);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr

#define instr setbe
static void do_execute()
{
	if (cpu.zf == 1 || cpu.cf == 1)
		OPERAND_W(op_src, 1);
	else
		OPERAND_W(op_src, 0);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr

#define instr seta
static void do_execute()
{
	if (cpu.zf == 0 && cpu.cf == 0)
		OPERAND_W(op_src, 1);
	else
		OPERAND_W(op_src, 0);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr

#define instr setae
static void do_execute()
{
	if (cpu.cf == 0)
		OPERAND_W(op_src, 1);
	else
		OPERAND_W(op_src, 0);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr

#define instr setb
static void do_execute()
{
	if (cpu.cf == 1)
		OPERAND_W(op_src, 1);
	else
		OPERAND_W(op_src, 0);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr

#define instr setc
static void do_execute()
{
	if (cpu.cf == 1)
		OPERAND_W(op_src, 1);
	else
		OPERAND_W(op_src, 0);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr

#define instr setz
static void do_execute()
{
	if (cpu.zf == 1)
		OPERAND_W(op_src, 1);
	else
		OPERAND_W(op_src, 0);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr

#define instr setg
static void do_execute()
{
	if (cpu.zf == 0 && cpu.sf == cpu.of)
		OPERAND_W(op_src, 1);
	else
		OPERAND_W(op_src, 0);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr

#define instr setge
static void do_execute()
{
	if (cpu.sf == cpu.of)
		OPERAND_W(op_src, 1);
	else
		OPERAND_W(op_src, 0);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr

#define instr setl
static void do_execute()
{
	if (cpu.sf != cpu.of)
		OPERAND_W(op_src, 1);
	else
		OPERAND_W(op_src, 0);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr

#define instr setle
static void do_execute()
{
	if (cpu.zf == 1 || cpu.sf != cpu.of)
		OPERAND_W(op_src, 1);
	else
		OPERAND_W(op_src, 0);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr

#define instr setna
static void do_execute()
{
	if (cpu.zf == 1 || cpu.cf == 1)
		OPERAND_W(op_src, 1);
	else
		OPERAND_W(op_src, 0);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr

#define instr setnae
static void do_execute()
{
	if (cpu.cf == 1)
		OPERAND_W(op_src, 1);
	else
		OPERAND_W(op_src, 0);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr

#define instr setnb
static void do_execute()
{
	if (cpu.cf == 0)
		OPERAND_W(op_src, 1);
	else
		OPERAND_W(op_src, 0);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr

#define instr setnbe
static void do_execute()
{
	if (cpu.zf == 0 || cpu.cf == 0)
		OPERAND_W(op_src, 1);
	else
		OPERAND_W(op_src, 0);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr

#define instr setnc
static void do_execute()
{
	if (cpu.cf == 0)
		OPERAND_W(op_src, 1);
	else
		OPERAND_W(op_src, 0);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr

#define instr setne
static void do_execute()
{
	if (cpu.zf == 0)
		OPERAND_W(op_src, 1);
	else
		OPERAND_W(op_src, 0);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr

#define instr setng
static void do_execute()
{
	if (cpu.zf == 1 || cpu.sf != cpu.of)
		OPERAND_W(op_src, 1);
	else
		OPERAND_W(op_src, 0);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr

#define instr setnge
static void do_execute()
{
	if (cpu.zf == 1 || cpu.sf != cpu.of)
		OPERAND_W(op_src, 1);
	else
		OPERAND_W(op_src, 0);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr

#define instr setnl
static void do_execute()
{
	if (cpu.sf == cpu.of)
		OPERAND_W(op_src, 1);
	else
		OPERAND_W(op_src, 0);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr

#define instr setnle
static void do_execute()
{
	if (cpu.zf == 0 || cpu.sf == cpu.of)
		OPERAND_W(op_src, 1);
	else
		OPERAND_W(op_src, 0);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr

#define instr setno
static void do_execute()
{
	if (cpu.of == 0)
		OPERAND_W(op_src, 1);
	else
		OPERAND_W(op_src, 0);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr

#define instr setnp
static void do_execute()
{
	if (cpu.pf == 0)
		OPERAND_W(op_src, 1);
	else
		OPERAND_W(op_src, 0);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr

#define instr setns
static void do_execute()
{
	if (cpu.sf == 0)
		OPERAND_W(op_src, 1);
	else
		OPERAND_W(op_src, 0);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr

#define instr setnz
static void do_execute()
{
	if (cpu.zf == 0)
		OPERAND_W(op_src, 1);
	else
		OPERAND_W(op_src, 0);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr

#define instr seto
static void do_execute()
{
	if (cpu.of == 1)
		OPERAND_W(op_src, 1);
	else
		OPERAND_W(op_src, 0);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr

#define instr setp
static void do_execute()
{
	if (cpu.pf == 1)
		OPERAND_W(op_src, 1);
	else
		OPERAND_W(op_src, 0);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr

#define instr setpe
static void do_execute()
{
	if (cpu.pf == 1)
		OPERAND_W(op_src, 1);
	else
		OPERAND_W(op_src, 0);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr

#define instr setpo
static void do_execute()
{
	if (cpu.pf == 0)
		OPERAND_W(op_src, 1);
	else
		OPERAND_W(op_src, 0);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr

#define instr sets
static void do_execute()
{
	if (cpu.sf == 1)
		OPERAND_W(op_src, 1);
	else
		OPERAND_W(op_src, 0);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr

#include "cpu/exec/template-end.h"
