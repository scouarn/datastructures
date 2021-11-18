#include "../datastruct.h"

#include <stdio.h>
#include <stdlib.h>

M_stack_t* s;
M_queue_t* q;

int main(int argc, char** argv) {
		
	printf("Testing data structure and utility lib\n");

	s = M_stack_make();
	q = M_queue_make();
	#define PRINTOUT {printf("- q : %ld\n", (long)M_queue_pop(q));}

	M_queue_push(q, VP(0));
	
	PRINTOUT

	M_queue_push(q, VP(0));
	M_queue_push(q, VP(1));

	PRINTOUT
	PRINTOUT

	M_queue_push(q, VP(2));

	PRINTOUT	


	M_stack_free(s);
	M_queue_free(q);

	

	printf("SUCCESS\n");
	return 0;
}