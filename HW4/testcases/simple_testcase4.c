#include <stdio.h>
#include "537malloc.h"

int main() {
	printf("Allocating 1 byte of memory\n");
	char *ptr = malloc537(sizeof(char));

	printf("Double Free : Freeing memory at %p twice\n", ptr);
	free537(ptr);
	printf("1st free, should be a success\n");
	free537(ptr);
	printf("This statement should not be printed!\n");

	return 0;
}
