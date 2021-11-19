#include "../datastruct.h"

#include <stdio.h>
#include <stdlib.h>

static void callback(M_uint_t id) {

	int i;

	printf("doing job #%ld\n", id);

	for (i = 0; i < 1000000000; i++) {}

	printf("job #%ld done\n", id);
}


M_tpool_t* pool;

int main(int argc, char** argv) {
		
	printf("Testing data structure and utility lib\n");

	pool = M_tpool_make(10);

	M_tpool_batch(pool, callback, 20);

	M_tpool_free(pool);

	printf("SUCCESS\n");
	return 0;
}