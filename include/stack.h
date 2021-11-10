#ifndef _STACK_H_
#define _STACK_H_


typedef struct __M_stack_t__ M_stack_t;

M_stack_t* M_stack_make();
void M_stack_free(M_stack_t* stack);

void M_stack_push(M_stack_t* stack, void* elem);

/* returns the item but doesn't remove it */
void* M_stack_peak(M_stack_t* stack);

/* returns the item and remove it */
void* M_stack_pop(M_stack_t* stack);


#endif /* stack_h */