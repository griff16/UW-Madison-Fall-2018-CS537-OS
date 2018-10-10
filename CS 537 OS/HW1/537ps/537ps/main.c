#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include "func_all.h"
#include "func_print.h"
#include "isnumber.h"

/*
* CS 537 Fall 2018 
* Program Assignment 1
* Student 1: Xiao Zhang      
* Student 2: Yanting Liang   
*/

int param[6] = {0, 0, 1, 0, 0, 1};  // index 0,1,2,3,4,5 means p, s, U, S, v, c. 0 means off 1 means on

int main (int argc, char* argv[]){
    opterr = 0;
    char opt;
    char* pid = NULL;
    int param[6] = {0, 0, 1, 0, 0, 1};  // index 0,1,2,3,4,5 means p, s, U, S, v, c. 0 means off 1 means on
    while ((opt = getopt(argc, argv, "p:s::U::S::v::c::")) != -1){
        switch (opt) {
            case 'p':
                if(optarg != NULL &&  isnumber(optarg) == 0) {
                    fprintf(stderr, "Invalid Argument for -%c.\n", opt);
                    exit(0);
                } else {
                    param[0] = 1;
                    pid = optarg;
                }
                break;
            case 's': 
                if(optarg == NULL) param[1] = 1;
                else if(optarg != NULL && strcmp(optarg, "-") != 0) {
                    fprintf(stderr, "Invalid Argument for -%c.\n", opt);
                    exit(0);
                }
                break;
            case 'U':
                if(optarg != NULL && strcmp(optarg, "-") == 0) param[2] = 0;
                else if(optarg != NULL && strcmp(optarg, "-") != 0) {
                    fprintf(stderr, "Invalid Argument for -%c.\n", opt);
                    exit(0);
                }
                break;
            case 'S':
                if(optarg == NULL) param[3] = 1;
                else if(optarg != NULL && strcmp(optarg, "-") != 0) {
                    fprintf(stderr, "Invalid Argument for -%c.\n", opt);
                    exit(0);
                }
                break;
            case 'v':
                if(optarg == NULL) param[4] = 1;
                else if(optarg != NULL && strcmp(optarg, "-") != 0) {
                    fprintf(stderr, "Invalid Argument for -%c.\n", opt);
                    exit(0);
                }   
                break;
            case 'c':
                if(optarg != NULL && strcmp(optarg, "-") == 0) param[5] = 0; 
                else if(optarg != NULL && strcmp(optarg, "-") != 0) {
                    fprintf(stderr, "Invalid Argument for -%c.\n", opt);
                    exit(0);
            }
                break;
            case '?':
                if(optopt == 'p') {
                    fprintf(stderr, "Option %c needs argument\n", optopt);
                    exit(0);
                } else {
                    fprintf(stderr, "Unknow option %c. \n", optopt);
                    exit(0);
                }
                break;
            default: 
                abort();
        }
    }

    for(int index = optind; index < argc; index++) {
        printf("Invalid input flag %s\n", argv[index]);
        exit(0);
    }

    // determines prints out everything or given pid
    if(param[0] == 0){
        func_all(param);
    } else {
        func_print(pid, param);
    }
            

}
