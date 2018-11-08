# Project 3: 537make

The assignment is to write a program that implements Linux command make

## Run the program

1. Compile multiple files, also generate object files and a final prog

```
make

```

3. The program usage is as same as make command

4. Delete all .o files and prog

```
537make clean

```

## Functions

* main (int argc, char* argv[])

    The main function is where to load buildGrapg and execution
    
* buildGraph (FILE* fp)

   open the specified makefile, or the default makefile and build a graph based on it.

* hasNode (char* target, Graph* graph)

   return -1 if no identical node was found else return the index value of the graph_node

* isOutOfDate(GraphNode* node, Graph* graph, int index)

    return 1 when either the specified .o file is not found or the file is out of date

* typedef struct Queue 

    This function acts as a constructor of Queue class.

* typedef struct Graph 
    This function acts as a constructor of Graph class.

* typedef struct GraphNode 
    This function acts as a constructor of GraphNode class.

* void helper(int index, Graph* g, int* visited)

    helper function for dfs function
    
* void dfs(Graph* g, int clean)

    This function implements dfs to the graph
    
* void execution(Graph* graph, int clean){

    This functions executes the makefile commands.