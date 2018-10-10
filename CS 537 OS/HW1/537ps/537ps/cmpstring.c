#include <stdlib.h>
#include "cmpstring.h"

/*
* CS 537 Fall 2018 
* Program Assignment 1
* Student 1: Xiao Zhang     
* Student 2: Yanting Liang  
*/

int cmpstring(const void* a, const void* b){  // for qsort
    return (atoi(a)-atoi(b));
}