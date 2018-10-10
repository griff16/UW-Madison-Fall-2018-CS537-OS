#include "func_p.h"
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

/*
* CS 537 Fall 2018 
* Program Assignment 1
* Student 1: Xiao Zhang    
* Student 2: Yanting Liang   
*/

void func_p(char* pid){
    int flag = 0;
    DIR* procf;
    struct dirent *dp;
    procf = opendir("/proc");
    while ((dp = readdir(procf)) != NULL){
        if(strcmp(dp -> d_name, pid) == 0){
            printf("%s: ",dp -> d_name);
            flag = 1;
            break;
        }
    }
    if(flag == 0) {
        puts("cannot find the given pid"); 
        exit(-1);
    }
    closedir(procf);   
}