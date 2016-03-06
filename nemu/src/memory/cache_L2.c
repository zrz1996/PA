#include "common.h"
#include "misc.h"
#include "stdlib.h"

uint32_t dram_read(hwaddr_t, size_t);
void dram_write(hwaddr_t, size_t, uint32_t);

#define CACHE_L2_DATA_SIZE 22

#define BLOCK_WIDTH 6
#define LINE_WIDTH 4
#define SET_WIDTH (CACHE_L2_DATA_SIZE - BLOCK_WIDTH - LINE_WIDTH)

typedef union {
	struct {
		uint32_t block: BLOCK_WIDTH;
		uint32_t set: SET_WIDTH;
		uint32_t tag: (32 - SET_WIDTH - BLOCK_WIDTH);
	};
	uint32_t addr;
} cache_L2_addr;

#define NR_BLOCK (1 << BLOCK_WIDTH)
#define NR_SET (1 << SET_WIDTH)
#define NR_LINE (1 << LINE_WIDTH)

#define get_tag(x) ((x) >> (SET_WIDTH + BLOCK_WIDTH))
#define get_pos(x) ((x) & (NR_BLOCK - 1))

typedef struct Block_L2{
	uint8_t data[NR_BLOCK];
	uint32_t tag;
	bool valid_bit;
	bool dirty_bit;

	void (* init) (struct Block_L2 *this);
	void (* write) (struct Block_L2 *this, uint32_t arg);
	bool (* check) (struct Block_L2 *this, uint32_t arg);
	uint8_t (*read) (struct Block_L2 *this, uint32_t arg);
	void (* writeback) (struct Block_L2 *this, uint32_t arg);
} Block_L2;
void Block_L2_init(Block_L2 *this)
{
	memset(this->data, 0, sizeof(this->data));
	this->tag = 0;
	this->valid_bit = 0;
	this->dirty_bit = 0;
}
void Block_L2_wirte(Block_L2 *this, uint32_t addr)
{
	this->tag = get_tag(addr);
	int i;
	for (i = 0; i < NR_BLOCK; i++)
		this->data[i] = dram_read(addr + i, 1);
	this->valid_bit = 1;
	this->dirty_bit = 0;
}
void Block_L2_writeback(Block_L2 *this, uint32_t set)
{
	cache_L2_addr temp;
	temp.block = 0;
	temp.set = set;
	temp.tag = this->tag;
	hwaddr_t addr = temp.addr;
	int i;
	for (i = 0; i < NR_BLOCK; i++)
		dram_write(addr + i, 1, this->data[i]);
}
bool Block_L2_check(Block_L2 *this, uint32_t addr)
{
	if (this->valid_bit == 0)
		return 0;
	if (this->tag != get_tag(addr))
		return 0;
	return 1;
}
uint8_t Block_L2_read(Block_L2 *this, uint32_t addr)
{
	return this->data[get_pos(addr)];
}

Block_L2 cache_L2[NR_SET][NR_LINE];

void cache_L2_init()
{
	int i, j;
	for (i = 0; i < NR_SET; i++)
		for (j = 0; j < NR_LINE; j++)
		{
			cache_L2[i][j].init = Block_L2_init;
			cache_L2[i][j].write = Block_L2_wirte;
			cache_L2[i][j].read = Block_L2_read;
			cache_L2[i][j].check = Block_L2_check;
			cache_L2[i][j].init(&cache_L2[i][j]);
			cache_L2[i][j].writeback = Block_L2_writeback;
		}
}
uint32_t cache_L2_update(uint32_t addr, int line)
{
	cache_L2_addr temp;
	temp.addr = addr;
	uint32_t set = temp.set;
	if (line == -1)
	{
		line = rand() & (NR_LINE - 1);
		if (cache_L2[set][line].dirty_bit == 1)
		{
			cache_L2[set][line].writeback(&cache_L2[set][line], set);
		}
	}
	cache_L2[set][line].write(&cache_L2[set][line], addr);
	return line;
}
void cache_L2_r(hwaddr_t addr, void *data, size_t len)
{
	cache_L2_addr temp;
	temp.addr = addr;
	uint32_t tag = temp.tag;
	uint32_t set = temp.set;
	uint32_t block = temp.block;
	int i, pos = -1;
	for (i = 0; i < NR_LINE; i++)
		if (cache_L2[set][i].tag == tag && cache_L2[set][i].valid_bit == 1)
		{
			memcpy(data, cache_L2[set][i].data + block, len);
			return;
		}
		else
		{
			if (cache_L2[set][i].valid_bit == 0)
				pos = i;
		}
	memcpy(data, cache_L2[set][cache_L2_update(addr ^ block, pos)].data + block, len);
}
uint32_t cache_L2_read(hwaddr_t addr, size_t len)
{
	uint32_t offset = addr & (NR_BLOCK - 1);
	union {
		uint8_t temp[4];
		uint32_t ret;
	}buf;
	if (offset + len > NR_BLOCK)
	{
		cache_L2_r(addr, buf.temp, NR_BLOCK - offset);
		cache_L2_r((addr ^ offset) + NR_BLOCK, buf.temp + NR_BLOCK - offset, len - (NR_BLOCK - offset));
	}
	else
	{
		cache_L2_r(addr, buf.temp, len);
	}
	return buf.ret;
}
void cache_L2_w(hwaddr_t addr, size_t len, void *data)
{
	cache_L2_addr temp;
	temp.addr = addr;
	uint32_t tag = temp.tag;
	uint32_t set = temp.set;
	uint32_t block = temp.block;
	int i, pos = -1;
	for (i = 0; i < NR_LINE; i++)
		if (cache_L2[set][i].tag == tag && cache_L2[set][i].valid_bit == 1)
		{
			memcpy(cache_L2[set][i].data + block, data, len);
			cache_L2[set][i].dirty_bit = 1;
			return;
		}
		else
		{
			if (cache_L2[set][i].valid_bit == 0)
				pos = i;
		}
	uint32_t line = cache_L2_update(addr ^ block, pos);
	memcpy(cache_L2[set][line].data + block, data, len);
	cache_L2[set][line].dirty_bit = 1;
}
void cache_L2_write(hwaddr_t addr, size_t len, uint32_t data)
{
	uint32_t offset = addr & (NR_BLOCK - 1);
	union {
		uint8_t temp[4];
		uint32_t ret;
	}buf;
	buf.ret = data;
	if (offset + len > NR_BLOCK)
	{
		cache_L2_w(addr, NR_BLOCK - offset, buf.temp);
		cache_L2_w((addr ^ offset) + NR_BLOCK, len - (NR_BLOCK - offset), buf.temp + NR_BLOCK - offset);
	}
	else
		cache_L2_w(addr, len, buf.temp);
}

