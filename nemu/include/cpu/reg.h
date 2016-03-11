#ifndef __REG_H__
#define __REG_H__

#include "common.h"
#include "../../lib-common/x86-inc/cpu.h"

enum { R_EAX, R_ECX, R_EDX, R_EBX, R_ESP, R_EBP, R_ESI, R_EDI };
enum { R_AX, R_CX, R_DX, R_BX, R_SP, R_BP, R_SI, R_DI };
enum { R_AL, R_CL, R_DL, R_BL, R_AH, R_CH, R_DH, R_BH };

/* TODO: Re-organize the `CPU_state' structure to match the register
 * encoding scheme in i386 instruction format. For example, if we
 * access cpu.gpr[3]._16, we will get the `bx' register; if we access
 * cpu.gpr[1]._8[1], we will get the 'ch' register. Hint: Use `union'.
 * For more details about the register encoding scheme, see i386 manual.
 */

typedef struct {
	union {
		union {
			uint32_t _32;
			uint16_t _16;
			uint8_t _8[2];
		} gpr[8];

		/* Do NOT change the order of the GPRs' definitions. */

		struct { 
			uint32_t eax, ecx, edx, ebx, esp, ebp, esi, edi; 
		};
	};
	struct {
		union {
			uint32_t eflags;
			struct {
				uint8_t cf : 1;
				uint8_t res1 : 1;
				uint8_t pf : 1;
				uint8_t res2 : 1;
				uint8_t af : 1;
				uint8_t res3 : 1;
				uint8_t zf : 1;
				uint8_t sf : 1;
				uint8_t tf : 1;
				uint8_t _if_ : 1; 
				uint8_t df : 1;
				uint8_t of : 1;
				uint8_t ol : 1;
				uint8_t ip : 1;
				uint8_t nt : 1;
				uint8_t res4 : 1;
				uint8_t rf : 1;
				uint8_t vm : 1;
			};
		};
	};
	swaddr_t eip;
	//uint32_t cr0;
	CR0 cr0;
	CR3 cr3;
	union {
		uint16_t segreg[4];
		struct {
			uint16_t es, cs, ss, ds;
		};
	};
	uint32_t segbase[4];
	uint32_t seglimit[4];
	uint64_t gdtr;
} CPU_state;

extern CPU_state cpu;

static inline int check_reg_index(int index) {
	assert(index >= 0 && index < 8);
	return index;
}

#define reg_l(index) (cpu.gpr[check_reg_index(index)]._32)
#define reg_w(index) (cpu.gpr[check_reg_index(index)]._16)
#define reg_b(index) (cpu.gpr[check_reg_index(index) & 0x3]._8[index >> 2])

extern const char* regsl[];
extern const char* regsw[];
extern const char* regsb[];

extern const char* segname[];  

#endif
