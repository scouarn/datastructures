#define M_HSHTBL_STATIC
#include "../datastruct.h"


#include <stdio.h>
#include <stdlib.h>

M_hshtbl_t* table;

int main(int argc, char** argv) {
	
	printf("Testing data structure and utility lib\n");
	
	table = M_hshtbl_nmake(10);

	M_hshtbl_add(table, 69, VP(420));


	printf("found : %ld\n", (long) M_hshtbl_get(table, 69));


	table = M_hshtbl_resize(table, 20);

	
	M_hshtbl_set(table, 69, VP(99));



	printf("found : %ld\n", (long) M_hshtbl_get(table, 69));

	M_hshtbl_rem(table, 69);

	printf("found : %ld\n", (long) M_hshtbl_get(table, 69));


	M_hshtbl_free(table);

	printf("SUCCESS\n");
	return 0;
}