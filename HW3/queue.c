#include <stdlib.h>
#include <stdio.h>
#include "graphNode.h"
#include "queue.h"

/*
* CS 537 Fall 2018 
* Program Assignment 3
* 1,Griff Zhang,xzhang953,griff,xzhang953@wisc.edu,9078214609
* 2,Yanting Liang, yliang73,yliang73,yliang73@wisc.edu,9074460412
*/

void initQueue(Queue *q){
	q->front = NULL;
	q->last = NULL;
	q->size = 0;
}

GraphNode* getNode(Queue* q){
    return q->front;
}

void dequeue(Queue *q){
	q->size--;
	GraphNode* tmp = q->front;
	q->front = q->front->next;
	free(tmp);
}
 
void enqueue(Queue *q, GraphNode* graph_node){
	q->size++;
 
	if (q->front == NULL) {
		// q->front = (GraphNode*) malloc(sizeof(GraphNode));
		q->front = graph_node;
		q->front->next = NULL;
		q->last = q->front;
	} else {
		// q->last->next = (GraphNode*) malloc(sizeof(GraphNode));
        q->last->next = graph_node;
        q->last->next->next = NULL;
        q->last = q->last->next;
	}
}

void printQ(Queue* q){
    while(getNode(q) != NULL){
        printf("size: %d\n", q->size);
        printNode(getNode(q));
		dequeue(q);
    }
}
