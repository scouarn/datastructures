#include "preint.h"
#include "errors.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define WIDTH 1
#define RADIX 256


struct __M_int_t__ {
	uint8_t* data;
	size_t size;
};


M_int_t* M_int_make(size_t size, uint64_t init_value) {
	
	M_int_t* num = malloc(sizeof(M_int_t));
	num->data = calloc(size, WIDTH);
	
	M_assert(num->data != NULL, "Couldn't allocate for large integer.");

	num->size = size;


	return num;
}



void M_int_free(M_int_t* num) {
	if (num->data)
		free(num->data);

	if (num)
		free(num);
}


void M_int_print(M_int_t* num) {
	
	size_t i;
	for (i = num->size-1; i >= 0; i-= WIDTH) 
		printf("%d", num->data[i]);
}


int M_int_cpy(M_int_t* res, M_int_t* a) {

	size_t i;
	for (i = 0; i < MIN(res->size, a->size); i+= WIDTH)
		res->data[i] = a->data[i]; 

	return 0;
}

int M_int_add(M_int_t* res, M_int_t* a, M_int_t* b) {
	return 0;
}

int M_int_sub(M_int_t* res, M_int_t* a, M_int_t* b) {
	return 0;
}

int M_int_mul(M_int_t* res, M_int_t* a, M_int_t* b) {
	return 0;
}

int M_int_div(M_int_t* res, M_int_t* a, M_int_t* b) {
	return 0;
}

int M_int_mod(M_int_t* res, M_int_t* a, M_int_t* b) {
	return 0;
}

int M_int_pow(M_int_t* res, M_int_t* n, M_int_t* p) {
	return 0;
}

int M_int_neg(M_int_t* res, M_int_t* num) {
	return 0;
}

int M_int_inv(M_int_t* res, M_int_t* num) {
	return 0;
}

int M_int_lsh(M_int_t* res, M_int_t* num) {
	return 0;
}

int M_int_rsh(M_int_t* res, M_int_t* num) {
	return 0;
}

int M_int_fct(M_int_t* res, M_int_t* num) {
	return 0;
}

int M_int_sqt(M_int_t* res, M_int_t* num) {
	return 0;
}
