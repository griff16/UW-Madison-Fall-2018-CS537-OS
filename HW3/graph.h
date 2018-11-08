#ifndef GRAPH_H
#define GRAPH_H

#include "graphNode.h"

/*
* CS 537 Fall 2018 
* Program Assignment 3
* 1,Griff Zhang,xzhang953,griff,xzhang953@wisc.edu,9078214609
* 2,Yanting Liang, yliang73,yliang73,yliang73@wisc.edu,9074460412
*/

typedef struct{
    int** adj_matrix;  // the adjacency matrix represents dependency
    GraphNode** graph_nodes;  // an array contains all the graphNode and the index represents its position in the adj_matrix
    int graph_size;  // the number of nodes in the graph
}Graph;

void initGraph(Graph* graph);
void printSize(Graph* g);
void printMatrix(Graph* g);
void printNodes(Graph* g);
void printDependent(Graph* g);
void printAll(Graph* g);

#endif 
