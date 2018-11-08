#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <errno.h>
#include "graph.h"
#include "queue.h"

extern int errno ;

/*
* CS 537 Fall 2018 
* Program Assignment 3
* 1,Griff Zhang,xzhang953,griff,xzhang953@wisc.edu,9078214609
* 2,Yanting Liang, yliang73,yliang73,yliang73@wisc.edu,9074460412
*/

// return 1 when either the specified .o file is not found or the file is out of date
int isOutOfDate(GraphNode* node, Graph* graph, int index){
	
	 // target that is not a file and needs to be executed
	char* string = node->target;

    if(strcmp(node->target, "clean") == 0) return 0;
    if(string[strlen(string) - 2] != '.') return 1; 
    
	time_t time_one, time_two;
	char* path_target = malloc((strlen(node->target) + 3) * sizeof(char));
	struct stat statbuff_one, statbuff_two;

	// getting the target last modified time 
	strcpy(path_target, "./");
	strcat(path_target, node->target);
	if ((stat(path_target, &statbuff_one)) == -1){
        //perror("Out of Date: stat");
    }  // double check this part
	
    time_one = statbuff_one.st_mtime;

	// getting the dependency files' last modified times and check if it is out of date
	int i;
	for(i = 0; i < graph->graph_size; i++){
		if(graph->adj_matrix[index][i] == 1){  // found the dependent file
			char* dependent = malloc((strlen(graph->graph_nodes[i]->target) + 3) * sizeof(char));
			strcpy(dependent, "./");
			strcat(dependent, graph->graph_nodes[i]->target);
			if(stat(dependent, &statbuff_two) == -1){
                //perror("Stat, buff 2");
				//printf("cannot open the path: %s", dependent);
                return 1;
			}
			time_two = statbuff_two.st_mtime;
			
			// compare two times 
			if(difftime(time_one, time_two) >= 0) return 1;
		}
	}
	return 0;
}

void helper(int index, Graph* g, int* visited){
    if(visited[index] == 1){
        printf("there is a loop in the makefile\n");
        exit(-1);
    }
    g->graph_nodes[index]->type = 1;
    visited[index] = 1;
    int i;
    for(i = 0; i < g->graph_size; i++){
        //printf("index:%d, i:%d\n", index, i);
        if(g->adj_matrix[index][i] == 1) {
            int* visited_new = (int*)malloc(g->graph_size * sizeof(int));
            int j = 0;
            for(j = 0; j < g->graph_size; j++)visited_new[j] = visited[j]; 
            helper(i, g, visited_new);
        }
    }
}

void dfs(Graph* g, int clean){
    int i, j;
    if(clean == 0){
        for(i = 0; i < g->graph_size; i++){
            if(strcmp(g->graph_nodes[i]->target, "clean") != 0){
                for(j = 0; j < g->graph_size; j++){
                    if(g->adj_matrix[j][i] != 0){
                        break;
                    }
                    int* visited = (int*)malloc(g->graph_size * sizeof(int));
                    memset(visited, 0, g->graph_size * sizeof(int));
                    if(j == g->graph_size - 1)helper(i, g, visited);
                }
            }
        }
    } else {
        int i;
        for(i = 0; i < g->graph_size; i++){
            int* visited = (int*)malloc(g->graph_size * sizeof(int));
            memset(visited, 0, g->graph_size * sizeof(int));
            if(strcmp(g->graph_nodes[i]->target, "clean") == 0)helper(i, g, visited);
        }
    }

}

void execution(Graph* graph, int clean){
    
    // DFS and mark type
    dfs(graph, clean);
    
    // initialization
    int i, j, k, a;
    int flag = 0;  // 0 means there is a loop, 1 means no loop in the matrix
    int** copy_matrix = (int**) malloc(graph->graph_size * sizeof(int*));
    for(i = 0; i < graph->graph_size; i++){
        copy_matrix[i] = malloc(graph->graph_size * sizeof(int));
        for(j = 0; j < graph->graph_size; j++) copy_matrix[i][j] = graph->adj_matrix[i][j];  // copying the adj_matrix
    }
    Queue* q = (Queue*)malloc(sizeof(Queue));  // the order of the execution list
    initQueue(q);

	// loop through the adjacency matrix. Each row represents 
    for(i = 0; i < graph->graph_size; i++){
		for(j = 0; j < graph->graph_size; j++){  // j represents the jth row to be checked
			for(k = 0; k < graph->graph_size; k++){  // k represents the kth column to be checked 
				if((copy_matrix[j][k] == 0)/* || (j == k && (copy_matrix[j][k]) == 1)*/){  // keep checking the row and see if they're all zeros
                    if(k == graph->graph_size - 1) flag = 1; // the jth row is all zeros, and flag to represent no loop
				} else {  // this jth row still has dependency  
				    break;
				}
			}
            if(k == graph->graph_size)break;
		}
		if(flag == 0){  // there is loop
			puts("there is a loop in the makefile");
			exit(-1);
		} else {
            for(a = 0; a < graph->graph_size; a++) copy_matrix[a][j] = 0;
            copy_matrix[j][j] = 1;
        }
        
        // no loop and add the graph node to the exe_list and zero jth ro (except make row j column j to 1), and check if it is out of date
		// returns 1 when either the .o file is not found or is out of date and build the file
        if(isOutOfDate(graph->graph_nodes[j], graph, j) && graph->graph_nodes[j]->type ==1) enqueue(q, graph->graph_nodes[j]); // add the graph node to the list
        flag = 0;
    }

	int p, stat, argc = 0,size = q->size;
    int errornum;
	
	for(i = 0; i < size; i++){
        for(j =0; j < getNode(q)->command_size; j++){
			p = fork();
			if(p < 0){
				puts("invalid argument");
				exit(-1);
			} else if(p == 0){  // child process
                char* argv[30] = {0};
				char* token = strtok(getNode(q)->command[j], " ");
				while(token != NULL){
					argv[argc] =(char*) malloc(strlen(token) * sizeof(char)); 
                    strcpy(argv[argc],token);
					token =  strtok(NULL, " ");
					argc++;
				}
                
                if(execvp(argv[0], argv) == -1){
                    errornum = errno;
                    printf("%d : Error val\n", errornum);
                    perror("exec");
                    exit(-1);
                }
			} else {  // parent processes
                wait(&stat);
				if(WEXITSTATUS(stat) == -1){
					puts("command error");
					exit(-1);
				}
			}
            argc = 0;
		}
        dequeue(q);
	}
}
