#include "dict.h"
#include "errors.h"

#include <stdlib.h>
#include <string.h>

/* ADAPTED FROM HSHTBL_STATIC_C */


#define M_DICT_DEFAULT_SIZE 1024

typedef struct  {
	const char* key;
	void* val;
	bool used;
} _pair;


struct __M_dict_t__ {
	_pair *array;
	size_t  size;
};




M_dict_t* M_dict_nmake(size_t size) {
	int i;
	M_dict_t* dict = malloc(sizeof(M_dict_t));
	
	dict->array = malloc(size * sizeof(_pair));
	dict->size = size;

	for (i = 0; i < size; i++) {
		dict->array[i].key = 0;
		dict->array[i].val = 0;
		dict->array[i].used = false;
	}

	return dict;
}

M_dict_t* M_dict_make() {
	M_dict_t* t = M_dict_nmake(M_DICT_DEFAULT_SIZE); 
	return t;
}


void M_dict_free(M_dict_t* dict) {
	free(dict->array);
	free(dict);
}


/* http://www.cse.yorku.ca/~oz/hash.html */
static size_t djb2(const char *str) {
    size_t hash = 5381;
    int c;

    while ( (c = *str++) )
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}


/* utility to find where a key is located */
static size_t find(M_dict_t* dict, const char* key) {

	int i;
	size_t index, hash;

	hash = djb2(key);
	index = hash % dict->size;


	/* stop if the end of the dict is reach or the key found */	
	for (i = index; i < dict->size; i++) {

		if (dict->array[i].used == false
		||  0 == strcmp(dict->array[i].key, key))
			return i;
	}

	return dict->size;
}


void* M_dict_get(M_dict_t *dict, const char* key) {

	size_t loc = find(dict, key);

	M_assert(loc < dict->size && dict->array[loc].used == true, 
		"Key not in dict.");

	return dict->array[loc].val;
}


void M_dict_set(M_dict_t* dict, const char* key, void* value) {

	size_t loc = find(dict, key);

	M_assert(loc < dict->size && dict->array[loc].used == true,
		"Key not in dict.");

	dict->array[loc].val = value;
}


void M_dict_add(M_dict_t* dict, const char* key, void* value) {

	size_t loc = find(dict, key);

	M_assert(loc < dict->size, "Table full.");

	M_assert(dict->array[loc].used == false, 
		"Key already in dict.");
	
	dict->array[loc].val = value;
	dict->array[loc].key = key;
	dict->array[loc].used = true;
}


void M_dict_forceAdd(M_dict_t* dict, const char* key, void* value) {

	size_t loc = find(dict, key);

	M_assert(loc < dict->size, "Table full.");

	while (dict->array[loc].used) {
		loc++;
		M_assert(loc < dict->size, "Table full.");
	}

	dict->array[loc].key = key;
	dict->array[loc].used = true;
	dict->array[loc].val = value;

}


void M_dict_rem(M_dict_t* dict, const char* key) {

	size_t loc = find(dict, key);
	M_assert(loc < dict->size && dict->array[loc].used == true, 
		"Key not in dict.");

	dict->array[loc].used = false;
}



void M_dict_forceRem(M_dict_t* dict, const char* key) {

	size_t loc = find(dict, key);
	
	/* if in dict remove node */
	if (loc == dict->size) {
		dict->array[loc].used = false;
	}

}


bool M_dict_mem(M_dict_t* dict, const char* key) {

	size_t loc = find(dict, key);

	return loc < dict->size && dict->array[loc].used == true;
}

