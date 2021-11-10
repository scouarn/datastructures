#ifndef _HSHTBL_H_
#define _HSHTBL_H_


/* This is a pretty generelize hashtable implementation which only works 
 * with integer keys. An equality test function would be requiered if it
 * was to be done even more general. Here the hash is just the key modulo
 * the size of the table. For string-keyed dictionnary, using a dedicated 
 * module is prefered but you can use a hash of the string as a key if 
 * you know overlaps won't happen. */


#include <stdlib.h>
#include <stdbool.h>

#ifdef M_HSHTBL_STATIC 
    typedef struct __M_hshtbl_static_t__ M_hshtbl_t;

    #define M_hshtbl_make      M_hshtbl_static_make
    #define M_hshtbl_nmake     M_hshtbl_static_nmake
    #define M_hshtbl_resize    M_hshtbl_static_resize
    #define M_hshtbl_free      M_hshtbl_static_free
    #define M_hshtbl_get       M_hshtbl_static_get
    #define M_hshtbl_set       M_hshtbl_static_set
    #define M_hshtbl_add       M_hshtbl_static_add
    #define M_hshtbl_rem       M_hshtbl_static_rem
    #define M_hshtbl_mem       M_hshtbl_static_mem
    #define M_hshtbl_forceAdd  M_hshtbl_static_forceAdd
    #define M_hshtbl_forceRem  M_hshtbl_static_forceRem

 
#else 
    typedef struct __M_hshtbl_dyn_t__ M_hshtbl_t;

    #define M_hshtbl_make      M_hshtbl_dyn_make
    #define M_hshtbl_nmake     M_hshtbl_dyn_nmake
    #define M_hshtbl_resize    M_hshtbl_dyn_resize
    #define M_hshtbl_free      M_hshtbl_dyn_free
    #define M_hshtbl_get       M_hshtbl_dyn_get
    #define M_hshtbl_set       M_hshtbl_dyn_set
    #define M_hshtbl_add       M_hshtbl_dyn_add
    #define M_hshtbl_rem       M_hshtbl_dyn_rem
    #define M_hshtbl_mem       M_hshtbl_dyn_mem
    #define M_hshtbl_forceAdd  M_hshtbl_dyn_forceAdd
    #define M_hshtbl_forceRem  M_hshtbl_dyn_forceRem

#endif



M_hshtbl_t* M_hshtbl_make();
M_hshtbl_t* M_hshtbl_nmake(size_t size);
M_hshtbl_t* M_hshtbl_resize(M_hshtbl_t* table); /* reallocate it in an array that fits the data better */
void M_hshtbl_free(M_hshtbl_t* table);


/* crashes if not found */
void* M_hshtbl_get(M_hshtbl_t* table, size_t key);

/* crashes if not in table yet */
void M_hshtbl_set(M_hshtbl_t* table, size_t key, void* value); 

/* crashes if already in table */
void M_hshtbl_add(M_hshtbl_t* table, size_t key, void* value);

/* remove from table, return false if it not in table  */
void M_hshtbl_rem(M_hshtbl_t* table, size_t key);

/* check if present in the table */
bool  M_hshtbl_mem(M_hshtbl_t* table, size_t key); 

/* if not in table, add it and return true, else change and return false */
bool M_hshtbl_forceAdd(M_hshtbl_t* table, size_t key, void* value);

/* if not in table, remove it and return true, else do nothing and return false */
bool M_hshtbl_forceRem(M_hshtbl_t* table, size_t key);



#endif /* hshtbl_h */