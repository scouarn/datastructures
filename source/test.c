#include "../datastruct.h"


#include <stdio.h>
#include <stdlib.h>

long int data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
M_list_t *mylist, *tmp;

int main(int argc, char** argv) {
	int i;

	printf("Testing data structure and utility lib\n");

	mylist = EMPTY_LIST;

	for (i = 0; i < 10; i++) M_list_push(&mylist, (void*)data[i]);

	M_list_print("%d, ", mylist);

	M_list_free(mylist);

	printf("SUCCESS\n");
	
	return 0;
}