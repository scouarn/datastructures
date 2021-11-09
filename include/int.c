#ifndef _INT_H_
#define _INT_H_

/* static size integer */

#include "utils.h"

typedef struct __M_int_t__ M_int_t;


M_int_t* M_int_make(long size, long init_value);
void M_int_free (M_int_t* num);
void M_int_print(M_int_t* num);

long M_int_ladd(M_int_t* res, M_int_t* a, long b);
long M_int_lsub(M_int_t* res, M_int_t* a, long b);
long M_int_lmul(M_int_t* res, M_int_t* a, long b);
long M_int_ldiv(M_int_t* res, M_int_t* a, long b);
long M_int_lmod(M_int_t* res, M_int_t* a, long b);


long M_int_cpy(M_int_t* res, M_int_t* num);
long M_int_add(M_int_t* res, M_int_t* a, M_int_t* b);
long M_int_sub(M_int_t* res, M_int_t* a, M_int_t* b);
long M_int_neg(M_int_t* res, M_int_t* num);
long M_int_mul(M_int_t* res, M_int_t* a, M_int_t* b);
long M_int_div(M_int_t* res, M_int_t* a, M_int_t* b);
long M_int_mod(M_int_t* res, M_int_t* a, M_int_t* b);



#endif /* int_h */