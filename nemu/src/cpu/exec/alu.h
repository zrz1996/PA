#define alu(a, b, type, op) \
({\
 	DATA_TYPE s1 = (a); \
 	DATA_TYPE s2 = (b); \
	DATA_TYPE _type = (type); \
 	DATA_TYPE _op = (op); \
 	uint32_t ret = 0; \
 	uint32_t size = DATA_BYTE * 8; \
	if (_type) \
	{\
		if (_op) \
			s2 = ~s2 + 1; \
		ret = (DATA_TYPE)(s1 + s2 + cpu.cf); \
		cpu.zf = ret == 0; \
		cpu.sf = ret >> size; \
		cpu.pf = !(((ret >> 1) ^ (ret >> 2) ^ (ret >> 4)) & 1); \
		cpu.of = (s1 >> size) == (s2 >> size) && ((s1 >> size) != cpu.sf); \
		cpu.cf ^= (ret < s1 || (ret == s1 && cpu.cf)) ^ _op; \
	}\
	else \
	{\
		if (_op == 1) \
			ret = s1 & s2; \
		if (_op == 2) \
			ret = s1 | s2; \
		cpu.zf = ret == 0; \
		cpu.cf = 0; \
		cpu.of = 0; \
		cpu.pf = !(((ret >> 1) ^ (ret >> 2) ^ (ret >> 4)) & 1); \
		cpu.sf = ret >> 31; \
	}\
 	ret; \
})