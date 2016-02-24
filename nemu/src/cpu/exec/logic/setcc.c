#include "cpu/exec/helper.h"

#define DATA_BYTE 1
#include "setcc-template.h"
#undef DATA_BYTE

/* for instruction encoding overloading */

/*
make_helper_v(sete_i)
make_helper_v(setbe_i)
make_helper_v(seta_i)
make_helper_v(setae_i)
make_helper_v(setc_i)
make_helper_v(setcxz_i)
make_helper_v(setecxz_i)
make_helper_v(setz_i)
make_helper_v(setg_i)
make_helper_v(setge_i)
make_helper_v(setl_i)
make_helper_v(setle_i)
make_helper_v(setna_i)
make_helper_v(setnae_i)
make_helper_v(setnb_i)
make_helper_v(setnbe_i)
make_helper_v(setnc_i)
make_helper_v(setne_i)
make_helper_v(setng_i)
make_helper_v(setnge_i)
make_helper_v(setnl_i)
make_helper_v(setnle_i)
make_helper_v(setno_i)
make_helper_v(setnp_i)
make_helper_v(setns_i)
make_helper_v(setnz_i)
make_helper_v(seto_i)
make_helper_v(setp_i)
make_helper_v(setpe_i)
make_helper_v(setpo_i)
make_helper_v(sets_i)
make_helper_v(setb_i)
*/
