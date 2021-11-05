#ifndef _ERRORS_H_
#define _ERRORS_H_

#include <stdlib.h>
#include <stdio.h>
#include <time.h>


/* has to be a macro to now what __FILE__ is... */
#define M_throw(type, message) {\
	char buffer[16];\
	time_t sec = time(NULL);\
	struct tm* tm_info = localtime(&sec);\
	strftime(buffer, 16, "%H:%M:%S", tm_info);\
	fprintf(stderr, "[%s - %s] %s : %s\n", buffer, __FILE__, type, message);\
}\


#define M_error(message) {\
	M_throw("ERROR", message);\
	exit(EXIT_FAILURE);\
}\

#define M_warning(message) {\
	M_throw("WARNING", message);\
}\


#define M_assert(test, message) {\
	if (!(test)) {\
		M_throw("FAILED TO ASSERT " #test, message);\
		exit(EXIT_FAILURE);\
	}\
}\



#endif /* errors_h */


