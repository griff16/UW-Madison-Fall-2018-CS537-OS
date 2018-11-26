#include <stdio.h>
#include "537malloc.h"

int main() {
	printf("Allocating 10 bytes of memory\n");
	char *ptr = malloc537(10);

	printf("Allocated addr : %p\n", ptr);
	// This should pass
	memcheck537(ptr, 10);

	printf("Reallocating to 20 bytes\n");
	ptr = realloc537(ptr, 20);

	printf("Reallocated addr : %p\n", ptr);

	// This should pass
	memcheck537(ptr, 10);
	printf("If this prints, realloc is passing!\n");

	return 0;
}
