#ifndef _UTILS_H_
#define _UTILS_H_


#include <stdint.h>
#include <stdbool.h>

/* not safe with MIN(a++, --b)... */
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))


#define VP(x) ((void*)(x))



#endif /* utils_h */