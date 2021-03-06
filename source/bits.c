#include "bits.h"
#include <stdlib.h>

#define M_BITS_LEN (sizeof(M_bits_t) * 8)

M_bits_t* M_bits_alloc(M_uint_t nb_bits) {
	return (M_bits_t*) malloc(nb_bits / 8);
}

void M_bits_set(M_bits_t bits[], M_uint_t pos) {
	bits[pos/M_BITS_LEN] |= (M_bits_t)1 << (pos%M_BITS_LEN);	
}


void M_bits_reset (M_bits_t bits[], M_uint_t pos) {
	bits[pos/M_BITS_LEN] &= ~((M_bits_t)1 << (pos%M_BITS_LEN));
}


void M_bits_toggle(M_bits_t bits[], M_uint_t pos) {
	bits[pos/M_BITS_LEN] ^= (M_bits_t)1 << (pos%M_BITS_LEN);
}

void M_bits_data(M_bits_t bits[], M_uint_t pos, bool data) {
	M_bits_reset(bits, pos);
	if (data) M_bits_set(bits, pos);
}

bool M_bits_get(M_bits_t bits[], M_uint_t pos) {

	M_bits_t b = bits[pos/M_BITS_LEN];

	if (b & ((M_bits_t) 1 << pos)) {
		return true;
	}

	else  {
		return false;
	}

}

