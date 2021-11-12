/* ADAPTED FROM DICT_STATIC_C */


#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define M_DICT_STATIC

typedef struct  { /* the used flag is the key... */
	const char* key;
	void*  val;
} _pair;


struct __M_dict_static_t__ {
	_pair *array;
	long size;
};


#include "dict.h"
#include "errors.h"



M_dict_t* M_dict_nmake(long size) {
	M_dict_t* table = malloc(sizeof(M_dict_t));
	
	table->array = calloc(size, sizeof(_pair));
	table->size = size;

	return table;
}

M_dict_t* M_dict_make() {
	M_dict_t* t = M_dict_nmake(M_DICT_DEFAULT_SIZE); 
	return t;
}


M_dict_t* M_dict_resize(M_dict_t* table, long size) {

	int i;
	M_dict_t* new_table = M_dict_nmake(size);

	for (i = 0; i < table->size; i++) {
		_pair* p = &(table->array[i]);

		if (p->key != NULL)
			M_dict_add(new_table, p->key, p->val);
	}

	M_dict_free(table);
	return new_table;	
}


void M_dict_free(M_dict_t* table) {
	free(table->array);
	free(table);
}


/* http://www.cse.yorku.ca/~oz/hash.html */
static long djb2(const char *str) {
    long hash = 5381;
    int c;

    while ( (c = *str++) )
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}


/* utility to find where a key is located */
static _pair* find(M_dict_t *table, const char* key) {

	int i;
	long index = djb2(key) % table->size;

	/* stop if the end of the table is reach or the key found */	
	i = index;

	while ( table->array[i].key != NULL
	   &&  0 != strcmp(table->array[i].key, key)) {

		i = (i+1) % table->size;

		if (i == index) return NULL; /* not found */
	}

	return &(table->array[i]);

}

void* M_dict_get(M_dict_t *table, const char* key) {

	_pair* p = find(table, key);

	/* not in table */
	if (p == NULL || p->key == NULL) {
		return NULL;
	} 

	return p->val;
}


bool M_dict_set(M_dict_t* table, const char* key, void* value) {

	_pair* p = find(table, key);

	/* not in table */
	if (p == NULL || p->key == NULL) {
		return false;
	} 

	p->val = value;

	return true;
}


bool M_dict_add(M_dict_t* table, const char* key, void* value) {

	_pair* p = find(table, key);

	/* table full or already in table */
	if (p == NULL || p->key != NULL) {
		return false;
	} 

	p->val = value;
	p->key = key;

	return true;
}


bool M_dict_rem(M_dict_t* table, const char* key) {

	_pair* p = find(table, key);
	
	/* not in table */
	if (p == NULL || p->key == NULL) {
		return false;
	} 

	p->key = NULL;

	return true;
}

bool M_dict_mem(M_dict_t* table, const char* key) {

	_pair* p = find(table, key);

	return p != NULL && p->key == NULL;
}

