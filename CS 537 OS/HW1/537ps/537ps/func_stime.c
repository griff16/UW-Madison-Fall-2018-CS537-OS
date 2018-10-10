#include <stdio.h>
#include "func_stime.h"

/*
* CS 537 Fall 2018 
* Program Assignment 1
* Student 1: Xiao Zhang      
* Student 2: Yanting Liang   
*/

void func_stime(char* pid){
	FILE* fp;
	int i;
	char buffer[256] = "";
	char temp[256];
    sprintf(buffer, "/proc/%s/stat", pid);
    fp = fopen(buffer, "r");
    for (i = 0; i<14; i++){
        fscanf(fp, "%s", temp);
    }
    printf("stime=%s ", temp);
    fclose(fp);
}