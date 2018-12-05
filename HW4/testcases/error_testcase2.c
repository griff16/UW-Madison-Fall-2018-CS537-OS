#include <stdio.h>
#include "537malloc.h"

#define SIZE 1000

int main() {
	int *ptr = malloc537(SIZE);
	printf("Allocated %d bytes @ %p\n", SIZE, ptr);

	printf("Freeing at %p + 5 : Should fail - Not a start address!\n", ptr);
	free537(ptr + 5);

	printf("If this prints, no points\n");

	return 0;
}
