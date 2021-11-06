#include "hshtbl.h"
#include "errors.h"

/* I decided not to rely on the linked list functions
 * already implemented in order to keep this module 
 * self-contained */

/* In this implementation, each cell of the talbe
 * is a list of (key, val) pairs with the last node always
 * left available to add an element into. */


typedef struct __list__ {
	size_t hash;
	void* value;
	struct __list__ *next;
} _list;


struct __M_hshtbl_t__ {
	_list *array;
	size_t size;

};



M_hshtbl_t* M_hshtbl_make() {
	return M_hshtbl_nMake(M_HSHTBL_DEFAULT_SIZE); 
}


M_hshtbl_t* M_hshtbl_nMake(size_t size) {

	M_hshtbl_t* table = malloc(sizeof(M_hshtbl_t));
	
	table->array = calloc(size, sizeof(_list));
	table->size = size;

	return table;
}


void M_hshtbl_free(M_hshtbl_t* table) {
	
	M_warning("TODO : FREE THE LISTS");

	free(table->array);
	free(table);
}


/* utility to find where a key is located, 
 * return the tail of the list if not found */
static _list* find(M_hshtbl_t *table, size_t hash) {

	size_t index = hash % table->size;

	_list* node = &(table->array[index]);

	while (node->next != NULL  /* stop if the tail is reach or the key foud */
	    && node->hash != hash)

		node = node->next;

	return node;
}


void* M_hshtbl_get(M_hshtbl_t *table, size_t hash) {

	_list* node = find(table, hash);

	M_assert(node->next != NULL, "Key not in table.");

	return node->value;
}


void M_hshtbl_set(M_hshtbl_t* table, size_t hash, void* value) {

	_list* node = find(table, hash);

	M_assert(node->next != NULL, "Key not in table.");

	node->value = value;	
}


void M_hshtbl_add(M_hshtbl_t* table, size_t hash, void* value) {

	_list* node = find(table, hash);

	M_assert(node->next == NULL, "Key already in table.");

	node->value = value;
	node->hash  = hash;

	/* leave a new available node */
	node->next = malloc(sizeof(_list));
	node->next->next = NULL;
}


bool M_hshtbl_forceAdd(M_hshtbl_t* table, size_t hash, void* value) {

	bool res;
	_list* node = find(table, hash);


	/* key not in table, leave a new available node */
	if (node->next == NULL)  {
		res = true;
		node->next = malloc(sizeof(_list));
		node->next->next = NULL;
	}
	else {
		res = false;
	}

	/* either case set the node */
	node->value = value;
	node->hash  = hash;

	return res;
}


void M_hshtbl_rem(M_hshtbl_t* table, size_t hash) {
	_list* next;
	_list* node = find(table, hash);

	M_assert(node->next != NULL, "Key not in table.");

	/* list surgery to remove the node : override it with the next one */
	next = node->next;

	node->hash  = next->hash;
	node->value = next->value;
	node->next  = next->next;

	free(next);

	/* should be correct even if it is overridden by the last node */

}



bool M_hshtbl_forceRem(M_hshtbl_t* table, size_t hash) {

	_list* next;
	_list* node = find(table, hash);

	/* if in table remove node */
	if (node->next != NULL) {

		next = node->next;

		node->hash  = next->hash;
		node->value = next->value;
		node->next  = next->next;

		free(next);

		return true;
	}

	else {

		return false;
	}



}

bool M_hshtbl_mem(M_hshtbl_t* table, size_t hash) {

	_list* node = find(table, hash);

	return node->hash == hash;
}
