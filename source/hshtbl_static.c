#include "hshtbl.h"
#include "errors.h"


#define M_HSHTBL_DEFAULT_SIZE 1024

typedef struct  {
	size_t key;
	void*  val;
	bool  used;
} _pair;


typedef struct __M_hshtbl_static_t__ {
	_pair *array;
	size_t size;
} M_hshtbl_static_t;




M_hshtbl_static_t* M_hshtbl_static_nmake(size_t size) {
	int i;
	M_hshtbl_static_t* table = malloc(sizeof(M_hshtbl_static_t));
	
	table->array = malloc(size * sizeof(_pair));
	table->size = size;

	for (i = 0; i < size; i++) {
		table->array[i].key = 0;
		table->array[i].val = 0;
		table->array[i].used = false;
	}

	return table;
}

M_hshtbl_static_t* M_hshtbl_static_make() {
	M_hshtbl_static_t* t = M_hshtbl_static_nmake(M_HSHTBL_DEFAULT_SIZE); 
	return t;
}


void M_hshtbl_static_free(M_hshtbl_static_t* table) {
	free(table->array);
	free(table);
}


/* utility to find where a key is located */
static size_t find(M_hshtbl_static_t *table, size_t hash) {

	int i;
	size_t index = hash % table->size;

	/* stop if the end of the table is reach or the key found */	
	for (i = index; i < table->size; i++) {

		if (table->array[i].key  == hash
		||  table->array[i].used == false)
			return i;
	}

	return table->size;
}


void* M_hshtbl_static_get(M_hshtbl_static_t *table, size_t hash) {

	size_t loc = find(table, hash);

	M_assert(loc < table->size && table->array[loc].used == true, 
		"Key not in table.");

	return table->array[loc].val;
}


void M_hshtbl_static_set(M_hshtbl_static_t* table, size_t hash, void* value) {

	size_t loc = find(table, hash);

	M_assert(loc < table->size && table->array[loc].used == true,
		"Key not in table.");

	table->array[loc].val = value;
}


void M_hshtbl_static_add(M_hshtbl_static_t* table, size_t hash, void* value) {

	size_t loc = find(table, hash);

	M_assert(loc < table->size, "Table full.");

	M_assert(table->array[loc].used == false, 
		"Key already in table.");
	
	table->array[loc].val = value;
	table->array[loc].key = hash;
	table->array[loc].used = true;
}


void M_hshtbl_static_forceAdd(M_hshtbl_static_t* table, size_t hash, void* value) {

	size_t loc = find(table, hash);

	M_assert(loc < table->size, "Table full.");

	while (table->array[loc].used) {
		loc++;
		M_assert(loc < table->size, "Table full.");
	}

	table->array[loc].key = hash;
	table->array[loc].used = true;
	table->array[loc].val = value;

}


void M_hshtbl_static_rem(M_hshtbl_static_t* table, size_t hash) {

	size_t loc = find(table, hash);
	M_assert(loc < table->size && table->array[loc].used == true, 
		"Key not in table.");

	table->array[loc].used = false;
}



void M_hshtbl_static_forceRem(M_hshtbl_static_t* table, size_t hash) {

	size_t loc = find(table, hash);
	
	/* if in table remove node */
	if (loc == table->size) {
		table->array[loc].used = false;
	}

}


bool M_hshtbl_static_mem(M_hshtbl_static_t* table, size_t hash) {

	size_t loc = find(table, hash);

	return loc < table->size && table->array[loc].used == true;
}

