# Project 2: prodcomm

The assignment is to write a program that implements multiple threads environment using monitor to handle strings. Space characters in the strings should be replaced with an asterisk chracters and convert all the letters to upper case. Finally after terminating the program, it should print out all the statistics in the queues.

## Run the program

1. Compile multiple files, also generate object files and a final prog

```
make
```

2. Enter command line with flags

```
Hello  43343 fgt g4j5
```

3. The prog runs our the command, and displays the processed strings. We might expect the output to look like:

```
HELLO*4343*FGT*G4J5
```
4. Delete all .o files and prog

```
make clean
```

## Functions

* main ( )

    The main function is where to read the strings. After the termination of the threads, the program will also print out all the stats about the three queues. 
    
* Munch1 (void *args)

    Munch1 will scan the line and replace each space character (not tabs or newlines) with an asterisk ("*") character. It will then pass the line to thread Munch2 through another queue of character strings.

* Munch2 (void* args)

   Munch2 will scan the line and convert all lower case letters to upper case (e.g., convert "a" to "A"). It will then pass the line to thread Writer though yet another queue of character strings.

* Reader (void* q)

    The Reader thread will read from standard input, one line at a time. Reader will take the each line of the input and pass it to thread Munch1 though a queue of character strings.

* typedef struct Queue 

    This function acts as a constructor of Queue class.

* Queue *CreateStringQueue(int size) 

    This function will initialize all the necessary data inside Queue class
    
* int ModIncr(int v, Queue *q)

    This function increments the pointer of the queue that points to the last index
    
* void *EnqueueString(Queue *q, char *string)

    This functions will add a process to a queue.

* char *DequeueString(Queue *q)

    This function will dequeue a process from a queue

* void *PrintQueueStats(Queue *q)

    This function will print out all the queue stats to console.

* void *Writer(void *q)

    Writer will write the line to standard output.

