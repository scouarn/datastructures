#include "list.h"
#include "errors.h"

#include <stdlib.h>
#include <stdio.h>

struct __M_list_t__ {
	void* data;
	struct __M_list_t__ *next;
	struct __M_list_t__ *prev;
};


M_list_t* M_list_make() {

	M_list_t* list = malloc(sizeof(M_list_t));
	list->next = NULL;
	list->prev = NULL;
	list->data = 0;

	return list;
}

M_list_t* M_list_fromArray(void* arr[], size_t len) {

	M_list_t *list, *tail, *newNode;
	size_t i;

	list = M_list_make();
	tail = list;

	for (i = 0; i < len; i++) {
		newNode = malloc(sizeof(M_list_t));

		tail->next = newNode;
		newNode->prev = tail;
		newNode->data = arr[i];

		tail = newNode;
	}

	return list;

}


void M_list_free(M_list_t* list) {

	M_list_t* head;
	list = M_list_head(list);

	while (list != NULL) {
		head = list;
		list = list->next;
		free(head);
	}

}

void M_list_print(const char* format, M_list_t* list) {
	list = M_list_head(list);

	printf("[");

	while (!M_list_isTail(list)) {
		printf(format, M_list_get(list));
		list = M_list_next(list);
	}

	printf("]\n");
}



bool M_list_isTail(M_list_t* list) {
	return list->next == NULL;
}

bool M_list_isHead(M_list_t* list) {
	return list->prev == NULL;
}

bool M_list_isEmpty(M_list_t* list) {
	return M_list_isHead(list) && M_list_isTail(list);
}


M_list_t* M_list_next(M_list_t* list) {

	M_assert(!M_list_isTail(list), "Tail.");
	return list->next;
}


M_list_t* M_list_prev(M_list_t* list) {

	M_assert(!M_list_isHead(list), "Tail.");
	return list->prev;
}


M_list_t* M_list_tail(M_list_t* list) {

	while (!M_list_isTail(list)) 
		list = M_list_next(list);

	return list;
}


M_list_t* M_list_head(M_list_t* list) {

	while (!M_list_isHead(list)) 
		list = M_list_prev(list);

	return list;
}


void* M_list_get(M_list_t* list) {

	M_assert(!M_list_isEmpty(list), "Empty list.");
	return list->data;
}


void M_list_set(M_list_t* list, void* elem) {

	M_assert(!M_list_isEmpty(list), "Empty list.");
	list->data = elem;
}


void M_list_push(M_list_t* list, void* elem) {

	M_list_t* newNode = malloc(sizeof(M_list_t));
	list = M_list_tail(list);

	list->next = newNode;
	newNode->prev = list;
	newNode->next = NULL;
	newNode->data = elem;
}


void* M_list_pop(M_list_t* list) {

	void* res;

	M_assert(!M_list_isEmpty(list), "Empty list.");

	list = M_list_tail(list);
	res  = M_list_get(list);

	list->prev->next = NULL;
	free(list);

	return res;
}



void M_list_add(M_list_t* list, void* elem) {
	
	M_list_t* newNode = malloc(sizeof(M_list_t));
	list = M_list_head(list);

	list->prev = newNode;
	newNode->next = list;
	newNode->prev = NULL;
	newNode->data = elem;
}


void* M_list_rem(M_list_t* list) {
	void* res;

	M_assert(!M_list_isEmpty(list), "Empty list.");

	list = M_list_head(list);
	res  = M_list_get(list);

	list->next->prev = NULL;
	free(list);
	
	return res;
}


void M_list_concat(M_list_t* l1, M_list_t* l2) {

	l1 = M_list_tail(l1);
	l2 = M_list_head(l2);

	l1->next = l2;
	l2->prev = l1;
}


size_t M_list_length(M_list_t* list) {

	int i = 0;

	for (i = 0; !M_list_isTail(list); i++)
		list = M_list_next(list);

	return i;
}

