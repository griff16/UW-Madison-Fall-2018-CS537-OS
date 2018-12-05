#include <stdio.h>
#include "537malloc.h"

#define SIZE 1000

int main() {
	int size = sizeof(int) * SIZE;
	void *ptr = malloc537(size);
	printf("Allocated %d bytes @ %p\n", size, ptr);

	printf("Freeing at %p + mid : Should fail - Invalid address!\n", ptr);
	free537(ptr + (size / 2));

	printf("If this prints, no points\n");

	return 0;
}
