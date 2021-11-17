#ifndef _UTILS_H_
#define _UTILS_H_



/* not safe with MIN(a++, --b)... */
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))


#define VP(x) ((void*)(x))

typedef unsigned long int M_uint_t;



#endif /* utils_h */