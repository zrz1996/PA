#include "cpu/exec/helper.h"

#define DATA_BYTE 2
#include "movsx-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "movsx-template.h"
#undef DATA_BYTE

/* for instruction encoding overloading */

make_helper_v(movsx_rm2r)
