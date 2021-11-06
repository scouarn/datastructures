#ifndef _BIGINT_H_
#define _BIGINT_H_

typedef struct __M_int_t__ M_int_t;

#include <stdint.h>
#include "utils.h"

M_int_t* M_int_make(uint64_t size, uint64_t init_value);
void M_int_free (M_int_t* num);
void M_int_print(M_int_t* num);

int M_int_add(M_int_t* res, M_int_t* a, M_int_t* b);
int M_int_sub(M_int_t* res, M_int_t* a, M_int_t* b);
int M_int_mul(M_int_t* res, M_int_t* a, M_int_t* b);
int M_int_div(M_int_t* res, M_int_t* a, M_int_t* b);
int M_int_mod(M_int_t* res, M_int_t* a, M_int_t* b);
int M_int_pow(M_int_t* res, M_int_t* n, M_int_t* p);
int M_int_cpy(M_int_t* res, M_int_t* num);
int M_int_neg(M_int_t* res, M_int_t* num);
int M_int_inv(M_int_t* res, M_int_t* num);
int M_int_lsh(M_int_t* res, M_int_t* num);
int M_int_rsh(M_int_t* res, M_int_t* num);
int M_int_fct(M_int_t* res, M_int_t* num);
int M_int_sqt(M_int_t* res, M_int_t* num);



#endif /* bigint_h */