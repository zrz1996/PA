#include "cpu/exec/helper.h"
#include "../alu.h"

#define DATA_BYTE 1
#include "cmps-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "cmps-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "cmps-template.h"
#undef DATA_BYTE
/* for instruction encoding overloading */

make_helper_v(cmps)
