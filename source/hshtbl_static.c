#include "hshtbl.h"
#include "errors.h"

#include <stdbool.h>


typedef struct  {
	size_t key;
	void*  val;
	bool  used;
} _pair;


struct __M_hshtbl_t__ {
	_pair *array;
	size_t size;
};



M_hshtbl_t* M_hshtbl_make() {
	return M_hshtbl_nMake(M_HSHTBL_DEFAULT_SIZE); 
}


M_hshtbl_t* M_hshtbl_nMake(size_t size) {

	M_hshtbl_t* table = malloc(sizeof(M_hshtbl_t));
	
	table->array = calloc(size, sizeof(_pair));
	table->size = size;

	return table;
}


void M_hshtbl_free(M_hshtbl_t* table) {
	free(table->array);
	free(table);
}


/* utility to find where a key is located */
static size_t find(M_hshtbl_t *table, size_t hash) {

	int i;
	size_t index = hash % table->size;

	/* stop if the end of the table is reach or the key found */	
	for (i = index; i < table->size; i++) {

		if (table->array[i].key == hash 
		&&  table->array[i].used == false)
			return i;
	}

	return table->size;
}


void* M_hshtbl_get(M_hshtbl_t *table, size_t hash) {

	size_t loc = find(table, hash);

	M_assert(loc < table->size, "Key not in table.");

	return table->array[loc].val;
}


void M_hshtbl_set(M_hshtbl_t* table, size_t hash, void* value) {

	size_t loc = find(table, hash);

	M_assert(loc < table->size, "Key not in table.");

	table->array[loc].val = value;
}


void M_hshtbl_add(M_hshtbl_t* table, size_t hash, void* value) {

	size_t loc = find(table, hash);

	M_assert(loc == table->size, "Key already in table.");

	while (table->array[loc].used) {
		loc++;
		M_assert(loc < table->size, "Table full.");
	}

	table->array[loc].val = value;
	table->array[loc].key = hash;
	table->array[loc].used = false;
}


bool M_hshtbl_forceAdd(M_hshtbl_t* table, size_t hash, void* value) {

	bool res;
	size_t loc = find(table, hash);


	/* key not in table, leave a new available node */
	if (loc == table->size)  {

		loc = hash % table->size;
		while (table->array[loc].used) {
			loc++;
			M_assert(loc < table->size, "Table full.");
		}

		table->array[loc].key = hash;
		table->array[loc].used = true;

		res = true;

	}
	else {
		res = false;
	}

	table->array[loc].val = value;


	return res;
}


void M_hshtbl_rem(M_hshtbl_t* table, size_t hash) {

	size_t loc = find(table, hash);
	M_assert(loc < table->size, "Key not in table.");

	table->array[loc].used = false;
}



bool M_hshtbl_forceRem(M_hshtbl_t* table, size_t hash) {

	size_t loc = find(table, hash);
	M_assert(loc < table->size, "Key not in table.");

	/* if in table remove node */
	if (loc == table->size) {
		table->array[loc].used = false;
		return true;
	}

	/* do nothing */
	else {
		return false;
	}


}

bool M_hshtbl_mem(M_hshtbl_t* table, size_t hash) {

	size_t loc = find(table, hash);
	return loc < table->size;
}

