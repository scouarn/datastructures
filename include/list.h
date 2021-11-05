#ifndef _LIST_H_
#define _LIST_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#define EMPTY_LIST NULL

/* In the functions of this module, the convention
 * is to pass a pointer to the head node of the list */

typedef struct __M_list_t__ {
	void* data;
	struct __M_list_t__ *next;
	struct __M_list_t__ *prev;
} M_list_t;


/* Creates a list with a single item in it,
 * it can also be done by adding or pushing 
 * to the EMPTY_LIST */
M_list_t* M_list_make(void* elem);

/* The size of the elements of arr must be sizeof(void*) */
M_list_t* M_list_fromArray(void* arr[], size_t len);

/* Free each node from the given node up to the tail */
void M_list_free (M_list_t* list);

/* Print with specified "printf" format for items */
void M_list_print(const char* format, M_list_t* list);

bool M_list_isTail(M_list_t* list);
bool M_list_isHead(M_list_t* list);

M_list_t* M_list_next(M_list_t* list);
M_list_t* M_list_prev(M_list_t* list);
M_list_t* M_list_tail(M_list_t* list);
M_list_t* M_list_head(M_list_t* list);

void* M_list_get(M_list_t* list);
void  M_list_set(M_list_t* list, void* elem);


/* To keep the passed list pointer pointing to its head,
 * a double pointer is passed so it can be changed when 
 * adding at the begining, or changing it to EMPTY_LIST 
 * in certain cases. 
 * Returning a new valid pointer is not practical since
 * other values are returned by pop et remove */

/* at the end */
void  M_list_push(M_list_t** pList, void* elem);
void* M_list_pop (M_list_t** list);

/* at the begining */
void  M_list_add(M_list_t** pList, void* elem);
void* M_list_rem(M_list_t** list);


/* l1 followed by l2 */
void M_list_concat(M_list_t* l1, M_list_t* l2);

/* assumes it is passed the head and count up to the tail */
size_t M_list_length(M_list_t* list);



#endif /* list_h */