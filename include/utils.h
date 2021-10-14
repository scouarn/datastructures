#ifndef _UTILS_H_
#define _UTILS_H_


#include <stdint.h>


#define MAX(a,b) \
   ({ __typeof__ (a) _a = (a); \
      __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define MIN(a,b) \
   ({ __typeof__ (a) _a = (a); \
      __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

#define VP(x) ((void*)x)


typedef enum {false, true} bool;


void M_assert(bool test, const char* error_message);



#endif //utils_h