#include "stack.h"
#include "errors.h"

#include <stdlib.h>

/* Just a linked list implementation... */

struct __M_stack_t__ {
	void* elem;
	struct __M_stack_t__ *next;
};


M_stack_t* M_stack_make() {
	M_stack_t* newNode = malloc(sizeof(M_stack_t));
	
	newNode->next = NULL;

	return newNode;
}

void M_stack_free(M_stack_t* stack) {
	M_stack_t* temp;

	while (stack != NULL) {
		temp = stack;
		stack = stack->next;
		free(temp);
	}

}

void M_stack_push(M_stack_t* stack, void* elem) {
	
	M_stack_t* newNode = malloc(sizeof(M_stack_t));

	newNode->elem = elem;
	newNode->next = stack->next;

	stack->next = newNode;

}

void* M_stack_peak(M_stack_t* stack) {

	M_assert(stack->next != NULL, "Can't access element from empty stack.");

	return stack->next->elem;
}

void* M_stack_pop(M_stack_t* stack) {

	void* res;
	M_stack_t* head;

	M_assert(stack->next != NULL, "Can't access element from empty stack.");

	head = stack->next;
	res  = head->elem;

	stack->next = head->next;

	free(head);

	return res;
}



