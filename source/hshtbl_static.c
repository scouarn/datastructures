

#include <stdlib.h>
#include <stdbool.h>
#include "utils.h"

#define M_HSHTBL_STATIC

typedef struct  {
	M_uint_t key;
	void*  val;
	bool  used;
} _pair;


struct __M_hshtbl_static_t__ {
	_pair *array;
	M_uint_t size;
};


#include "hshtbl.h"
#include "errors.h"



M_hshtbl_t* M_hshtbl_nmake(M_uint_t size) {
	M_hshtbl_t* table = malloc(sizeof(M_hshtbl_t));
	
	table->array = calloc(size, sizeof(_pair));
	table->size = size;

	return table;
}

M_hshtbl_t* M_hshtbl_make() {
	M_hshtbl_t* t = M_hshtbl_nmake(M_HSHTBL_DEFAULT_SIZE); 
	return t;
}


M_hshtbl_t* M_hshtbl_resize(M_hshtbl_t* table, M_uint_t size) {

	M_uint_t i;
	M_hshtbl_t* new_table = M_hshtbl_nmake(size);

	for (i = 0; i < table->size; i++) {
		_pair* p = &(table->array[i]);

		if (p->used == true)
			M_hshtbl_add(new_table, p->key, p->val);
	}

	M_hshtbl_free(table);
	return new_table;	
}


void M_hshtbl_free(M_hshtbl_t* table) {
	free(table->array);
	free(table);
}


/* utility to find where a key is located */
static _pair* find(M_hshtbl_t *table, M_uint_t key) {

	M_uint_t i;
	M_uint_t index = key % table->size;

	/* stop if the end of the table is reach or the key found */	
	i = index;

	while (table->array[i].key  != key
	   &&  table->array[i].used == true) {

		i = (i+1) % table->size;

		if (i == index) return NULL; /* not found */
	}
		
	return &(table->array[i]);

}

void* M_hshtbl_get(M_hshtbl_t *table, M_uint_t key) {

	_pair* p = find(table, key);

	/* not in table */
	if (p == NULL || !p->used) {
		return NULL;
	} 

	return p->val;
}


bool M_hshtbl_set(M_hshtbl_t* table, M_uint_t key, void* value) {

	_pair* p = find(table, key);

	/* not in table */
	if (p == NULL || !p->used) {
		return false;
	} 

	p->val = value;

	return true;
}


bool M_hshtbl_add(M_hshtbl_t* table, M_uint_t key, void* value) {

	_pair* p = find(table, key);

	/* table full or already in table */
	if (p == NULL || p->used) {
		return false;
	} 

	p->val = value;
	p->key = key;
	p->used = true;

	return true;
}


bool M_hshtbl_rem(M_hshtbl_t* table, M_uint_t key) {

	_pair* p = find(table, key);
	
	/* not in table */
	if (p == NULL || !p->used) {
		return false;
	} 

	p->used = false;

	return true;
}

bool M_hshtbl_mem(M_hshtbl_t* table, M_uint_t key) {

	_pair* p = find(table, key);

	return p != NULL && p->used == true;
}

