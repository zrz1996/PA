#include "common.h"
#include "misc.h"
#include "stdlib.h"

uint32_t dram_read(hwaddr_t, size_t);
void dram_write(hwaddr_t, size_t, uint32_t);

#define CACHE_DATA_SIZE 16

#define BLOCK_WIDTH 6
#define LINE_WIDTH 3
#define SET_WIDTH (CACHE_DATA_SIZE - BLOCK_WIDTH - LINE_WIDTH)

typedef union {
	struct {
		uint32_t tag: 32 - SET_WIDTH - BLOCK_WIDTH;
		uint32_t set: SET_WIDTH;
		uint32_t block: BLOCK_WIDTH;
	};
	uint32_t addr;
} cache_addr;

#define NR_BLOCK (1 << BLOCK_WIDTH)
#define NR_SET (1 << SET_WIDTH)
#define NR_LINE (1 << LINE_WIDTH)

#define get_tag(x) ((x) >> (SET_WIDTH + BLOCK_WIDTH))
#define get_pos(x) ((x) & (NR_BLOCK - 1))

typedef struct Block{
	uint8_t data[NR_BLOCK];
	uint32_t tag;
	bool valid_bit;

	void (* init) (struct Block *this);
	void (* write) (struct Block *this, uint32_t arg);
	bool (* check) (struct Block *this, uint32_t arg);
	uint8_t (*read) (struct Block *this, uint32_t arg);
} Block;
void Block_init(Block *this)
{
	memset(this->data, 0, sizeof(this->data));
	this->tag = 0;
	this->valid_bit = 0;
}
void Block_wirte(Block *this, uint32_t addr)
{
	this->tag = get_tag(addr);
	int i;
	for (i = 0; i < NR_BLOCK; i++)
		this->data[i] = dram_read(addr + i, 1);
	this->valid_bit = 1;
}
bool Block_check(Block *this, uint32_t addr)
{
	if (this->valid_bit == 0)
		return 0;
	if (this->tag != get_tag(addr))
		return 0;
	return 1;
}
uint8_t Block_read(Block *this, uint32_t addr)
{
	return this->data[get_pos(addr)];
}

Block cache[NR_SET][NR_LINE];

void cache_init()
{
	int i, j;
	for (i = 0; i < NR_SET; i++)
		for (j = 0; j < NR_LINE; j++)
		{
			cache[i][j].init = Block_init;
			cache[i][j].write = Block_wirte;
			cache[i][j].read = Block_read;
			cache[i][j].check = Block_check;
			cache[i][j].init(&cache[i][j]);
		}
}
uint32_t cache_update(uint32_t addr)
{
	cache_addr temp;
	temp.addr = addr;
	uint32_t set = temp.set;
	int i;
	uint32_t line = -1;
	for (i = 0; i < NR_LINE; i++)
		if (cache[set][i].valid_bit == 0)
			line = i;
	if (line == -1)
		line = rand() & (NR_LINE - 1);
	cache[set][line].write(&cache[set][line], addr);
	return line;
}
void cache_r(hwaddr_t addr, void *data, size_t len)
{
	//Assert(addr < HW_MEM_SIZE, "physical address %x is outside of the physical memory!", addr);
	cache_addr temp;
	temp.addr = addr;
	uint32_t tag = temp.tag;
	uint32_t set = temp.set;
	uint32_t block = temp.block;
	int i;
	for (i = 0; i < NR_LINE; i++)
		if (cache[set][i].tag == tag && cache[set][i].valid_bit == 1)
		{
			memcpy(data, cache[set][i].data + block, len);
			return;
		}
	memcpy(data, cache[set][cache_update(addr ^ block)].data + block, len);
}
uint32_t cache_read(hwaddr_t addr, size_t len)
{
	printf("%x %d\n", addr, (int)len);
	uint32_t offset = addr & (NR_BLOCK - 1);
	union {
		uint8_t temp[4];
		uint32_t ret;
	}buf;
	if (offset + len > NR_BLOCK)
	{
		cache_r(addr, buf.temp, NR_BLOCK - offset);
		cache_r((addr ^ offset) + NR_BLOCK, buf.temp + NR_BLOCK - offset, len - (NR_BLOCK - offset));
	}
	else
	{
		printf("...");
		cache_r(addr, buf.temp, len);
	}
	return buf.ret;
}
void cache_w(hwaddr_t addr, size_t len, void *data)
{
	//Assert(addr < HW_MEM_SIZE, "physical address %x is outside of the physical memory!", addr);
	cache_addr temp;
	temp.addr = addr;
	uint32_t tag = temp.tag;
	uint32_t set = temp.set;
	uint32_t block = temp.block;
	int i;
	for (i = 0; i < NR_LINE; i++)
		if (cache[set][i].tag == tag && cache[set][i].valid_bit == 1)
		{
			memcpy(cache[set][i].data + block, data, len);
			return;
		}
}
void cache_write(hwaddr_t addr, size_t len, uint32_t data)
{
	uint32_t offset = addr & (NR_BLOCK - 1);
	union {
		uint8_t temp[4];
		uint32_t ret;
	}buf;
	buf.ret = data;
	dram_write(addr, len, data);
	if (offset + len > NR_BLOCK)
	{
		cache_w(addr, NR_BLOCK - offset, buf.temp);
		cache_w((addr ^ offset) + NR_BLOCK, len - (NR_BLOCK - offset), buf.temp + NR_BLOCK - offset);
	}
	else
		cache_w(addr, len, buf.temp);
}
