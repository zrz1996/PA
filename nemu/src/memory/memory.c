#include "common.h"
#include "nemu.h"
#include "../../lib-common/x86-inc/mmu.h"

uint32_t dram_read(hwaddr_t, size_t);
void dram_write(hwaddr_t, size_t, uint32_t);

void cache_write(hwaddr_t, size_t, uint32_t);
uint32_t cache_read(hwaddr_t, size_t);
#define CACHE_ENABLE
/* Memory accessing interfaces */

uint32_t hwaddr_read(hwaddr_t addr, size_t len) {
#ifndef CACHE_ENABLE
	return dram_read(addr, len) & (~0u >> ((4 - len) << 3));
#else
	return cache_read(addr, len) & (~0u >> ((4 - len) << 3));
#endif
}

void hwaddr_write(hwaddr_t addr, size_t len, uint32_t data) {
#ifndef CACHE_ENABLE
	dram_write(addr, len, data);
#else
	cache_write(addr, len, data);
#endif
}

hwaddr_t page_translate(lnaddr_t addr)
{
	if (!cpu.cr0.protect_enable || !cpu.cr0.paging)
		return addr;
	printf("%x\n", addr);
	uint32_t pd1_base = cpu.cr3.page_directory_base;
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
	dir_entry.val = hwaddr_read(pd1_base + (temp.dir << 2), 4);
	assert(dir_entry.present);
	PTE pg_entry;
	pg_entry.val = hwaddr_read(dir_entry.page_frame + (temp.page << 2), 4);
	assert(pg_entry.present);
	return (pg_entry.page_frame << 12) | temp.page;
}

uint32_t lnaddr_read(lnaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	if ((addr >> 12) != ((addr + len) >> 12)) /* cross a page */
	{
		printf("cross a page!\n");
		assert(0);
	}
	else
	{
		hwaddr_t hwaddr = page_translate(addr);
		return hwaddr_read(hwaddr, len);
	}
}

void lnaddr_write(lnaddr_t addr, size_t len, uint32_t data) {
	assert(len == 1 || len == 2 || len == 4);
	if ((addr >> 12) != ((addr + len) >> 12)) /* cross a page */
	{
		printf("cross a page!\n");
		printf("%x %d\n", addr, (int)len);
		assert(0);
	}
	else
	{
		hwaddr_t hwaddr = page_translate(addr);
		hwaddr_write(hwaddr, len, data);
	}
}


lnaddr_t seg_translate(swaddr_t addr, size_t len, uint8_t sreg)
{
	if (!cpu.cr0.protect_enable)
		return addr;
	uint32_t base = cpu.segbase[sreg];
	return addr + base;
}


uint32_t swaddr_read(swaddr_t addr, size_t len, uint8_t sreg) {
#ifdef DEBUG
	assert(len == 1 || len == 2 || len == 4);
#endif
	lnaddr_t lnaddr = seg_translate(addr, len, sreg);
	return lnaddr_read(lnaddr, len);
}

void swaddr_write(swaddr_t addr, size_t len, uint32_t data, uint8_t sreg) {
#ifdef DEBUG
	assert(len == 1 || len == 2 || len == 4);
#endif
	lnaddr_t lnaddr = seg_translate(addr, len, sreg);
	lnaddr_write(lnaddr, len, data);
}

