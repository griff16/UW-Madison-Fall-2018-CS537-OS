#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "Queue.h"

/*
* CS 537 Fall 2018 
* Program Assignment 2
* 1,Griff Zhang,xzhang953,griff,xzhang953@wisc.edu,9078214609
* 2,Yanting Liang, yliang73,yliang73,yliang73@wisc.edu,9074460412
*/

void *Writer(void *q) {
	Queue *queue = (Queue*) q;
	char *string;
	do
	{
		string = DequeueString(queue);
		if(string != NULL) {
			printf("%s", string);
		}
	} while (string != NULL);
	pthread_exit(NULL);
}