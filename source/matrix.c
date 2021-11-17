#include "matrix.h"
#include "errors.h"
#include <stdlib.h>

/* safe conversion */
static M_scalar_t* int_to_ptr(M_uint_t n) {

	union {
		M_uint_t i;
		M_scalar_t* ptr;
	} box;

	box.i = n;

	return box.ptr;
}

static M_uint_t ptr_to_int(M_scalar_t* p) {

	union {
		M_uint_t i;
		M_scalar_t* ptr;
	} box;

	box.ptr = p;

	return box.i;
}


M_mat_t* M_mat_make(M_uint_t rows, M_uint_t cols) {

	M_uint_t i;
	M_mat_t* mat = malloc( (rows+2) * sizeof(M_scalar_t*) );
	
	/* hide size in the first two cells of array */
	mat += 2;
	mat[-1] = int_to_ptr(rows);
	mat[-2] = int_to_ptr(cols);

	mat[0] = malloc( rows * cols * sizeof(M_uint_t) );

	for (i = 1; i < rows; i++)
		mat[i] = mat[0] + i*cols;

	return (M_mat_t*)mat;
}

M_mat_t* M_mat_fromArray(M_scalar_t* data, M_uint_t rows, M_uint_t cols) {

	M_uint_t i;
	M_mat_t* mat = malloc( (rows+2) * sizeof(M_scalar_t*) );
	
	/* hide size in the first two cells of array */
	mat += 2;
	mat[-1] = int_to_ptr(rows);
	mat[-2] = int_to_ptr(cols);

	mat[0] = data;

	for (i = 1; i < rows; i++)
		mat[i] = data + i*cols;

	return (M_mat_t*)mat;
}


void M_mat_free(M_mat_t* mat) {
	free(mat[0]);
	free(mat-2);
}

void M_mat_size(M_mat_t* mat, M_uint_t* rows, M_uint_t* cols) {
	*rows = ptr_to_int(mat[-1]);
	*cols = ptr_to_int(mat[-2]);
}


void M_mat_print(const char* format, M_mat_t* mat) {
	M_uint_t i, j, rows, cols;
	M_mat_size(mat, &rows, &cols);

	for (i = 0; i < rows; i++) {

		printf("[ ");

		for (j = 0; j < cols; j++)
			printf(format, mat[i][j]);

		printf(" ]\n");
	}

}

void M_mat_zero(M_mat_t* mat) {
	M_uint_t i, j, rows, cols;
	M_mat_size(mat, &rows, &cols);

	for (i = 0; i < rows; i++)
	for (j = 0; j < cols; j++)
		mat[i][j] = 0.0;
}


void M_mat_unit(M_mat_t* mat) {
	M_uint_t i, rows, cols;
	M_mat_size(mat, &rows, &cols);

	M_assert(rows == cols, "Identity matrix must be square.");

	for (i = 0; i < rows; i++)
		mat[i][i] = 1.0;
}


void M_mat_copy(M_mat_t* dst, M_mat_t* src) {
	M_uint_t i, j, src_r, src_c, dst_r, dst_c;
	M_mat_size(src, &src_r, &src_c);
	M_mat_size(dst, &dst_r, &dst_c);

	M_assert(src_r == dst_r && src_c == dst_c, 
		"dst and src must be same size.");

	for (i = 0; i < dst_r; i++)
	for (j = 0; j < dst_c; j++)
		dst[i][j] = src[i][j];
}



void M_mat_add(M_mat_t* dst, M_mat_t* a, M_mat_t* b) {
	M_uint_t i, j, a_r, a_c, b_r, b_c, dst_r, dst_c;
	M_mat_t* tmp;

	M_mat_size(a, &a_r, &a_c);
	M_mat_size(b, &b_r, &b_c);
	M_mat_size(dst, &dst_r, &dst_c);

	M_assert(a_r == dst_r && a_c == dst_c, 
		"dst and a must be same size.");

	M_assert(b_r == dst_r && b_c == dst_c, 
		"dst and b must be same size.");


	if (dst == a || dst == b)
		tmp = M_mat_make(dst_r, dst_c);
	else
		tmp = dst;


	for (i = 0; i < dst_r; i++)
	for (j = 0; j < dst_c; j++)
		tmp[i][j] = a[i][j] + b[i][j];


	if (dst == a || dst == b) {
		M_mat_copy(dst, tmp);
		M_mat_free(tmp);
	}

}


void M_mat_scale(M_mat_t* dst, M_mat_t* src, double a) {
	M_uint_t i, j, src_r, src_c, dst_r, dst_c;
	M_mat_size(src, &src_r, &src_c);
	M_mat_size(dst, &dst_r, &dst_c);

	M_assert(src_r == dst_r && src_c == dst_c, 
		"dst and src must be same size.");

	for (i = 0; i < dst_r; i++)
	for (j = 0; j < dst_c; j++)
		dst[i][j] = a * src[i][j];
}


void M_mat_trans(M_mat_t* dst, M_mat_t* src) {
	M_uint_t i, j, src_r, src_c, dst_r, dst_c;
	M_mat_t* tmp;

	M_mat_size(src, &src_r, &src_c);
	M_mat_size(dst, &dst_r, &dst_c);

	M_assert(src_r == dst_c && src_c == dst_r, 
		"Invalid dimensions for transposition.");


	if (dst == src)
		tmp = M_mat_make(dst_r, dst_c);
	else
		tmp = dst;


	for (i = 0; i < dst_r; i++)
	for (j = 0; j < dst_c; j++)
		tmp[i][j] = src[j][i];


	if (dst == src) {
		M_mat_copy(dst, tmp);
		M_mat_free(tmp);
	}

}


void M_mat_mul(M_mat_t* dst, M_mat_t* a, M_mat_t* b) {
	M_uint_t i, j, k, a_r, a_c, b_r, b_c, dst_r, dst_c;
	M_mat_t* tmp;

	M_mat_size(a, &a_r, &a_c);
	M_mat_size(b, &b_r, &b_c);
	M_mat_size(dst, &dst_r, &dst_c);

	M_assert(a_c == b_r, 
		"a must have as much cols as b has rows.");

	M_assert(dst_r == a_r, 
		"dst must have as much rows as a.");

	M_assert(dst_c == b_c, 
		"dst must have as much cols as b.");


	if (dst == a || dst == b)
		tmp = M_mat_make(dst_r, dst_c);
	else
		tmp = dst;


	for (i = 0; i < dst_r; i++)
	for (j = 0; j < dst_c; j++) {

		tmp[i][j] = 0;
		for (k = 0; k < a_c; k++)
			tmp[i][j] += a[i][k] * b[k][j];
	}


	if (dst == a || dst == b) {
		M_mat_copy(dst, tmp);
		M_mat_free(tmp);
	}

}