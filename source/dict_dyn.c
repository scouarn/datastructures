
#define M_DICT_DEFAULT_SIZE 1024

#include <stdbool.h>
#include <string.h>
#include "dict.h"
#include "errors.h"


typedef struct __pair__ {
	const char* key;
	void* val;
	struct __pair__ *next;
} _pair;


struct __M_dict_dyn_t__ {
	_pair *array;
	M_uint_t size;

};




M_dict_t* M_dict_nmake(M_uint_t size) {

	M_dict_t* table = malloc(sizeof(M_dict_t));
	
	table->array = calloc(size, sizeof(_pair));
	table->size = size;

	return table;
}


M_dict_t* M_dict_make() {
	return M_dict_nmake(M_DICT_DEFAULT_SIZE);
}

void M_dict_free(M_dict_t* table) {

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


M_dict_t* M_dict_resize(M_dict_t* table, M_uint_t size) {

	M_dict_t* new_table = M_dict_nmake(size);

	M_uint_t i;
	for (i = 0; i < table->size; i++) {
		_pair* node = &(table->array[i]);

		while (node->next != NULL) {
			M_dict_add(new_table, node->key, node->val);
			node = node->next;
		}

	}



	M_dict_free(table);
	return new_table;
}



/* http://www.cse.yorku.ca/~oz/hash.html */
static M_uint_t djb2(const char *str) {
    M_uint_t hash = 5381;
    int c;

    while ( (c = *str++) )
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

/* return the (unused) list tail if not found */
static _pair* find(M_dict_t *table, const char* key) {

	_pair* node;
	M_uint_t index = djb2(key) % table->size;

	/* stop if the end of the list is reach or the key found */	
	node = &(table->array[index]);

	while (node->next != NULL
		&& node->key  != NULL
	    && 0 != strcmp(node->key, key)) {

		node = node->next;
	}
	
	return node;
}


void* M_dict_get(M_dict_t *table, const char* key) {
	_pair* p = find(table, key);

	if (p->next == NULL) { /* if not in table */
		return NULL;
	}

	return p->val;
}


bool M_dict_set(M_dict_t* table, const char* key, void* value) {
	_pair* p = find(table, key);

	if (p->next == NULL) { /* if not in table */
		return false;
	}

	p->val = value;

	return true;
}


bool M_dict_add(M_dict_t* table, const char* key, void* value) {
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



bool M_dict_rem(M_dict_t* table, const char* key) {
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


bool M_dict_mem(M_dict_t* table, const char* key) {

	_pair* p = find(table, key);

	return p->next != NULL;

}
