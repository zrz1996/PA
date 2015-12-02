#include "cpu/exec/template-start.h"
#include "../alu.h"
#define instr je
static void do_execute()
{
	if (cpu.zf == 1)
		cpu.eip += signExtend(op_src->val, DATA_BYTE);
	print_asm_template1();
}
make_instr_helper(i)
#undef instr

#define instr jbe
static void do_execute()
{
	if (cpu.zf == 1 || cpu.cf == 1)
		cpu.eip += signExtend(op_src->val, DATA_BYTE);
	print_asm_template1();
}
make_instr_helper(i)
#undef instr

#define instr ja
static void do_execute()
{
	if (cpu.zf == 0 || cpu.cf == 0)
		cpu.eip += signExtend(op_src->val, DATA_BYTE);
	print_asm_template1();
}
make_instr_helper(i)
#undef instr

#define instr jae
static void do_execute()
{
	if (cpu.cf == 0)
		cpu.eip += signExtend(op_src->val, DATA_BYTE);
	print_asm_template1();
}
make_instr_helper(i)
#undef instr

#define instr jb
static void do_execute()
{
	if (cpu.cf == 1)
		cpu.eip += signExtend(op_src->val, DATA_BYTE);
	print_asm_template1();
}
make_instr_helper(i)
#undef instr

#define instr jc
static void do_execute()
{
	if (cpu.cf == 1)
		cpu.eip += signExtend(op_src->val, DATA_BYTE);
	print_asm_template1();
}
make_instr_helper(i)
#undef instr

#define instr jcxz
static void do_execute()
{
	if (REG(R_CX) == 0)
		cpu.eip += signExtend(op_src->val, DATA_BYTE);
	print_asm_template1();
}
make_instr_helper(i)
#undef instr

#define instr jecxz
static void do_execute()
{
	if (REG(R_ECX))
		cpu.eip += signExtend(op_src->val, DATA_BYTE);
	print_asm_template1();
}
make_instr_helper(i)
#undef instr

#define instr jz
static void do_execute()
{
	if (cpu.zf == 1)
		cpu.eip += signExtend(op_src->val, DATA_BYTE);
	print_asm_template1();
}
make_instr_helper(i)
#undef instr

#define instr jg
static void do_execute()
{
	if (cpu.zf == 0 && cpu.sf == cpu.of)
		cpu.eip += signExtend(op_src->val, DATA_BYTE);
	print_asm_template1();
}
make_instr_helper(i)
#undef instr

#define instr jge
static void do_execute()
{
	if (cpu.sf == cpu.of)
		cpu.eip += signExtend(op_src->val, DATA_BYTE);
	print_asm_template1();
}
make_instr_helper(i)
#undef instr

#define instr jl
static void do_execute()
{
	if (cpu.sf != cpu.of)
		cpu.eip += signExtend(op_src->val, DATA_BYTE);
	print_asm_template1();
}
make_instr_helper(i)
#undef instr

#define instr jle
static void do_execute()
{
	if (cpu.zf == 1 || cpu.sf != cpu.of)
		cpu.eip += signExtend(op_src->val, DATA_BYTE);
	print_asm_template1();
}
make_instr_helper(i)
#undef instr

#define instr jna
static void do_execute()
{
	if (cpu.zf == 1 || cpu.cf == 1)
		cpu.eip += signExtend(op_src->val, DATA_BYTE);
	print_asm_template1();
}
make_instr_helper(i)
#undef instr

#define instr jnae
static void do_execute()
{
	if (cpu.cf == 1)
		cpu.eip += signExtend(op_src->val, DATA_BYTE);
	print_asm_template1();
}
make_instr_helper(i)
#undef instr

#define instr jnb
static void do_execute()
{
	if (cpu.cf == 0)
		cpu.eip += signExtend(op_src->val, DATA_BYTE);
	print_asm_template1();
}
make_instr_helper(i)
#undef instr

#define instr jnbe
static void do_execute()
{
	if (cpu.zf == 0 || cpu.cf == 0)
		cpu.eip += signExtend(op_src->val, DATA_BYTE);
	print_asm_template1();
}
make_instr_helper(i)
#undef instr

#define instr jnc
static void do_execute()
{
	if (cpu.cf == 0)
		cpu.eip += signExtend(op_src->val, DATA_BYTE);
	print_asm_template1();
}
make_instr_helper(i)
#undef instr

#define instr jne
static void do_execute()
{
	if (cpu.zf == 0)
		cpu.eip += signExtend(op_src->val, DATA_BYTE);
	print_asm_template1();
}
make_instr_helper(i)
#undef instr

#define instr jng
static void do_execute()
{
	if (cpu.zf == 1 || cpu.sf != cpu.of)
		cpu.eip += signExtend(op_src->val, DATA_BYTE);
	print_asm_template1();
}
make_instr_helper(i)
#undef instr

#define instr jnge
static void do_execute()
{
	if (cpu.zf == 1 || cpu.sf != cpu.of)
		cpu.eip += signExtend(op_src->val, DATA_BYTE);
	print_asm_template1();
}
make_instr_helper(i)
#undef instr

#define instr jnl
static void do_execute()
{
	if (cpu.sf == cpu.of)
		cpu.eip += signExtend(op_src->val, DATA_BYTE);
	print_asm_template1();
}
make_instr_helper(i)
#undef instr

#define instr jnle
static void do_execute()
{
	if (cpu.zf == 0 || cpu.sf == cpu.of)
		cpu.eip += signExtend(op_src->val, DATA_BYTE);
	print_asm_template1();
}
make_instr_helper(i)
#undef instr

#define instr jno
static void do_execute()
{
	if (cpu.of == 0)
		cpu.eip += signExtend(op_src->val, DATA_BYTE);
	print_asm_template1();
}
make_instr_helper(i)
#undef instr

#define instr jnp
static void do_execute()
{
	if (cpu.pf == 0)
		cpu.eip += signExtend(op_src->val, DATA_BYTE);
	print_asm_template1();
}
make_instr_helper(i)
#undef instr

#define instr jns
static void do_execute()
{
	if (cpu.sf == 0)
		cpu.eip += signExtend(op_src->val, DATA_BYTE);
	print_asm_template1();
}
make_instr_helper(i)
#undef instr

#define instr jnz
static void do_execute()
{
	if (cpu.zf == 0)
		cpu.eip += signExtend(op_src->val, DATA_BYTE);
	print_asm_template1();
}
make_instr_helper(i)
#undef instr

#define instr jo
static void do_execute()
{
	if (cpu.of == 1)
		cpu.eip += signExtend(op_src->val, DATA_BYTE);
	print_asm_template1();
}
make_instr_helper(i)
#undef instr

#define instr jp
static void do_execute()
{
	if (cpu.pf == 1)
		cpu.eip += signExtend(op_src->val, DATA_BYTE);
	print_asm_template1();
}
make_instr_helper(i)
#undef instr

#define instr jpe
static void do_execute()
{
	if (cpu.pf == 1)
		cpu.eip += signExtend(op_src->val, DATA_BYTE);
	print_asm_template1();
}
make_instr_helper(i)
#undef instr

#define instr jpo
static void do_execute()
{
	if (cpu.pf == 0)
		cpu.eip += signExtend(op_src->val, DATA_BYTE);
	print_asm_template1();
}
make_instr_helper(i)
#undef instr

#define instr js
static void do_execute()
{
	if (cpu.sf == 1)
		cpu.eip += signExtend(op_src->val, DATA_BYTE);
	print_asm_template1();
}
make_instr_helper(i)
#undef instr

#include "cpu/exec/template-end.h"
