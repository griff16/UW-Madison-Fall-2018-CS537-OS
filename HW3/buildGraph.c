#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "graph.h"

/*
* CS 537 Fall 2018 
* Program Assignment 3
* 1,Griff Zhang,xzhang953,griff,xzhang953@wisc.edu,9078214609
* 2,Yanting Liang, yliang73,yliang73,yliang73@wisc.edu,9074460412
*/

// return -1 if no identical node was found else return the index value of the graph_node
int hasNode(char* target, Graph* graph){
    int i;
    for(i = 0; i < graph->graph_size; i++){
        if(strcmp(target, graph->graph_nodes[i]->target) == 0) return i;
    }
    return -1; 
}

// the class to create dependency matrix
Graph* buildGraph(FILE* fp){

    // initializing variables
    Graph* graph = (Graph*)(malloc(sizeof(Graph)));  // the return variable
    initGraph(graph);
    int count = 0;  // count if each line is less than or equals to 1023 characters
    int track = 0;  // the index of the last inserted target (not dependent files)
    char holder = '\0';
    int lineCounter = 1;
    bool hasTarget = true;
    
    // start reading the makefile
    while((holder = fgetc(fp)) != EOF){
        char* temp = malloc(1024 * sizeof(char));
        count++;
        
        if(holder == '\n' || holder == '\r'){  // blank line case
            continue;
        } else if(holder == '#'){  // comment line case
            while((holder != '\n' || holder != EOF) && count < 1024){
                holder = fgetc(fp);
                count++;
            }
        } else if(holder == '\t'){  // command line case
            if (!hasTarget) {
                fprintf(stderr, "%d: Invalid line: Wrong Format.\n", lineCounter);
                exit(-1);
            }
            int i = 0;
            while(count < 1024 && holder != EOF && holder != '\n'){
                if(holder == '\t' || holder == ' ' || holder == '\r'){
                    if(holder != '\r' && temp[i] != ' ') {
                        temp[i] = ' ';
                        i++;
                    }
                } else {
                    temp[i] = holder;
                    i++;
                }
                holder = fgetc(fp);
                count++;
            }
            if(count >= 1024) break;  // chekcing if the line exceeds the limit
            
            if(strlen(temp) == 1 && temp[0] == ' ')continue;
            graph->graph_nodes[track]->command[graph->graph_nodes[track]->command_size] = temp;  // insert the command line to the graphNode
            graph->graph_nodes[track]->command_size++;  // increment the command_size

        } else {  // target line case
            
            // getting the target node
            int i = 0, flag = 0;
            do{
                if(holder == ' ' || holder == '\t'){
                    flag = 1;
                    holder = fgetc(fp);
                    continue;
                }
                if(flag == 1){
                    printf("multiple file");
                    exit(-1);
                }
                temp[i] = holder; 
                holder = fgetc(fp);
                i++; count++;
            }while(holder != ':' && holder != '\n' && count < 1024);  // did not handle the case when there is more than one targets
            if(count >= 1024) break;  // chekcing if the line exceeds the limit

            //checking if the target already exists
            if((track = hasNode(temp, graph)) == -1){  // new graph_node needs to be added
                GraphNode* node = (GraphNode*)malloc(sizeof(GraphNode));
                initGraphNode(node, temp);  // only 10 command lines can be stored 
                graph->graph_nodes[graph->graph_size] = node;
                track = graph->graph_size;
                graph->graph_size++;
            }

            // finding dependency files and update adj_matrix 
            i = 0;
            int index = 0;  // the index of the already existed graph_node in the graph
            char* dependent = (char*)malloc(1024 * sizeof(char));
            while(count < 1024){
                holder = fgetc(fp);
                if(holder == '\r') continue;  // only for windows since window new linwe is \r\n unlike linux \n, later can be taken out
                if(holder == ' ' || holder == '\t' || holder == '\n' || holder == EOF){
                    if((strlen(dependent)== 0 && holder == '\n') || holder == EOF) break;  // case of the line does not have dependecy
                    if(strlen(dependent) != 0){  // handling the cases when the holder is reading continuous space characters or one single character at the either end 
                        if((index = hasNode(dependent, graph)) == -1){  // when the dependency file does NOT exists in the graph
                            GraphNode* node = (GraphNode*)malloc(sizeof(GraphNode));
                            initGraphNode(node, dependent);
                            graph->graph_nodes[graph->graph_size] = node; 
                            graph->adj_matrix[track][graph->graph_size] = 1; 
                            graph->graph_size++;
                        } else {  // when the dependency file already exist in the graph
                            graph->adj_matrix[track][index] = 1; 
                        }
                        if(holder == '\n')break;
                    }
                    dependent = (char*)malloc(1024 * sizeof(char));
                    i = 0;
                } else {  // if it is not space ot tab then keep append the char to dependent
                    dependent[i] = holder;
                    i++;
                }
                count++;
            }
            if(count >= 1024)break;  // chekcing if the line exceeds the 
        }

        // checking if the line exceeds the limit
        if(count >= 1024){
            fprintf(stderr, "%d: Invalid line: this line exceeds buffer size.\n", lineCounter);
            exit(-1);
        }
        lineCounter++;
        count = 0;  // since everytime the big boolean statement will only be run when holder is pointing to the first character of a new line 
    }
    return graph;
}
