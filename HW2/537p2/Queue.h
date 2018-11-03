

typedef struct Queue Queue;

//Dynamically allocate a new Queue structure and initialize it with an array of character points 
//of length size. That means you'll malloc the queue structure and then malloc 
//the char * array pointed to from that structure. Also remember to any state 
//and synchronization variables used in this structure.
//The function returns a pointer to the new queue structure.
//For testing purposes, create your Queue's with a size of 10
Queue *CreateStringQueue(int);

int ModIncr(int, Queue *);

//This function places the pointer to the string at the end of queue q. If the queue is full, 
//then this function blocks until there is space available.

void *EnqueueString(Queue *, char *);

//This function removes a pointer to a string from the beginning of queue q. If the queue is empty, 
//then this function blocks until there is a string placed into the queue. This function returns 
//the pointer that was removed from the queue.
char *DequeueString(Queue *);

//This function prints the statistics for this queue (see the next section for details).
void *PrintQueueStats(Queue *);
