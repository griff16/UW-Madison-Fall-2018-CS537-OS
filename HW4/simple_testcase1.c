#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "537malloc.h"

struct testNode {
	int val;
	char name;
};

int main()
{
	// 1-A: Simple testcase - Memory Allocation
	printf("Allocating 10 bytes of Memory\n");
	char *this_ptr = malloc537(sizeof(char) * 10);
	if(this_ptr == NULL) {
		printf("Memory allocation failed!\n");
		exit(1);
	}

	// 1-B: Simple testcase - Memory check 1st 5 byts
	printf("Checking first 5 bytes of %p\n", this_ptr);
	memcheck537(this_ptr, 5);

	strncpy(this_ptr, "hello world", 10);
	printf("Content : %s\n", this_ptr);

	// 1-C: Simple testcase - Memory check last 5 bytes
	printf("Checking last 5 bytes of %p\n", this_ptr);
	memcheck537(this_ptr + 5, 5);

	printf("Freeing memory : %p\n", this_ptr);
	// 1-D: Correct Free
	free537(this_ptr);
	printf("Successfully freed memory!\n");

	// 1-E: Same cases as above
	printf("Allocating memory for the struct\n");
	struct testNode *new_ptr = (struct testNode *)malloc537(sizeof(struct testNode));
	if(new_ptr == NULL) {
		printf("Memory allocation failed!\n");
		exit(1);
	}
	printf("Allocated Memory : %p\n", new_ptr);
	printf("Allocated size : %ld\n", sizeof(struct testNode));

	printf("Checking 1st 5 bytes of memory allocated\n");
	memcheck537(new_ptr, 5);

	printf("Freeing the structure pointer : %p\n", new_ptr);
	free(new_ptr);

	printf("If this prints, everything is success!\n");
	return 0;
}
