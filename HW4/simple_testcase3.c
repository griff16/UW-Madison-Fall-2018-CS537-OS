#include <stdio.h>
#include "537malloc.h"

int main() {
	printf("Allocating 10 * sizeof(int) memory\n");
	int *ptr = malloc537(sizeof(int) * 10);

	printf("Allocated memory location : %p\n", ptr);
	ptr--;
	printf("After decrement, ptr value : %p\n", ptr);

	printf("Freeing : %p\n", ptr);
	// Should throw an error
	free537(ptr);

	printf("This statment should not be printed");
	return 0;
}
