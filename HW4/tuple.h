/*
* CS537 Fall 2018
* Program Assignment 4
* Alexandra maas, maas, amaas4@wisc.edu, 9073795388
* Griff Zhang, griff, xzhang953@wisc.edu, 9078214609
*/

#ifndef TUPLE_H
#define TUPLE_H

#include <stdlib.h>

typedef struct tuple{
    int test;
    int height;  // the height of this tuple
    size_t len;  // stores the length of the allocated memory segment
    void* addr;  // the address to the starting point of the memory
    int freeStat;  // 0 means free, 1 means occupied;
    int alloc;  // 0 means never been alloced, 1 means has been alloced
    struct tuple* left;
    struct tuple* right;
}Tuple;

void tuplecpy(Tuple* a, Tuple* b);
void initTuple (Tuple* tuple, size_t size);
void freeTuple (Tuple* tuple);

#endif