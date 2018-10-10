#include <stdio.h>
#include "func_v.h"

/*
* CS 537 Fall 2018 
* Program Assignment 1
* Student 1: Xiao Zhang      
* Student 2: Yanting Liang   
*/

void func_v(char* pid){
	FILE* fp;
	char buffer[256] = "";
	char temp[256];
    sprintf(buffer, "/proc/%s/statm", pid);
    fp = fopen(buffer, "r");
    fscanf(fp, "%s", temp);
    printf("vmemory=%s ", temp);
    fclose(fp);
}