#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
/*
* CS 537 Fall 2018 
* Program Assignment 3
* 1,Griff Zhang,xzhang953,griff,xzhang953@wisc.edu,9078214609
* 2,Yanting Liang, yliang73,yliang73,yliang73@wisc.edu,9074460412
*/

void initGraph(Graph* graph){
    int i;
    graph->adj_matrix = (int**) malloc(100 * sizeof(int*));
    for(i = 0; i < 100; i++) graph->adj_matrix[i] = (int*)malloc(100 * sizeof(int));  // create 100x100 adj_matrix
    graph->graph_nodes = (GraphNode**) malloc(sizeof(GraphNode*));  // create 1D array for the graphNode
    graph->graph_size = 0; 
}

void printSize(Graph* g){
    printf("graph size: %d\n", g->graph_size);
}

void printMatrix(Graph* g){
    int i, j;
    for(i = 0; i<g->graph_size; i++){
        printf("row(%d):", i);
        for(j=0; j<g->graph_size; j++){
            printf("%d ", g->adj_matrix[i][j]);
        }
        puts("");
    }
}

void printNodes(Graph* g){
    int i;
    for(i = 0; i<g->graph_size; i++){
        printf("%d: %s\n",i,g->graph_nodes[i]->target );
        printNode(g->graph_nodes[i]);
    }
    puts("");
}

void printDependent(Graph* g){
    int i, j;
    for(i = 0; i < g->graph_size; i++){
        printf("dependency list of %s: ", g->graph_nodes[i]->target);
        for(j = 0; j < g->graph_size; j++){
            if(g->adj_matrix[i][j] == 1){
                printf("%s, ", g->graph_nodes[j]->target);
            }
        }
        puts(" ");
    }
}

void printAll(Graph* g){
    printSize(g);
    printMatrix(g);
    printNodes(g);
    printDependent(g);
}
