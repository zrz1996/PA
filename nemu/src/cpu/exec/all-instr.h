#include "prefix/prefix.h"

#include "data-mov/mov.h"
#include "data-mov/xchg.h"
#include "data-mov/leave.h"
#include "data-mov/lea.h"
#include "data-mov/movsx.h"
#include "data-mov/movzx.h"
#include "data-mov/cltq.h"
#include "data-mov/cwtl.h"
#include "data-mov/cmovcc.h"

#include "arith/dec.h"
#include "arith/inc.h"
#include "arith/neg.h"
#include "arith/imul.h"
#include "arith/mul.h"
#include "arith/idiv.h"
#include "arith/div.h"
#include "arith/sub.h"
#include "arith/sbb.h"
#include "arith/add.h"
#include "arith/adc.h"
#include "arith/cmp.h"

#include "logic/and.h"
#include "logic/or.h"
#include "logic/not.h"
#include "logic/xor.h"
#include "logic/sar.h"
#include "logic/shl.h"
#include "logic/shr.h"
#include "logic/shrd.h"
#include "logic/shld.h"
#include "logic/test.h"
#include "logic/setcc.h"

#include "string/rep.h"
#include "string/movs.h"
#include "string/stos.h"
#include "string/cmps.h"

#include "misc/misc.h"
#include "misc/cld.h"
#include "misc/std.h"
#include "special/special.h"

#include "control/call.h"
#include "control/push.h"
#include "control/jmp.h"
#include "control/ret.h"
#include "control/jcc.h"
#include "control/pop.h"
#include "control/pusha.h"
#include "control/popa.h"

#include "sys/lgdt.h"
#include "sys/lidt.h"
#include "sys/in.h"
#include "sys/out.h"
