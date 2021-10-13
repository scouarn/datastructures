#ifndef _MATRIX_H_
#define _MATRIX_H_

typedef struct __M_mat_t__ M_mat_t;
typedef struct __M_vec_t__ M_vec_t;

M_vec_t* M_vec_make(int dim);
M_mat_t* M_mat_make(int rows, int cols);

void M_vec_free(M_vec_t* vec);
void M_mat_free(M_mat_t* mat);

void M_vec_print(M_vec_t* vec);
void M_mat_print(M_mat_t* mat);


double M_vec_dot   (M_vec_t* u, M_vec_t* v);
double M_vec_normsq(M_vec_t* vec);
double M_vec_norm  (M_vec_t* vec);

double M_mat_trace (M_mat_t* mat);
double M_mat_det   (M_mat_t* mat);


void M_vec_copy (M_vec_t* dst, M_vec_t* src);
void M_vec_add  (M_vec_t* dst, M_vec_t* u, M_vec_t* v);
void M_vec_scale(M_vec_t* dst, M_vec_t* vec, double a);

void M_extract_row(M_vec_t* dst, M_mat_t* mat);
void M_extract_col(M_vec_t* dst, M_mat_t* mat);


void M_mat_copy (M_mat_t* dst, M_mat_t* src);
void M_mat_add  (M_mat_t* dst, M_mat_t* a, M_mat_t* b);
void M_mat_scale(M_mat_t* dst, M_mat_t* mat, double a);


void M_mat_transpose(M_mat_t* dst, M_mat_t* mat);
void M_mat_invert   (M_mat_t* dst, M_mat_t* mat);
void M_linsolve	    (M_mat_t* dst, M_mat_t* mat, M_mat_t* vec);


void M_mat_ab  (M_mat_t* dst, M_mat_t* a, M_mat_t* b);
void M_mat_aTb (M_mat_t* dst, M_mat_t* a, M_mat_t* b);
void M_mat_abT (M_mat_t* dst, M_mat_t* a, M_mat_t* b);
void M_mat_aTbT(M_mat_t* dst, M_mat_t* a, M_mat_t* b);
#define M_mat_mul M_mat_ab


#endif //matrix_h