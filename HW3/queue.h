#ifndef QUEUE
#define QUEUE
#include "graphNode.h"

typedef struct{
	GraphNode* front;
	GraphNode* last;
	int size;
} Queue;

void initQueue(Queue *q);
GraphNode* getNode(Queue* q);
void dequeue(Queue *q);
void enqueue(Queue *q, GraphNode* graph_node);
void printQ(Queue* q);

#endif
