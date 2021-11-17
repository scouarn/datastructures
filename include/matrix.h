#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "utils.h"

typedef double  M_scalar_t;
typedef M_scalar_t* M_mat_t;

M_mat_t* M_mat_make(M_uint_t rows, M_uint_t cols);
void M_mat_free(M_mat_t* mat);

/* if M_mat_free used on a matrix made with this function,
 * data will also be freeed. To avoid that just use free(mat). */
M_mat_t* M_mat_fromArray(double* data, M_uint_t rows, M_uint_t cols);

void M_mat_size(M_mat_t* mat, M_uint_t* rows, M_uint_t* cols);
void M_mat_print(const char* format, M_mat_t* mat);

void M_mat_zero(M_mat_t* dst);
void M_mat_unit(M_mat_t* dst);
void M_mat_copy (M_mat_t* dst, M_mat_t* src);
void M_mat_add  (M_mat_t* dst, M_mat_t* a, M_mat_t* b);
void M_mat_scale(M_mat_t* dst, M_mat_t* mat, double a);
void M_mat_trans(M_mat_t* dst, M_mat_t* mat);
void M_mat_mul(M_mat_t* dst, M_mat_t* a, M_mat_t* b);



#endif /* matrix_h */

