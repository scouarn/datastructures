#define M_HSHTBL_STATIC

#include "../datastruct.h"


#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv) {
	void* x;
	M_hshtbl_t* table = M_hshtbl_make();

	M_hshtbl_add(table, 9, VP(99));

	x = M_hshtbl_get(table, 9);

	printf("%d\n", (int)x);

	M_hshtbl_free(table);

	printf("Testing data structure and utility lib\n");
	printf("SUCCESS\n");
	

	return 0;
}