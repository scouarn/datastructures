#ifndef _DICT_H_
#define _DICT_H_



#include <stdlib.h>
#include <stdbool.h>

typedef struct __M_dict_t__ M_dict_t;


M_dict_t* M_dict_make();
M_dict_t* M_dict_nmake(size_t size);
M_dict_t* M_dict_resize(M_dict_t* dict);
void M_dict_free(M_dict_t* dict);


/* crashes if not found */
void* M_dict_get(M_dict_t* dict, const char* key);

/* crashes if not in dict yet */
void M_dict_set(M_dict_t* dict, const char* key, void* value); 

/* crashes if already in dict */
void M_dict_add(M_dict_t* dict, const char* key, void* value);

/* remove from dict, return false if it not in dict  */
void M_dict_rem(M_dict_t* dict, const char* key);

/* check if present in the dict */
bool  M_dict_mem(M_dict_t* dict, const char* key); 

/* if not in dict, add it and return true, else change and return false */
void M_dict_forceAdd(M_dict_t* dict, const char* key, void* value);

/* if not in dict, remove it and return true, else do nothing and return false */
void M_dict_forceRem(M_dict_t* dict, const char* key);





#endif /* dict_h */