#ifndef _BITS_H_

/* generalization of bit manipulation for number of bits
 * that doesn't fit in a single int */

#include <stdint.h>
#include <stdbool.h>
#include "utils.h"

typedef uint32_t M_bits_t;

M_bits_t* M_bits_alloc(M_uint_t nb_bits);
void M_bits_set   (M_bits_t bits[], M_uint_t pos);
void M_bits_reset (M_bits_t bits[], M_uint_t pos);
void M_bits_toggle(M_bits_t bits[], M_uint_t pos);
void M_bits_data  (M_bits_t bits[], M_uint_t pos, bool data);
bool M_bits_get   (M_bits_t bits[], M_uint_t pos);



#define _BITS_H_

#endif /* bits_h */