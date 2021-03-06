#include "common.h"
#include "nemu.h"
#include "../../lib-common/x86-inc/mmu.h"
#include "device/mmio.h"

uint32_t dram_read(hwaddr_t, size_t);
void dram_write(hwaddr_t, size_t, uint32_t);

void cache_write(hwaddr_t, size_t, uint32_t);
uint32_t cache_read(hwaddr_t, size_t);
//#define CACHE_ENABLE

hwaddr_t TLB_translate(lnaddr_t addr);
#define TLB_ENABLE
extern uint32_t TLB[];
inline uint32_t hwaddr_read(hwaddr_t addr, size_t len) {
	int id = is_mmio(addr);
	if (id != - 1)
	{
		return mmio_read(addr, len, id);
	}
	else
	{
#ifndef CACHE_ENABLE
		return dram_read(addr, len) & (~0u >> ((4 - len) << 3));
#else
		return cache_read(addr, len) & (~0u >> ((4 - len) << 3));
#endif
	}
}

inline void hwaddr_write(hwaddr_t addr, size_t len, uint32_t data) {
	int id = is_mmio(addr);
	if (id != -1)
	{
		mmio_write(addr, len, data, id);
	}
	else
	{
#ifndef CACHE_ENABLE
		dram_write(addr, len, data);
#else
		cache_write(addr, len, data);
#endif
	}
}

hwaddr_t page_translate(lnaddr_t addr)
{
	if (!cpu.cr0.protect_enable || !cpu.cr0.paging)
		return addr;
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
	return (pg_entry.page_frame << 12) | temp.offset;
}

inline uint32_t lnaddr_read(lnaddr_t addr, size_t len) {
#ifdef DEBUG
	assert(len == 1 || len == 2 || len == 4);
#endif
	if ((addr >> 12) != ((addr + len - 1) >> 12)) /* cross a page */
	{
		int len1 = 4096 - (addr & 0xfff);
		int len2 = len - len1;
#ifndef TLB_ENABLE
		hwaddr_t hwaddr1 = page_translate(addr);
		hwaddr_t hwaddr2 = page_translate(addr + len1);
#else
		hwaddr_t hwaddr1 = TLB_translate(addr);
		hwaddr_t hwaddr2 = (TLB[addr >> 12] & 2) ? hwaddr1 + len1 : TLB_translate(addr + len1);
#endif
		/*
		if (hwaddr2 == hwaddr1)
			return hwaddr_read(hwaddr1, len);
		uint32_t ret1 = (len1 == 3) ? (hwaddr_read(hwaddr1, 2) | (hwaddr_read(hwaddr1 + 2, 1) << 16)) : hwaddr_read(hwaddr1, len1);
		uint32_t ret2 = (len2 == 3) ? (hwaddr_read(hwaddr2, 2) | (hwaddr_read(hwaddr2 + 2, 1) << 16)) : hwaddr_read(hwaddr2, len2);
		*/
		uint32_t ret1 = hwaddr_read(hwaddr1, len1);
		uint32_t ret2 = hwaddr_read(hwaddr2, len2);
		return ret1 | (ret2 << (len1 << 3));
	}
	else
	{
#ifndef TLB_ENABLE
		hwaddr_t hwaddr = page_translate(addr);
#else
		hwaddr_t hwaddr = TLB_translate(addr);
#endif
		return hwaddr_read(hwaddr, len);
	}
}

inline void lnaddr_write(lnaddr_t addr, size_t len, uint32_t data) {
#ifdef DEBUG
	assert(len == 1 || len == 2 || len == 4);
#endif
	if ((addr >> 12) != ((addr + len - 1) >> 12)) /* cross a page */
	{
		int len1 = 4096 - (addr & 0xfff);
		int len2 = len - len1;
#ifndef TLB_ENABLE
		hwaddr_t hwaddr1 = page_translate(addr);
		hwaddr_t hwaddr2 = page_translate(addr + len1);
#else
		hwaddr_t hwaddr1 = TLB_translate(addr);
		hwaddr_t hwaddr2 = TLB_translate(addr + len1);
		//hwaddr_t hwaddr2 = (TLB[addr >> 12] & 2) ? hwaddr1 + len : TLB_translate(addr + len1);
#endif
		/*
		if (len1 == 3)
		{
			hwaddr_write(hwaddr1, 2, data & 0xffff);
			hwaddr_write(hwaddr1 + 2, 1, (data >> 16) & 0xff);
		}
		else
			hwaddr_write(hwaddr1, len1, data & ((1 << (len1 << 3)) - 1));
		data >>= (len1 << 3);
		if (len2 == 3)
		{
			hwaddr_write(hwaddr2, 2, data & 0xffff);
			hwaddr_write(hwaddr2 + 2, 1, (data >> 16) & 0xff);
		}
		else
			hwaddr_write(hwaddr2, len2, data);
		*/
		hwaddr_write(hwaddr1, len1, data & ((1 << (len1 << 3)) - 1));
		hwaddr_write(hwaddr2, len2, data >> (len1 << 3));
	}
	else
	{
#ifndef TLB_ENABLE
		hwaddr_t hwaddr = page_translate(addr);
#else
		hwaddr_t hwaddr = TLB_translate(addr);
#endif
		hwaddr_write(hwaddr, len, data);
	}
}


inline lnaddr_t seg_translate(swaddr_t addr, uint8_t sreg)
{
	/*
	if (!cpu.cr0.protect_enable)
		return addr;
	*/
	uint32_t base = cpu.segbase[sreg];
	assert(base == 0);
	return addr + base;
}


inline uint32_t swaddr_read(swaddr_t addr, size_t len, uint8_t sreg) {
#ifdef DEBUG
	assert(len == 1 || len == 2 || len == 4);
#endif
	if (!cpu.cr0.protect_enable)
		return lnaddr_read(addr, len);
	/*
	lnaddr_t lnaddr = seg_translate(addr, sreg);
	return lnaddr_read(lnaddr, len);
	*/
	return lnaddr_read(addr, len);
}

inline void swaddr_write(swaddr_t addr, size_t len, uint32_t data, uint8_t sreg) {
#ifdef DEBUG
	assert(len == 1 || len == 2 || len == 4);
#endif
	if (!cpu.cr0.protect_enable)
		return lnaddr_write(addr, len, data);
	lnaddr_t lnaddr = seg_translate(addr, sreg);
	lnaddr_write(lnaddr, len, data);
}

