#include "list.h"
#include "errors.h"

#include <stdlib.h>
#include <stdio.h>


M_list_t* M_list_make(void* elem) {

	M_list_t* list = malloc(sizeof(M_list_t));
	list->next = NULL;
	list->prev = NULL;
	list->data = elem;

	return list;
}

M_list_t* M_list_fromArray(void* arr[], size_t len) {

	M_list_t *list, *tmp, *newNode;
	size_t i;

	if (len == 0) {
		return NULL;
	}
	else {

		list = M_list_make(arr[0]);
		tmp = list;

		for (i = 1; i < len; i++) {
			newNode = M_list_make(arr[i]);
			tmp->next = newNode;
			tmp = newNode;
		}

	}

	return list;

}


void M_list_free(M_list_t* list) {

	M_list_t* walk = list;

	while (walk != NULL) {
		M_list_t* temp = M_list_next(walk);
		free(walk);
		walk = temp;
	}
}

void M_list_print(const char* format, M_list_t* list) {
	printf("[");

	while (list != NULL) {
		printf(format, list->data);
		list = M_list_next(list);
	}

	printf("]\n");
}



bool M_list_isTail(M_list_t* list) {
	return M_list_next(list) == EMPTY_LIST;
}

bool M_list_isHead(M_list_t* list) {
	return M_list_prev(list) == EMPTY_LIST;
}


M_list_t* M_list_next(M_list_t* list) {

	if (list == EMPTY_LIST) {
		M_error("Asking for the next element of in an empty list.");
	}

	return list->next;
}


M_list_t* M_list_prev(M_list_t* list) {

	if (list == EMPTY_LIST) {
		M_error("Asking for the previous element of in an empty list.");
	}
	
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
	return list->data;
}


void M_list_set(M_list_t* list, void* elem) {
	list->data = elem;
}


void M_list_push(M_list_t** pList, void* elem) {

	M_list_t* tmp;

	M_assert(pList != NULL, "You have to give a valid pointer to a list pointer !");


	/* add to an empty list */
	if (*pList == EMPTY_LIST) {
		*pList = M_list_make(elem);
	}

	/* add to a list which as a memory location */
	else {
		tmp = M_list_tail(*pList);
		tmp->next = M_list_make(elem);
	}

	
}


void* M_list_pop(M_list_t** pList) {
	void* res;
	M_list_t* tmp;

	M_assert(pList != NULL, "You have to give a valid pointer to a list pointer !");


	if (*pList == EMPTY_LIST) {
		M_error("Popping from empty list.");
	}

	/* remove element */
	else {
		tmp = M_list_tail(*pList);
		res = M_list_get(tmp);

		if (tmp->prev != EMPTY_LIST) {
			tmp = M_list_prev(tmp);
			free(tmp->next);
			tmp->next = NULL;
		}

		/* special case if it was the last item */
		else {
			*pList = NULL;
			free(tmp);
		}
	}

	return res;
}



void M_list_add(M_list_t** pList, void* elem) {
	
	M_list_t *tmp;

	M_assert(pList != NULL, "You have to give a valid pointer to a list pointer !");

	tmp = *pList;
	
	/* add at the begining */
	*pList = M_list_make(elem);
	(*pList)->next = tmp;
	tmp->prev = (*pList);
	
}


void* M_list_rem(M_list_t** pList) {
	void* res;
	M_list_t *tmp;

	M_assert(pList != NULL, "You have to give a valid pointer to a list pointer !");

	if (*pList == EMPTY_LIST) {
		M_error("Removing from empty list.");
	}
	else {
		tmp = *pList;
		res = M_list_get(*pList);

		/* remove the first element */
		*pList = (*pList)->next;
		(*pList)->prev = NULL;
		free(tmp);
	}

	return res;
}


void M_list_concat(M_list_t* l1, M_list_t* l2) {

	l1 = M_list_tail(l1);
	l1->next = l2;
	l2->prev = l1;
}


size_t M_list_length(M_list_t* list) {

	int i;
	for (i = 0; !M_list_isTail(list); i++)
		list = M_list_next(list);

	return i;
}

