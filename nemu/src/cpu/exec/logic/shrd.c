#include "cpu/exec/helper.h"

#define DATA_BYTE 1
#include "shrd-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "shrd-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "shrd-template.h"
#undef DATA_BYTE

/* for instruction encoding overloading */
make_helper_v(shrd_i)
make_helper_v(shrd_r2rm_cl)
