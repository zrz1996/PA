#include "FLOAT.h"
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

FLOAT F_mul_F(FLOAT a, FLOAT b) {
	return ((uint64_t)a * b) >> 16;
}

#define sign(x) (x) >= 0 ? 1 : -1

FLOAT F_div_F(FLOAT a, FLOAT b) {
	int s = sign(a) * sign(b);
	a = a > 0 ? a : -a;
	b = b > 0 ? b : -b;
	int ret = a / b;
	a %= b;
	int i;
	for (i = 0; i < 16; i++)
	{
		a <<= 1;
		if (a > b)
		{
			ret = (ret << 1) | 1;
			a -= b;
		}
		else
			ret <<= 1;
	}
	return ret * s;
}

FLOAT f2F(float a) {
	uint32_t A = *(uint32_t *)&a;
	uint32_t s = A & 0x80000000;
	int e = ((A >> 23) & 0xff) - 150;
	uint32_t f = A & 0x7fffff;
	f += 1 << 23;
	e += 16;
	if (e > 0)
		f <<= e;
	else
		f >>= -e;
	return s ? -f : f;
}

FLOAT Fabs(FLOAT a) {
	return a >= 0 ? a : -a;
}

FLOAT sqrt(FLOAT x) {
	FLOAT dt, t = int2F(2);

	do {
		dt = F_div_int((F_div_F(x, t) - t), 2);
		t += dt;
	} while(Fabs(dt) > f2F(1e-4));

	return t;
}

FLOAT pow(FLOAT x, FLOAT y) {
	/* we only compute x^0.333 */
	FLOAT t2, dt, t = int2F(2);

	do {
		t2 = F_mul_F(t, t);
		dt = (F_div_F(x, t2) - t) / 3;
		t += dt;
	} while(Fabs(dt) > f2F(1e-4));

	return t;
}

