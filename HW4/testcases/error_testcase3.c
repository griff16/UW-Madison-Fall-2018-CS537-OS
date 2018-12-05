#include <stdio.h>
#include "537malloc.h"

#define SIZE 1000

int main() {
	int *ptr = malloc537(SIZE);
	printf("Allocated %d bytes @ %p\n", SIZE, ptr);

	printf("Memcheck at %p - 10 : Should fail - Invalid address!\n", ptr);
	memcheck537(ptr - 10, SIZE);

	printf("If this prints, no points\n");

	return 0;
}
