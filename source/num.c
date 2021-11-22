#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#include "utils.h"

#define BASE (((M_uint_t)UINT_MAX)+1)
typedef unsigned int radix_t;


struct __M_num_t__ {
	radix_t* data;
	M_uint_t size;
};

#include "num.h"

M_num_t* M_num_make(M_uint_t size) {
	M_num_t* num;

	size_t nbmemb = (1 + size) / sizeof(radix_t);

	num = malloc( sizeof(M_num_t) );
	num->data = calloc( nbmemb, sizeof(radix_t) );
	num->size = nbmemb;

	return num;

}


void M_num_free (M_num_t* num) {
	free(num->data);
	free(num);
}


/* number of significant digits */
static M_uint_t len(M_num_t* num) {
	M_uint_t i = num->size - 1;

	while (i > 0 && num->data[i] == 0) 
		i--;

	return 1+i;
}


void M_num_print(M_num_t* num) {
	M_uint_t i;


	for (i = len(num); i > 0; i--) {
		printf("%ld ", num->data[i-1]);
	}

	printf("\n");

}



void M_num_lcpy(M_num_t* num, M_uint_t n) {
	num->data[0] = n % BASE;
}

void M_num_ladd(M_num_t* res, M_num_t* a, M_uint_t b);
void M_num_lsub(M_num_t* res, M_num_t* a, M_uint_t b);
void M_num_lmul(M_num_t* res, M_num_t* a, M_uint_t b);
void M_num_ldiv(M_num_t* res, M_num_t* a, M_uint_t b);
void M_num_lmod(M_num_t* res, M_num_t* a, M_uint_t b);


void M_num_zero(M_num_t* res) {
	M_uint_t i;

	for (i = 0; i < res->size; i++)
		res->data[i] = 0;

}

void M_num_cpy(M_num_t* res, M_num_t* num) {
	M_uint_t i;

	for (i = 0; i < res->size && i < num->size; i++)
		res[i] = num[i];

}



void M_num_add(M_num_t* res, M_num_t* a, M_num_t* b) {
	M_uint_t i, r, c = 0;

	for (i = 0; i < res->size && i < a->size && i < b->size; i++) {

		r = c + a->data[i] + b->data[i];
		c = r >= BASE;
		res->data[i] = r; /* modulo by overflow */
	}

}


void M_num_sub(M_num_t* res, M_num_t* a, M_num_t* b) {
	M_uint_t i, r, c = 0;

	for (i = 0; i < res->size && i < a->size && i < b->size; i++) {

		r = BASE + a->data[i] - b->data[i] - c;
		c = r < BASE;
		res->data[i] = r; /* modulo by overflow */
	}


}

static void dmul(M_num_t* res, M_num_t* num, M_uint_t d);
void M_num_mul(M_num_t* res, M_num_t* a, M_num_t* b);
void M_num_div(M_num_t* res, M_num_t* a, M_num_t* b);
void M_num_mod(M_num_t* res, M_num_t* a, M_num_t* b);
