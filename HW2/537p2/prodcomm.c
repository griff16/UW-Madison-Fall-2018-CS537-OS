#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <assert.h>
#include "Reader.h"
#include "Writer.h"
#include "Munch1.h"
#include "Munch2.h"
#include "Queue.h"
#include "struct.h"

#define Max_Size 10

/*
* CS 537 Fall 2018 
* Program Assignment 2
* 1,Griff Zhang,xzhang953,griff,xzhang953@wisc.edu,9078214609
* 2,Yanting Liang, yliang73,yliang73,yliang73@wisc.edu,9074460412
*/

int main () {

	pthread_t rthread_id;
	pthread_t m1thread_id;
	pthread_t m2thread_id;
	pthread_t wthread_id;

	Queue *q1 = CreateStringQueue(Max_Size);
	Queue *q2 = CreateStringQueue(Max_Size);
	Queue *q3 = CreateStringQueue(Max_Size);

	int rc = pthread_create(&rthread_id, NULL, Reader, (void*)q1);
	assert(rc == 0);

	struct thread_args Munch1_args;
	Munch1_args.arg1 = q1;
	Munch1_args.arg2 = q2;
	rc = pthread_create(&m1thread_id, NULL, Munch1, (void *)&Munch1_args);
	assert(rc == 0);

	struct thread_args Munch2_args;
	Munch2_args.arg1 = q2;
	Munch2_args.arg2 = q3;
	rc = pthread_create(&m2thread_id, NULL, Munch2, (void *)&Munch2_args);
	assert(rc == 0);

	rc = pthread_create(&wthread_id, NULL, Writer, (void*)q3);
	assert(rc == 0);

	if(pthread_join(rthread_id, NULL) + pthread_join(m1thread_id, NULL) 
		+ pthread_join(m2thread_id, NULL) + pthread_join(wthread_id, NULL) != 0) {
		perror("pthread join failed");
		exit(1);
	}

	printf("First Queue Stat: \n");
	PrintQueueStats(q1);
	printf("Second Queue Stat: \n");
	PrintQueueStats(q2);
	printf("Third Queue Stat: \n");
	PrintQueueStats(q3);

	exit(0);
}
