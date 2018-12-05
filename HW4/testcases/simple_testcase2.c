#include <stdio.h>
#include "537malloc.h"

int main() {
	printf("Allocating memory of size 0 bytes\n");
	char *ptr = malloc537(0);
	printf("malloc should print a waring and proceed\n");

	printf("If this prints, you will get points\n");

	return 0;
}
