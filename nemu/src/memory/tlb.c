#include "common.h"
#include "misc.h"
#include "stdlib.h"
#include "../../lib-common/x86-inc/mmu.h"
#include "nemu.h"

uint32_t hwaddr_read(hwaddr_t hwaddr, size_t len);

#define NR_ITEM 1048576

uint32_t TLB[NR_ITEM];

void TLB_init()
{
	memset(TLB, 0, sizeof(TLB));
}

inline void TLB_insert()
{
	uint32_t tag = 0;
	for (; tag < NR_ITEM; tag++)
	{
		uint32_t addr = tag << 12;
		uint32_t dir_addr = (cpu.cr3.val & 0xfffff000) | ((addr >> 20) & 0xffc);
		uint32_t dir_entry = hwaddr_read(dir_addr, 4);
		uint32_t pg_addr = (dir_entry & 0xfffff000) | ((addr >> 10) & 0xffc);
		uint32_t pg_entry = hwaddr_read(pg_addr, 4);
		TLB[tag] = (pg_entry & 0xfffff000) | 1;
	}
	for (tag = 0; tag < NR_ITEM - 1; tag++)
		if (TLB[tag + 1] == TLB[tag] + 0x1000)
			TLB[tag] |= 2;
}
inline hwaddr_t TLB_translate(lnaddr_t addr)
{
	if (!cpu.cr0.protect_enable || !cpu.cr0.paging)
		return addr;
	uint32_t tag = addr >> 12;
#ifdef DEBUG
	assert(tag < NR_ITEM);
#endif
	if (TLB[tag] & 1)
		return (TLB[tag] & 0xfffffffc) | (addr & 0xfff);
	TLB_insert();
	return (TLB[tag] & 0xfffffffc) | (addr & 0xfff);
		/*
	uint32_t dir_addr = (cpu.cr3.val & 0xfffff000) | ((addr >> 20) & 0xffc);
	uint32_t dir_entry = hwaddr_read(dir_addr, 4);
#ifdef DEBUG
	assert(dir_entry & 1);
#endif
	uint32_t pg_addr = (dir_entry & 0xfffff000) | ((addr >> 10) & 0xffc);
	uint32_t pg_entry = hwaddr_read(pg_addr, 4);
#ifdef DEBUG
	assert(pg_entry & 1);
#endif
	TLB[tag] = (pg_entry & 0xfffff000) | 1;
	printf("%x %x\n", tag, TLB[tag] - 1);
	if (tag + 1 != NR_ITEM && (TLB[tag + 1] & 1))
		if (TLB[tag + 1] == TLB[tag] + 0x1000)
			TLB[tag] |= 2;
	return (pg_entry & 0xfffff000) | (addr & 0xfff);
	*/
}
