#include "../datastruct.h"


#include <stdio.h>
#include <stdlib.h>

M_list_t* l;

void* arr[10] = {1, 25, 3};

int main(int argc, char** argv) {
	int i;

	printf("Testing data structure and utility lib\n");

	l = M_list_fromArray(arr, 10);

	M_list_print("%d, ", l);

	M_list_free(l);

	printf("SUCCESS\n");
	
	return 0;
}