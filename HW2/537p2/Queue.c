#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "Queue.h"

/*
* CS 537 Fall 2018 
* Program Assignment 2
* 1,Griff Zhang,xzhang953,griff,xzhang953@wisc.edu,9078214609
* 2,Yanting Liang, yliang73,yliang73,yliang73@wisc.edu,9074460412
*/

typedef struct Queue 
{
	int front;  // index of first elemnt we insert
	int rear;  // index of last element we insert
	int capacity;
	char **array;
	//A count of the number of strings enqueued on this queue.
	int enqueueCount;
	//A count of the number of strings dequeued on this queue. We would expect that when the program exits, the two count values are equal.
	int dequeueCount;
	//A count of the number of times that an enqueue was attempted but blocked.
	int enqueueBlockCount;
	//A count of the number of times that a dequeue was attempted but blocked.
	int dequeueBlockCount;
	pthread_mutex_t mutexLock;
	pthread_cond_t full;
	pthread_cond_t empty;

}Queue;

Queue *CreateStringQueue(int size) 
{
	Queue *q;
	q = (Queue *)malloc(sizeof(Queue));
	if(q == NULL) {
		fprintf(stderr, "Malloc fails.\n");
	    return NULL;
    }
	q->array = (char **)malloc(sizeof(char *)*size);
	if(q->array == NULL) {
		fprintf(stderr, "Malloc fails.\n");
	}
	q->front = 0;
	q->rear = 0;
	q->capacity = size;
	q->enqueueCount = 0;
	q->enqueueBlockCount = 0;
	q->dequeueCount = 0;
	q->dequeueBlockCount = 0;
	//pthread_mutex_init(&q->frontLock, NULL);
	pthread_mutex_init(&q->mutexLock, NULL);
	pthread_cond_init(&q->full, NULL);
	pthread_cond_init(&q->empty, NULL);
	return q;

}
int ModIncr(int v, Queue *q) {
	return (v+1)%q->capacity;
}

void *EnqueueString(Queue *q, char *string)
{
	pthread_mutex_lock(&q->mutexLock);
	while(ModIncr(q->rear, q) == q->front) 
	{
		q->enqueueBlockCount++;
		pthread_cond_wait(&q->full, &q->mutexLock);
	}
	if(string == NULL) {
		q->array[q->rear] = NULL;
	} else {
		q->array[q->rear] = (char *)malloc(sizeof(char) * (strlen(string) + 1));
		if(q->array[q->rear] == NULL) 
		{
			fprintf(stderr, "Malloc fails.\n");
            return NULL;
		}
		strcpy(q->array[q->rear], string);
	}
	q->rear = ModIncr(q->rear, q);
	q->enqueueCount++;
	pthread_cond_signal(&q->empty);
	pthread_mutex_unlock(&q->mutexLock);
	return (void*)0;
}

char *DequeueString(Queue *q)
{
	pthread_mutex_lock(&q->mutexLock);
	while(q->rear == q->front) 
	{
		q->dequeueBlockCount++;
		pthread_cond_wait(&q->empty, &q->mutexLock);

	} 
	char *ptr = q->array[q->front];
	q->front = ModIncr(q->front, q);
	q->dequeueCount++;
	pthread_cond_signal(&q->full);
	pthread_mutex_unlock(&q->mutexLock);
	return ptr;
}

void *PrintQueueStats(Queue *q) 
{
	printf("The number of strings enqueued on this queue is %d. \n", q->enqueueCount);
	printf("The number of strings dequeued on this queue is %d. \n", q->dequeueCount);
	printf("The number of times that an enqueue was attempted but blocked is %d. \n", q->enqueueBlockCount);
	printf("The number of times that a dequeue was attempted but blocked is %d. \n", q->dequeueBlockCount);
	return (void*)0;
}
