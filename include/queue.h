#ifndef _QUEUE_H_
#define _QUEUE_H_


typedef struct __M_queue_t__ M_queue_t;

M_queue_t* M_queue_make();
void M_queue_free(M_queue_t* queue);

void M_queue_push(M_queue_t* queue, void* elem);

/* returns the item but doesn't remove it */
void* M_queue_peak(M_queue_t* queue);

/* returns the item and remove it */
void* M_queue_pop(M_queue_t* queue);


#endif /* queue_h */