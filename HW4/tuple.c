#include <stdio.h>
#include "tuple.h"

/*
* CS537 Fall 2018
* Program Assignment 4
* Alexandra maas, maas, amaas4@wisc.edu, 9073795388
* Griff Zhang, griff, xzhang953@wisc.edu, 9078214609
*/

void tuplecpy(Tuple* a, Tuple* b) {  // copy tuple b to tuple a
    a->test = b->test;
    a->len = b->len;
    a->addr = b->addr;
    a->freeStat = b->freeStat;
    a->alloc = b->alloc;
}

void initTuple (Tuple* tuple, size_t size){
    tuple->test = 0;  // test purpose
    tuple->height = 1;
    tuple->len = size;
    tuple->addr = malloc(size);
    tuple->freeStat = 1;
    tuple->alloc = 1;
    tuple->left = NULL;
    tuple->right = NULL;
}

void freeTuple (Tuple* tuple){
    tuple->freeStat = 0;
    free(tuple->addr);
}


