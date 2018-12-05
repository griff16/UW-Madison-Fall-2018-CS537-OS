#include <stdio.h>
#include <stdlib.h>
#include "537malloc.h"
#include <time.h>

#define LIMIT 1000000
#define SIZE 1

int main() {
	char *ptr[LIMIT];
	int i = 0;

	clock_t startTimeAlloc = clock();
	for(i = 0; i < LIMIT; i++) {
		ptr[i] = malloc537(SIZE);
		printf("Allocated 1 byte of memory at %p\n", ptr[i]);
	}
	clock_t endTimeAlloc = clock();

	clock_t startTimeMemCheck = clock();
	for(i = 0; i < LIMIT; i++) {
		printf("Mem check : %p\n", ptr[i]);
		memcheck537(ptr[i], 1);
	}
	clock_t endTimeMemCheck = clock();

	clock_t startTimeFree = clock();
	for(i = 0; i < LIMIT; i++) {
		printf("Freeing : %p\n", ptr[i]);
		free537(ptr[i]);
	}
	clock_t endTimeFree = clock();

	printf("If this prints, you get points!\n");
	printf("Alloc Time Taken : %f secs\n", ((double)endTimeAlloc - startTimeAlloc) / CLOCKS_PER_SEC);
	printf("Memcheck Time Taken : %f secs\n", ((double)endTimeMemCheck - startTimeMemCheck) / CLOCKS_PER_SEC);
	printf("Free Time Taken : %f secs\n", ((double)endTimeFree - startTimeFree) / CLOCKS_PER_SEC);
}
