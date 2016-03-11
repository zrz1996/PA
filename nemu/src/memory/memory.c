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

uint32_t lnaddr_read(lnaddr_t addr, size_t len) {
	return hwaddr_read(addr, len);
}

void lnaddr_write(lnaddr_t addr, size_t len, uint32_t data) {
	hwaddr_write(addr, len, data);
}


lnaddr_t seg_translate(swaddr_t addr, size_t len, uint8_t sreg)
{
	uint32_t gdt_addr = cpu.gdtr >> 16;
	uint32_t index = cpu.segreg[sreg] >> 3;
	index <<= 3;
	gdt_addr += index;
	uint64_t gdt = ((uint64_t)lnaddr_read(gdt_addr, 4) << 32) | lnaddr_read(gdt_addr + 4, 4);
	union {
		uint64_t gdt;
		SegDesc SD;
	}temp;
	temp.gdt = gdt;
	uint32_t base = (temp.SD.base_31_24 << 24) + (temp.SD.base_23_16 << 16) + (temp.SD.base_15_0);
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

