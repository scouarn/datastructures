
#include <stdlib.h>
#include "utils.h"
#include "errors.h"

typedef struct __pair__ {
	M_uint_t  key;
	void* val;
	struct __pair__ *next;
} _pair;


struct __M_hshtbl_dyn_t__ {
	_pair *array;
	M_uint_t size;

};


#include "hshtbl.h"


M_hshtbl_t* M_hshtbl_nmake(M_uint_t size) {

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
	M_uint_t i;
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


M_hshtbl_t* M_hshtbl_resize(M_hshtbl_t* table, M_uint_t size) {

	M_hshtbl_t* new_table = M_hshtbl_nmake(size);

	M_uint_t i;
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
static _pair* find(M_hshtbl_t *table, M_uint_t key) {

	_pair* node;
	M_uint_t index = key % table->size;


	/* stop if the end of the list is reach or the key found */	
	node = &(table->array[index]);

	while (node->next != NULL
	    && node->key  != key) {

		node = node->next;
	}
	
	return node;
}


void* M_hshtbl_get(M_hshtbl_t *table, M_uint_t key) {
	_pair* p = find(table, key);

	if (p->next == NULL) { /* if not in table */
		return NULL;
	}

	return p->val;
}


bool M_hshtbl_set(M_hshtbl_t* table, M_uint_t key, void* value) {
	_pair* p = find(table, key);

	if (p->next == NULL) { /* if not in table */
		return false;
	}

	p->val = value;

	return true;
}


bool M_hshtbl_add(M_hshtbl_t* table, M_uint_t key, void* value) {
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



bool M_hshtbl_rem(M_hshtbl_t* table, M_uint_t key) {
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



bool M_hshtbl_mem(M_hshtbl_t* table, M_uint_t key) {

	_pair* p = find(table, key);

	return p->next != NULL;

}
