uint32_t alu(uint32_t a, uint32_t b, uint8_t type, uint32_t op)
{
	uint32_t ret = 0;
	if (type)  //arithmetic
	{
		if (op)
			b = ~b + 1;
		ret = a + b + cpu.cf;
		#if DATA_BYPE == 1
			ret = (uint8_t)ret;
		#endif
		#if DATA_BYPE == 2
			ret = (uint16_t)ret;
		#endif
		cpu.zf = ret == 0;
		cpu.sf = ret >> 31;
		cpu.pf = !(((ret >> 1) ^ (ret >> 2) ^ (ret >> 4)) & 1);
		cpu.of = (a >> 31) == (b >> 31) && ((a >> 31) != cpu.sf);
		cpu.cf ^= ret < a || (ret == a && cpu.cf);
	}
	else  //logic
	{
		if (op == 1)
			ret = a & b;
		if (op == 2)
			ret = a | b;
		cpu.zf = ret == 0;
		cpu.cf = 0;
		cpu.of = 0;
		cpu.pf = !(((ret >> 1) ^ (ret >> 2) ^ (ret >> 4)) & 1);
		cpu.sf = ret >> 31;
	}
	return ret;
}
