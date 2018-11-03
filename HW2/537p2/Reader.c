#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "Queue.h"

#define BufferSize 1024 //BufferSize can change

/*
* CS 537 Fall 2018 
* Program Assignment 2
* 1,Griff Zhang,xzhang953,griff,xzhang953@wisc.edu,9078214609
* 2,Yanting Liang, yliang73,yliang73,yliang73@wisc.edu,9074460412
*/

void *Reader(void *q) 
{
	Queue *queue = (Queue*) q;
	char buffer[BufferSize];
	int flag = 0;

	while (fgetc(buffer, BufferSize, stdin) != NULL) {
		int len = strlen(buffer);
		if (len == BufferSize - 1 && buffer[len - 1] != '\n') {
			flag++;
		} else {
			// flag is larger than 0 when this line belongs to the line that exceeds buffer size
			if(flag > 0) {
				fprintf(stderr, "This line exceeds buffer size.\n");
				flag = 0;
			} else {
				EnqueueString(queue, buffer);
			}
		}
		memset(buffer, '\0', sizeof(buffer));	
	}
	// EOF, insert null to queue
	char *tmpPtr = NULL;
	EnqueueString(queue, tmpPtr);
	pthread_exit(NULL);
}
