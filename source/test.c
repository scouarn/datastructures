#include "../datastruct.h"


#include <stdio.h>
#include <stdlib.h>

M_hshtbl_t* dict;

int main(int argc, char** argv) {
	int i;

	printf("Testing data structure and utility lib\n");

	dict = M_hshtbl_make();


	M_hshtbl_add(dict, 0, VP(0));
	M_hshtbl_add(dict, 1, VP(1));
	M_hshtbl_add(dict, 10, VP(10));
	M_hshtbl_add(dict, 10564662214, VP(999));
	M_hshtbl_add(dict, 1024, VP(1111));
	M_hshtbl_add(dict, 1023, VP(444));
	M_hshtbl_add(dict, 1025, VP(333));
	M_hshtbl_add(dict, 2, VP(2));

	M_hshtbl_forceAdd(dict, 1, VP(69));


	printf("%ld\n", (long)M_hshtbl_get(dict, 0));
	printf("%ld\n", (long)M_hshtbl_get(dict, 1));
	printf("%ld\n", (long)M_hshtbl_get(dict, 10));
	printf("%ld\n", (long)M_hshtbl_get(dict, 10564662214));
	printf("%ld\n", (long)M_hshtbl_get(dict, 1024));
	printf("%ld\n", (long)M_hshtbl_get(dict, 1023));
	printf("%ld\n", (long)M_hshtbl_get(dict, 1025));
	printf("%ld\n", (long)M_hshtbl_get(dict, 2));


	M_hshtbl_rem(dict, 0);
	M_hshtbl_rem(dict, 1);
	M_hshtbl_forceRem(dict, 0);


	M_hshtbl_free(dict);

	printf("SUCCESS\n");
	
	return 0;
}