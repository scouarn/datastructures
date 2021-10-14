#ifndef _LIST_H_
#define _LIST_H_

typedef struct __M_list_t__ M_list_t;


M_list_t* M_list_make();
void M_list_free (M_list_t* list);
void M_list_print(M_list_t* list);

void M_list_push		  (M_list_t* list, void* elem);
void M_list_unshift		  (M_list_t* list, void* elem);
void M_list_insert_after  (M_list_t* list, void* elem);
void M_list_insert_before (M_list_t* list, void* elem);
void M_list_include_after (M_list_t* list, M_list_t* sublist);
void M_list_include_before(M_list_t* list, M_list_t* sublist);


void* M_list_remove(M_list_t* list);
void* M_list_pop   (M_list_t* list);
void* M_list_shift (M_list_t* list);

M_list_t* M_list_next(M_list_t* list);
M_list_t* M_list_prev(M_list_t* list);



#endif //list_h