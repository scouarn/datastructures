
#include <stdint.h>
#include <stdlib.h>

#include "bits.h"


void M_bits_set(M_bits_t bits[], int pos) {
	bits[pos/M_BITS_LEN] |= (M_bits_t)1 << (pos%M_BITS_LEN);	
}


void M_bits_reset (M_bits_t bits[], int pos) {
	bits[pos/M_BITS_LEN] &= ~((M_bits_t)1 << (pos%M_BITS_LEN));
}


void M_bits_toggle(M_bits_t bits[], int pos) {
	bits[pos/M_BITS_LEN] ^= (M_bits_t)1 << (pos%M_BITS_LEN);
}

void M_bits_data(M_bits_t bits[], int pos, bool data) {
	M_bits_reset(bits, pos);
	if (data) M_bits_set(bits, pos);
}

bool M_bits_get(M_bits_t bits[], int pos) {

	M_bits_t b = bits[pos/M_BITS_LEN];

	if (b & ((M_bits_t) 1 << pos)) {
		return true;
	}

	else  {
		return false;
	}

}

