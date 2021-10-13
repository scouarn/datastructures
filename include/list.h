#ifndef _LIST_H_
#define _LIST_H_

typedef struct __M_list_t__ M_list_t;

M_list_t* M_list_make();
void M_list_free (M_list_t* list);
void M_list_print(M_list_t* list);

#endif //list_h