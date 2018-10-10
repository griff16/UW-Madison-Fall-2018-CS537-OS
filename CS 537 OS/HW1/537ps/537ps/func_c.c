#include <stdio.h>
#include "func_c.h"

/*
* CS 537 Fall 2018 
* Program Assignment 1
* Student 1: Xiao Zhang      
* Student 2: Yanting Liang   
*/

void func_c(char* pid){
    FILE* fp;
    char buffer[256] = "";
    char c;
    char temp[1024];
    int counter = 0;
    for(int i = 0; i < 1024; i++) {
		temp[i] = '\0';
    }
    sprintf(buffer, "/proc/%s/cmdline", pid);
    fp = fopen(buffer, "r");
    c = fgetc(fp);
    while(c != EOF) {
		if(c == '\0') temp[counter] = ' ';
		else temp[counter] = c;
		c = fgetc(fp);
		counter++;
    }
    for(int i = counter-1; i >= 0; i--) {
		if(temp[i] == ' ') temp[i] = '\0';
		else break;
    }
    printf("[%s]", temp);
    fclose(fp);
}