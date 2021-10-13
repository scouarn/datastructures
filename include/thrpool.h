#ifndef _THRPOOL_H_
#define _THRPOOL_H_

typedef struct __M_thrpool_t__ M_thrpool_t;

M_thrpool_t* M_thrpool_make();
void M_thrpool_free (M_thrpool_t* pool);
void M_thrpool_print(M_thrpool_t* pool);

#endif //thrpool_h