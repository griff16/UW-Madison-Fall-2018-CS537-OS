#include <stdio.h>
#include "func_print.h"
#include "func_p.h"
#include "func_state.h"
#include "func_U.h"
#include "func_stime.h"
#include "func_v.h"
#include "func_c.h"

/*
* CS 537 Fall 2018 
* Program Assignment 1
* Student 1: Xiao Zhang    
* Student 2: Yanting Liang  
*/

void func_print(char* pid, int param[]){
    if (param[0] == 1) func_p(pid);
    if (param[1] == 1) func_state(pid);
    if (param[2] == 1) func_U(pid);
    if (param[3] == 1) func_stime(pid);
    if (param[4] == 1) func_v(pid);
    if (param[5] == 1) func_c(pid);
    printf("\n");
}
