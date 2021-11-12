#include "../datastruct.h"


#include <stdio.h>
#include <stdlib.h>

M_dict_t* table;

int main(int argc, char** argv) {
	
	printf("Testing data structure and utility lib\n");
	
	table = M_dict_nmake(10);

	M_dict_add(table, "69", VP(420));


	printf("found : %ld\n", (long) M_dict_get(table, "69"));


	table = M_dict_resize(table, 20);

	
	M_dict_set(table, "69", VP(99));



	printf("found : %ld\n", (long) M_dict_get(table, "69"));

	M_dict_rem(table, "69");

	printf("found : %ld\n", (long) M_dict_get(table, "69"));


	M_dict_free(table);

	printf("SUCCESS\n");
	return 0;
}