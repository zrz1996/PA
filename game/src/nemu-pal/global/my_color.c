#include "_common.h"
#include "my_color.h"
static BYTE color_shift(BYTE rel, SHORT iColorShift)
{
	BYTE b = (rel & 0x0F);
	if ((INT)b + iColorShift > 0x0F)
	{
		b = 0x0F;
	}
	else if ((INT)b + iColorShift < 0)
	{
		b = 0;
	}
	else
	{
		b += iColorShift;
	}

	return b | (rel & 0xF0);
}
BYTE color_table[256];
void make_color_table(SHORT iColorShift)
{
	int i;
	if (iColorShift != 0x7fff)
	{
		for (i = 0; i < 256; i++)
			color_table[i] = color_shift(i, iColorShift);
	}
}
