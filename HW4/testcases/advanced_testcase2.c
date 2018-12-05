#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "537malloc.h"

#define LIMIT 100000
#define SIZE_RANGE 10000

int main() {
    printf("dedededede");
//	int i;
//	int mem_size[LIMIT];
//	int *addr[LIMIT] = {NULL};
//
//	// Getting random sizes
//	srand(time(NULL));
//	for(i = 0; i < LIMIT; i++) {
//		mem_size[i] = rand() % SIZE_RANGE + 1;
//	}
//
//	clock_t startTimeAlloc = clock();
//	printf("Allocating randomly of random size\n");
//	// Allocating randomly
//	int count = 0, index;
//	while(count < LIMIT) {
//		index = rand() % LIMIT;
//		if(addr[index] == NULL) {
//			addr[index] = malloc537(mem_size[index]);
//			printf("Allocated %d size @ %p\n", mem_size[index], addr[index]);
//		}
//		count++;
//	}
//
//	// fill out the missing allocations
//	count = 0;
//	while(count < LIMIT) {
//		if(addr[count] == NULL) {
//			addr[count] = malloc537(mem_size[count]);
//			printf("Allocated %d size @ %p\n", mem_size[count], addr[count]);
//		}
//		count++;
//	}
//	clock_t endTimeAlloc = clock();
//
//	printf("Freeing randomly from the allocated addresses\n");
//	clock_t startTimeFree = clock();
//	// free randomly
//	count = 0;
//	index = 0;
//	printf("hello\n");
//	while(count < LIMIT) {
//		index = rand() % LIMIT;
//		if(addr[index] != NULL) {
//			printf("Free memory @ %p\n", addr[index]);
//			free537(addr[index]);
//			addr[index] = NULL;
//		}
//		count++;
//	}
//
//	// free the rest
//	count = 0;
//	while(count < LIMIT) {
//		if(addr[count] != NULL) {
//			printf("Free memory @ %p\n", addr[count]);
//			free537(addr[count]);
//			addr[index] = NULL;
//		}
//		count++;
//	}
//	clock_t endTimeFree = clock();
//
//	printf("If this prints, you get points!\n");
//	printf("Alloc Time Taken : %f secs\n", ((double)endTimeAlloc - startTimeAlloc) / CLOCKS_PER_SEC);
//	printf("Free Time Taken : %f secs\n", ((double)endTimeFree - startTimeFree) / CLOCKS_PER_SEC);
	return 0;
}
