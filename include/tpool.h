#ifndef _TPOOL_H_
#define _TPOOL_H_

#include <stdbool.h>
#include "utils.h"


typedef struct __M_tpool_t__ M_tpool_t;


M_tpool_t* M_tpool_make(M_uint_t nb_threads);
void M_tpool_free(M_tpool_t* pool);

/* will call func for each thread in the pool, has to be joined manually */
void M_tpool_call(M_tpool_t* pool, void (*func) (M_uint_t));
void M_tpool_join(M_tpool_t* pool);

/* will call func n times and return when everything is done */
void M_tpool_batch(M_tpool_t* pool, void (*func) (M_uint_t), M_uint_t n);





#endif /* tpool_h */