#ifndef _DINT_H_
#define _DINT_H_

/* dynamic size integer */

typedef struct __M_dint_t__ M_dint_t;

#include "utils.h"

M_dint_t* M_dint_make(long init_value);
void M_dint_free (M_dint_t* num);
void M_dint_print(M_dint_t* num);

long M_dint_add(M_dint_t* res, M_dint_t* a, long b);
long M_dint_sub(M_dint_t* res, M_dint_t* a, long b);
long M_dint_mul(M_dint_t* res, M_dint_t* a, long b);
long M_dint_div(M_dint_t* res, M_dint_t* a, long b);
long M_dint_mod(M_dint_t* res, M_dint_t* a, long b);


long M_dint_cpy(M_dint_t* res, M_dint_t* num);
long M_dint_add(M_dint_t* res, M_dint_t* a, M_dint_t* b);
long M_dint_sub(M_dint_t* res, M_dint_t* a, M_dint_t* b);
long M_dint_neg(M_dint_t* res, M_dint_t* num);
long M_dint_mul(M_dint_t* res, M_dint_t* a, M_dint_t* b);
long M_dint_div(M_dint_t* res, M_dint_t* a, M_dint_t* b);
long M_dint_mod(M_dint_t* res, M_dint_t* a, M_dint_t* b);



#endif /* dint_h */