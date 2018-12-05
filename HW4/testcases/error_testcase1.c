#include <stdio.h>
#include "537malloc.h"

int main() {
	int *ptr = NULL;

	printf("Freeing NULL pointer\n");
	free537(ptr);

	printf("If this prints, no points\n");
	return 0;
}
