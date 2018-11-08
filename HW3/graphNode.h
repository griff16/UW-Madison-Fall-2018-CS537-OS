#ifndef GRAPHNODE_H
#define GRAPHNODE_H

/*
* CS 537 Fall 2018 
* Program Assignment 3
* 1,Griff Zhang,xzhang953,griff,xzhang953@wisc.edu,9078214609
* 2,Yanting Liang, yliang73,yliang73,yliang73@wisc.edu,9074460412
*/

typedef struct node{
    char* target;
    char** command;
    int command_size;
    int type;
    struct node* next;  // only for the queue 
}GraphNode;

void initGraphNode(GraphNode* node, char* target);
void printNode(GraphNode* node);

#endif 
