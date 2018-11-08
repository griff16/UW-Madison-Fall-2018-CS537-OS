#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h> 
#include <unistd.h>
#include "buildGraph.h"
#include "graph.h"
#include "execution.h"

/*
* CS 537 Fall 2018 
* Program Assignment 3
* 1,Griff Zhang,xzhang953,griff,xzhang953@wisc.edu,9078214609
* 2,Yanting Liang, yliang73,yliang73,yliang73@wisc.edu,9074460412
*/

int main(int argc, char* argv[]){

    struct dirent* de;
    DIR* dir = opendir("./");
    FILE* fp;
    Graph* graph;
    char opt;
    opterr = 0;
    char* fileName = NULL;
    int clean = 0;

    int i = 0;
    for(i = 0; i < argc; i++) if(strcmp(argv[i], "clean") == 0) clean = 1;

    while ((opt = getopt(argc, argv, "f:")) != -1){
        if(opt == 'f'){
            fileName = optarg;
            break;
        } else if( opt == '?'){
            if(optopt == 'f') {
                fprintf(stderr, "Option %c needs argument\n", optopt);
                exit(0);
            } else {
                fprintf(stderr, "Unknow option %c. \n", optopt);
                exit(0);
            }
            break;
        }
    }
    
    while ((de = readdir(dir)) != NULL) {  // open the directory and find the makefile
        if (fileName != NULL || strcmp(de -> d_name, "Makefile") == 0 || strcmp(de -> d_name, "makefile") == 0){  // found the makefile
            
            // open the file and check if it opened successfully 
            if (fileName != NULL) {
                fp = fopen(fileName, "r");
            } else {
                fp = fopen(de -> d_name, "r");
            }
            if (fp == NULL){
                fprintf(stderr, "stderr:\n");
                fprintf(stderr, "Cannot open file \n");
                return -1;
            }
            
            // build graph and get the dependency matrix
            graph = buildGraph(fp);
            closedir(dir);

            // process creation and program execution and check loop
            execution(graph, clean);
            break;
        }
    }
    if(de == NULL) {  // when the makefile was not found
        fprintf(stderr, "File not found\n");
        exit(-1);
    }
    return 0;
}
