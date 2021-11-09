#ifndef _ERRORS_H_
#define _ERRORS_H_

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/* defined here :
 * M_throw
 * M_assert
 * M_error
 * M_warning				 */


#ifdef M_DEBUG

#define M_throw(type, message) {\
	char buffer[16];\
	time_t sec = time(NULL);\
	struct tm* tm_info = localtime(&sec);\
	strftime(buffer, 16, "%H:%M:%S", tm_info);\
	fprintf(stderr, "[%s - %s - %s] %s : %s\n", buffer, __FILE__, __func__, type, message);\
}\

#define M_assert(test, message) {\
	if (!(test)) {\
		M_throw("FAILED TO ASSERT " #test, message);\
		exit(EXIT_FAILURE);\
	}\
}\

#else

#define M_throw(type, message) {\
	char buffer[16];\
	time_t sec = time(NULL);\
	struct tm* tm_info = localtime(&sec);\
	strftime(buffer, 16, "%H:%M:%S", tm_info);\
	fprintf(stderr, "[%s] %s : %s\n", buffer, type, message);\
}\

#define M_assert(test, message) {\
	if (!(test)) {\
		M_error(message);\
	}\
}\

#endif



#define M_error(message) {\
	M_throw("ERROR", message);\
	exit(EXIT_FAILURE);\
}\

#define M_warning(message) {\
	M_throw("WARNING", message);\
}\





#endif /* errors_h */


