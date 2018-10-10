#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include "func_all.h"
#include "func_p.h"
#include "func_print.h"
#include "cmpstring.h"
#include "isnumber.h"

/*
* CS 537 Fall 2018 
* Program Assignment 1
* Student 1: Xiao Zhang      
* Student 2: Yanting Liang  
*/

void func_all(int param[]){
    DIR* procf;
    FILE* fp;
    int i;
    int count = 0;
    struct dirent *dp;
    char buf[1024];  
    char* ary[sizeof(char*)];  
    char temp[256];

    // load the user processes to an ary
    procf = opendir("/proc");
    while ((dp = readdir(procf)) != NULL){
        if(isnumber(dp -> d_name) == 1){  // found the pid) {  // found the number pid
           
            // extracting uid info
            sprintf(buf, "/proc/%s/status", dp -> d_name);
            fp = fopen(buf, "r");
            for (i = 0; i < 9; i++){  // get to the uid element
                fgets(temp, 50, fp);
            }
            fscanf(fp, "%s %s", temp, temp);  // extract second element in the line
            if ((signed)getuid() == atoi(temp)){  // checking uid are the same 
                ary[count] = dp -> d_name;  // if same load it to the ary
                count++;
            }
            fclose(fp);
        } 
    }

    // sorting ary in asceding order
    qsort(ary, count, sizeof(char*), cmpstring);

    int j;
    for(j = 0; j < count; j++){
        func_p(ary[j]);
        func_print(ary[j], param);
    }
}