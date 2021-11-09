#include "../datastruct.h"


#include <stdio.h>
#include <stdlib.h>

M_mat_t* a;
M_mat_t* b;
M_mat_t* c;

int main(int argc, char** argv) {
	int i;

	printf("Testing data structure and utility lib\n");

	a = M_mat_make(5, 5);
	b = M_mat_make(5, 5);
	c = M_mat_make(5, 5);

	M_mat_unit(a);
	M_mat_unit(b);
	M_mat_unit(c);

	M_mat_add(a, a, b);
	M_mat_scale(a, a, 5.0);
	a[0][3] = -1;
	M_mat_trans(a, a);

	b[4][4] = 2;

	M_mat_print("%lg, ", a);
	printf("\n");

	M_mat_print("%lg, ", b);
	printf("\n");

	M_mat_mul(c, a, b);


	M_mat_print("%lg, ", c);
	printf("\n");


	M_mat_free(a);
	M_mat_free(b);
	M_mat_free(c);

	printf("SUCCESS\n");
	
	return 0;
}