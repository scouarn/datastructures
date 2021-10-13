#include <stdlib.h>
#include <stdio.h>

#include "utils.h"


void M_assert(bool test, const char* error_message) {

	if (!test) {
		printf("%s", error_message);
		exit(EXIT_FAILURE);
	}

}


