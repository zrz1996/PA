#include "common.h"
#include "memory.h"
#include <string.h>
#include "avatar.h"

#define VMEM_ADDR 0xa0000
#define VMEM_SIZE 0x20000
#define SCR_SIZE (320 * 200)

/* Use the function to get the start address of user page directory. */
inline PDE* get_updir();
static PTE ptable_video[(VMEM_ADDR + VMEM_SIZE) / PAGE_SIZE] align_to_page;

void create_video_mapping() {
	/* TODO: create an identical mapping from virtual memory area 
	 * [0xa0000, 0xa0000 + SCR_SIZE) to physical memory area 
	 * [0xa0000, 0xa0000 + SCR_SIZE) for user program. You may define
	 * some page tables to create this mapping.
	 */
	PDE* pdir = get_updir();
	PTE* ptable = (PTE *)va_to_pa(ptable_video);
	pdir[0].val = make_pde(ptable);
	memset(ptable_video, 0, sizeof(ptable_video));
	uint32_t addr = VMEM_ADDR;
	uint32_t i = VMEM_ADDR / PAGE_SIZE;
	for (; addr < VMEM_ADDR + VMEM_SIZE; addr += PAGE_SIZE) {
		ptable_video[i ++].val = make_pte(addr);
	}
}
/*
void video_mapping_write_test() {
	int i;
	uint32_t *buf = (void *)VMEM_ADDR;
	for(i = 0; i < SCR_SIZE / 4; i ++) {
		buf[i] = i;
	}
}

void video_mapping_read_test() {
	int i;
	uint32_t *buf = (void *)VMEM_ADDR;
	for(i = 0; i < SCR_SIZE / 4; i ++) {
		assert(buf[i] == i);
	}
}

void video_mapping_clear() {
	memset((void *)VMEM_ADDR, 0, SCR_SIZE);
}
*/
static uint8_t palette[256][3];

void video_mapping_write_test() {
	uint32_t *buf = (void *)VMEM_ADDR;
	uint32_t i;
	for (i = 0; i < 256; i++) {
		out_byte(0x3c7, i);
		palette[i][0] = in_byte(0x3c9);
		palette[i][1] = in_byte(0x3c9);
		palette[i][2] = in_byte(0x3c9);
	}
	out_byte(0x3c8, 0);
	for (i = 0; i < 256; i++) {
		out_byte(0x3c9, header_data_cmap[i][0] >> 2);
		out_byte(0x3c9, header_data_cmap[i][1] >> 2);
		out_byte(0x3c9, header_data_cmap[i][2] >> 2);
	}
	memcpy(buf, header_data, width * height);
}

void video_mapping_read_test() {
	int i;
	uint32_t *buf = (void *)VMEM_ADDR;
	for(i = 0; i < SCR_SIZE / 4; i ++) {
		assert(buf[i] == ((uint32_t *)header_data)[i]);
	}
}

void video_mapping_clear() {
	memset((void *)VMEM_ADDR, 0, SCR_SIZE);
	out_byte(0x3c8, 0);
	uint32_t i;
	for (i = 0; i < 256; i++) {
		out_byte(0x3c9, palette[i][0]);
		out_byte(0x3c9, palette[i][1]);
		out_byte(0x3c9, palette[i][2]);
	}
}
