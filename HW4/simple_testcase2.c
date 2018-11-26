#include <stdio.h>
#include "537malloc.h"

int main() {
	printf("Allocating memory of size 0 bytes\n");
	char *ptr = malloc537(0);
	printf("malloc should print a waring and proceed\n");

	printf("Freeing the ptr should result in error\n");
	free537(ptr);

	printf("This statement shouldn't print\n");

	return 0;
}
