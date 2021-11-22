#ifndef _NUM_H_
#define _NUM_H_

/* static size integer */

#include "utils.h"

typedef struct __M_num_t__ M_num_t;
typedef enum {M_OK, M_CARRY, M_TOOSHORT} M_num_err;


M_num_t* M_num_make(M_uint_t size);
void M_num_free (M_num_t* num);
void M_num_print(M_num_t* num);

void M_num_lcpy(M_num_t* num, M_uint_t n);

void M_num_zero(M_num_t* res);
void M_num_cpy(M_num_t* res, M_num_t* num);
void M_num_add(M_num_t* res, M_num_t* a, M_num_t* b);
void M_num_sub(M_num_t* res, M_num_t* a, M_num_t* b);
void M_num_mul(M_num_t* res, M_num_t* a, M_num_t* b);
void M_num_div(M_num_t* res, M_num_t* a, M_num_t* b);
void M_num_mod(M_num_t* res, M_num_t* a, M_num_t* b);



#endif /* num_h */