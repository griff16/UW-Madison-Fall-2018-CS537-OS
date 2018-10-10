#include "isnumber.h"
#include <string.h>

/*
* CS 537 Fall 2018 
* Program Assignment 1
* Student 1: Xiao Zhang      
* Student 2: Yanting Liang  
*/

int isnumber(char* arg){
	int i;
	unsigned int a = strlen(arg);
	signed int b = a;
    for (i = 0; i < b; i++){
        if(*(arg + i) < '0' || *(arg + i) > '9') return 0; 
    }
    return 1;
}