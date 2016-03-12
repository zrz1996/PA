#include "common.h"
#include "misc.h"
#include "stdlib.h"
#include "../../lib-common/x86-inc/mmu.h"
#include "nemu.h"

uint32_t hwaddr_read(hwaddr_t hwaddr, size_t len);

#define NR_ITEM 64

typedef struct {
	PTE pg;
	uint32_t tag;
	uint8_t valid_bit;
} Item;

Item TLB[NR_ITEM];

void TLB_init()
{
	int i;
	for (i = 0; i < NR_ITEM; i++)
	{
		TLB[i].valid_bit = 0;
	}
}

hwaddr_t TLB_translate(lnaddr_t addr)
{
	if (!cpu.cr0.protect_enable || !cpu.cr0.paging)
		return addr;
	uint32_t tag = addr >> 12;
	int i;
	for (i = 0; i < NR_ITEM; i++)
		if (TLB[i].valid_bit && TLB[i].tag == tag)
		{
			return (TLB[i].pg.page_frame << 12) | (addr & 0xfff);
		}

	uint32_t pd1_base = cpu.cr3.page_directory_base << 12;
	union {
		struct {
			uint32_t offset : 12;
			uint32_t page : 10;
			uint32_t dir : 10;
		};
		uint32_t addr;
	} temp;
	temp.addr = addr;
	PDE dir_entry;
	dir_entry.val = hwaddr_read(pd1_base | (temp.dir << 2), 4);
	assert(dir_entry.present);
	PTE pg_entry;
	pg_entry.val = hwaddr_read((dir_entry.page_frame << 12) | (temp.page << 2), 4);
	assert(pg_entry.present);
	uint32_t len = rand() % NR_ITEM;
	TLB[len].pg = pg_entry;
	TLB[len].valid_bit = 1;
	TLB[len].tag = tag;
	return (pg_entry.page_frame << 12) | temp.offset;
}
