#include "queue.h"
#include "errors.h"

#include <stdlib.h>

struct __M_queue_t__ {
	void* elem;
	struct __M_queue_t__ *next;
	struct __M_queue_t__ *tail;
};


M_queue_t* M_queue_make() {
	M_queue_t* queue = malloc(sizeof(M_queue_t));
	
	queue->next = NULL;
	queue->tail = queue; /* only valid for the node pointed by the user's queue pointer */

	return queue;
}

void M_queue_free(M_queue_t* queue) {
	M_queue_t* temp;

	while (queue != NULL) {
		temp = queue;
		queue = queue->next;
		free(temp);
	}

}

void M_queue_push(M_queue_t* queue, void* elem) {
	/* push at the tail of the list */

	M_queue_t* newNode = malloc(sizeof(M_queue_t));

	newNode->elem = elem;
	newNode->next = NULL;

	queue->tail->next = newNode;
	queue->tail = newNode;

}

void* M_queue_peak(M_queue_t* queue) {

	M_assert(queue->next != NULL, "Can't access element from empty queue.");

	return queue->next->elem;
}

void* M_queue_pop(M_queue_t* queue) {
	/* pop from the head */

	void* res;
	M_queue_t* head;

	M_assert(queue->next != NULL, "Can't access element from empty queue.");

	head = queue->next;
	res  = head->elem;

	queue->next = head->next;

	if (queue->tail == head)
		queue->tail = queue;

	free(head);

	return res;
}



