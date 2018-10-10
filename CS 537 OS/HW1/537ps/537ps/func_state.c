#include <stdio.h>
#include "func_state.h"

/*
* CS 537 Fall 2018 
* Program Assignment 1
* Student 1: Xiao Zhang     
* Student 2: Yanting Liang  
*/

void func_state(char* pid){
	FILE* fp;
	char buffer[256] = "";
	char temp[256];
    sprintf(buffer, "/proc/%s/stat", pid);
    fp = fopen(buffer, "r");
    fscanf(fp, "%s %s %s", temp, temp, temp);  // get the third string 
    printf("%s ", temp);
    fclose(fp);
}