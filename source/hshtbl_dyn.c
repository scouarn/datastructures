
#define M_HSHTBL_DEFAULT_SIZE 1024

#include <stdbool.h>

typedef struct __pair__ {
	long  key;
	void* val;
	struct __pair__ *next;
} _pair;


struct __M_hshtbl_dyn_t__ {
	_pair *array;
	long size;

};

#include "hshtbl.h"
#include "errors.h"



M_hshtbl_t* M_hshtbl_nmake(long size) {

	M_hshtbl_t* table = malloc(sizeof(M_hshtbl_t));
	
	table->array = calloc(size, sizeof(_pair));
	table->size = size;

	return table;
}


M_hshtbl_t* M_hshtbl_make() {
	return M_hshtbl_nmake(M_HSHTBL_DEFAULT_SIZE);
}

void M_hshtbl_free(M_hshtbl_t* table) {

	/* free lists*/
	int i;
	for (i = 0; i < table->size; i++) {
		_pair* temp;
		_pair* node = table->array[i].next;

		while (node != NULL) {
			temp = node;
			node = temp->next;
			free(temp);
		}
	}

	free(table->array);
	free(table);
}


M_hshtbl_t* M_hshtbl_resize(M_hshtbl_t* table, long size) {

	M_hshtbl_t* new_table = M_hshtbl_nmake(size);

	int i;
	for (i = 0; i < table->size; i++) {
		_pair* node = &(table->array[i]);

		while (node->next != NULL) {
			M_hshtbl_add(new_table, node->key, node->val);
			node = node->next;
		}

	}



	M_hshtbl_free(table);
	return new_table;
}


/* return the (unused) list tail if not found */
static _pair* find(M_hshtbl_t *table, long key) {

	_pair* node;
	long index = key % table->size;


	/* stop if the end of the list is reach or the key found */	
	node = &(table->array[index]);

	while (node->next != NULL
	    && node->key  != key) {

		node = node->next;
	}
	
	return node;
}


void* M_hshtbl_get(M_hshtbl_t *table, long key) {
	_pair* p = find(table, key);

	if (p->next == NULL) { /* if not in table */
		return NULL;
	}

	return p->val;
}


bool M_hshtbl_set(M_hshtbl_t* table, long key, void* value) {
	_pair* p = find(table, key);

	if (p->next == NULL) { /* if not in table */
		return false;
	}

	p->val = value;

	return true;
}


bool M_hshtbl_add(M_hshtbl_t* table, long key, void* value) {
	_pair* p = find(table, key);

	if (p->next != NULL) { /* if already in table */
		return false;
	}

	p->key = key;
	p->val = value;

	p->next = malloc(sizeof(_pair));
	p->next->next = NULL;

	return true;
}



bool M_hshtbl_rem(M_hshtbl_t* table, long key) {
	_pair* next;
	_pair* p = find(table, key);

	if (p->next == NULL) { /* if not in table */
		return false;
	}

	next = p->next;

	/* to delete p, replace p by p->next */
	p->key  = next->key;
	p->val  = next->val;
	p->next = next->next;

	free(next);

	return true;
}


bool M_hshtbl_mem(M_hshtbl_t* table, long key) {

	_pair* p = find(table, key);

	return p->next != NULL;

}
