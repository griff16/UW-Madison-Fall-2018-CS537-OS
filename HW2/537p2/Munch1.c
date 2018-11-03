#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "Queue.h"
#include "struct.h"

/*
* CS 537 Fall 2018 
* Program Assignment 2
* 1,Griff Zhang,xzhang953,griff,xzhang953@wisc.edu,9078214609
* 2,Yanting Liang, yliang73,yliang73,yliang73@wisc.edu,9074460412
*/

void *Munch1(void *args) {
	struct thread_args *arg = args;
	Queue *in_queue = arg->arg1;
	Queue *out_queue = arg->arg2;
	char *string;
	int i;
	do {
		string = DequeueString(in_queue); 
		i = 0;
		if(string != NULL) {
			while (i < (int)strlen(string) - 1) {
				if (string[i] == ' ') {
					string[i] = '*';
				}
				i++;
			}
			EnqueueString(out_queue, string);
		} else {
			char *tmpPtr = NULL;
			EnqueueString(out_queue, tmpPtr);
		}
	} while (string != NULL);
	pthread_exit(NULL);
}
