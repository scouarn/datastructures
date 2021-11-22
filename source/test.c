#include "../datastruct.h"

#include <stdio.h>
#include <stdlib.h>



M_num_t* n;
M_num_t* m;

int main(int argc, char** argv) {
		
	printf("Testing data structure and utility lib\n");

	n = M_num_make(8);
	m = M_num_make(8);

	M_num_lcpy(n, 12);
	M_num_lcpy(m, 100);

	M_num_sub(n, m, n);	

	M_num_print(n);

	M_num_free(n);
	M_num_free(m);

	printf("SUCCESS\n");
	return 0;
}