#ifndef _DICT_H_
#define _DICT_H_


#include <stdbool.h>
#define M_DICT_DEFAULT_SIZE 1024


#ifdef M_DICT_STATIC 
    typedef struct __M_dict_static_t__ M_dict_t;

    #define M_dict_make      M_dict_static_make
    #define M_dict_nmake     M_dict_static_nmake
    #define M_dict_resize    M_dict_static_resize
    #define M_dict_free      M_dict_static_free
    #define M_dict_get       M_dict_static_get
    #define M_dict_set       M_dict_static_set
    #define M_dict_add       M_dict_static_add
    #define M_dict_rem       M_dict_static_rem
    #define M_dict_mem       M_dict_static_mem
    #define M_dict_forceAdd  M_dict_static_forceAdd
    #define M_dict_forceRem  M_dict_static_forceRem

 
#else 
    typedef struct __M_dict_dyn_t__ M_dict_t;

    #define M_dict_make      M_dict_dyn_make
    #define M_dict_nmake     M_dict_dyn_nmake
    #define M_dict_resize    M_dict_dyn_resize
    #define M_dict_free      M_dict_dyn_free
    #define M_dict_get       M_dict_dyn_get
    #define M_dict_set       M_dict_dyn_set
    #define M_dict_add       M_dict_dyn_add
    #define M_dict_rem       M_dict_dyn_rem
    #define M_dict_mem       M_dict_dyn_mem
    #define M_dict_forceAdd  M_dict_dyn_forceAdd
    #define M_dict_forceRem  M_dict_dyn_forceRem

#endif


/* uses the default size */
M_dict_t* M_dict_make();

M_dict_t* M_dict_nmake(long size);
void M_dict_free(M_dict_t* table);

/* a new table is created and the old one is freeed */
M_dict_t* M_dict_resize(M_dict_t* table, long size);


/* return NULL if not found */
void* M_dict_get(M_dict_t* table, const char* key);

/* return false if not in table yet */
bool M_dict_set(M_dict_t* table, const char* key, void* value); 

/* return false if already in table */
bool M_dict_add(M_dict_t* table, const char* key, void* value);

/* remove from table, return false if it was not in table */
bool M_dict_rem(M_dict_t* table, const char* key);

/* check if present in the table */
bool  M_dict_mem(M_dict_t* table, const char* key); 


#endif /* dict_h */