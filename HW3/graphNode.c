#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graphNode.h"
/*
* CS 537 Fall 2018 
* Program Assignment 3
* 1,Griff Zhang,xzhang953,griff,xzhang953@wisc.edu,9078214609
* 2,Yanting Liang, yliang73,yliang73,yliang73@wisc.edu,9074460412
*/

void initGraphNode(GraphNode* node, char* target){
    int i = 0;
    node->target = target;
    node->type = 0;
    node->command = (char**)malloc(10 * sizeof(char*));
    for(i = 0; i < 10; i++) node->command[i] = (char*)malloc(1024 * sizeof(char));
    node->command_size = 0;
    node->next = NULL;  // this will only be used during queue in the execution part
}

void printNode(GraphNode* node){
    printf("target: %s\n", node->target);
    printf("type: %d\n", node->type);
    printf("command_size: %d\n", node->command_size);
    int i = 0;
    for(i = 0; i<node->command_size; i++){
        printf("command:\n");
        printf("\t%d: %s\n", i, node->command[i]);
    }
}
