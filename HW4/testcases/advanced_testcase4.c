#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "537malloc.h"

#define LIMIT 100
#define SIZE_RANGE 100

int main() {
	int mem_size[LIMIT];
	int i;

	// Getting random sizes
	srand(time(NULL));
	for(i = 0; i < LIMIT; i++) {
		mem_size[i] = rand() % SIZE_RANGE + 1;
	}

	printf("Allocating memory of 10 bytes\n");
	char *ptr = malloc537(sizeof(char) * 10);
	printf("Allocated @ %p\n", ptr);

	for(i = 0; i < LIMIT; i++) {
		printf("Reallocating memory for %d bytes\n", mem_size[i]);
		ptr = realloc537(ptr, mem_size[i]);
		printf("Allocated @ %p\n", ptr);
	}

	printf("If this prints, you will get points\n");

	return 0;
}
