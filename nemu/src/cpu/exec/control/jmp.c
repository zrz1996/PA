#include "cpu/exec/helper.h"
#include "nemu.h"
#include "../../lib-common/x86-inc/mmu.h"

#define DATA_BYTE 1
#include "jmp-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "jmp-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "jmp-template.h"
#undef DATA_BYTE

/* for instruction encoding overloading */

make_helper_v(jmp_i)
make_helper_v(jmp_rm)

make_helper(ljmp) {
	uint32_t eip_t = instr_fetch(eip + 1, 4) - 7;
	uint16_t cs_t = instr_fetch(eip + 5, 2);
	cpu.cs = cs_t;
	cpu.eip = eip_t;
	uint32_t gdt_addr = cpu.gdtr >> 16;
	uint32_t index = cpu.cs >> 3;
	printf("%d\n", index);
	index <<= 3;
	gdt_addr += index;
	uint64_t gdt = ((uint64_t)lnaddr_read(gdt_addr, 4) << 32) | lnaddr_read(gdt_addr + 4, 4);
	union {
		uint64_t gdt;
		SegDesc SD;
	}temp;
	temp.gdt = gdt;
	cpu.segbase[1] = (temp.SD.base_31_24 << 24) + (temp.SD.base_23_16 << 16) + (temp.SD.base_15_0);
	cpu.seglimit[1] = (temp.SD.limit_19_16 << 16) + temp.SD.limit_15_0;
	print_asm("ljmp" " 0x%x,0x%x", cpu.cs, cpu.eip + 7);
	return 7;
}
