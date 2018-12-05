/*
* CS537 Fall 2018
* Program Assignment 4
* Alexandra maas, maas, amaas4@wisc.edu, 9073795388
* Griff Zhang, griff, xzhang953@wisc.edu, 9078214609
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tuple.h"
#include "AVLTree.h"

static Tuple* root = NULL;

void* malloc537(size_t size) {

    if ((int)size < 0) {
        fprintf(stderr, "trying to malloc a size that is less than 0\n");
        exit(-1);
    }

    if (size == 0) fprintf(stderr, "Warning, trying to allocate a memory size of 0\n");

    Tuple* newTuple = (Tuple*) malloc(sizeof(Tuple));
    initTuple(newTuple, size);

    if (root == NULL) root = insertTuple(NULL, newTuple);
    else root = insertTuple(root, newTuple);


    return newTuple->addr;
}

Tuple* freeHelper(void* ptr, Tuple* node) {  //
    if (node == NULL) {
        fprintf(stderr, "the pointer is freeing a place that has not been allocated yet\n");
        exit(-1);
    } else if (ptr < node->addr) {  // go
        return freeHelper(ptr, node->left);
    } else if (ptr >= (node->addr + node->len)) {
        return freeHelper(ptr, node->right);
    } else {
        if (node->freeStat == 0) {
            fprintf(stderr, "double free\n");
            exit(-1);
        } else if (ptr != node->addr) {
            fprintf(stderr, "ptr is not the first byte of the range of memory that was allocated\n");
            exit(-1);
        } else if (node->len == 0) {
            fprintf(stderr, "freeing memory of size 0\n");
            exit(-1);
        }
    }
    return node;

}

void free537(void* ptr){
    freeTuple(freeHelper(ptr, root));
}

void reallocHelper(void* ptr, size_t size, Tuple* tuple) {
    if (tuple == NULL) return;  // base case

    if (ptr < tuple->addr) reallocHelper(ptr, size, tuple->left);  // go left
    if ((ptr + size) > (tuple->addr + tuple->len)) reallocHelper(ptr, size, tuple->right);  // go right
    if (ptr >= tuple->addr && ptr <= (tuple->addr + tuple->len)) root = removeTuple(root, tuple);  // remove current node
}


void* realloc537(void* ptr, size_t size) {
    if (ptr != NULL && size == 0) {
        free537(ptr);
        return ptr;
    }
    if (ptr == NULL) return malloc537(size);

    void* tempAddr = realloc(ptr, size);

    // find the overlap tuples to remove it
    reallocHelper(tempAddr, size, root);
    print2DUtil(root, 0);

    // create the node
    Tuple* tuple = (Tuple*) malloc(sizeof(Tuple));
    initTuple(tuple, size);
    tuple->len = size;
    tuple->addr = tempAddr;

    // insert and return
    root = insertTuple(root, tuple);
    return tempAddr;
}

void memHelper(void* ptr, size_t size, Tuple* node) {
    if (node == NULL) {
       fprintf(stderr, "the pointer is pointing to a place that has not been allocated yet\n");
       exit(-1);
    } else if (ptr < node->addr) {
        memHelper(ptr, size, node->left);
    } else if (ptr > (node->addr + node->len)) {
        memHelper(ptr, size, node->right);
    } else {  // the pointer is pointing to a place that lies between the node's length
        if (node->freeStat == 0) {  // pointing to a freed position
            fprintf(stderr, "the pointer is pointing to an already freed memory positon\n");
            exit(-1);
        } else if ((ptr + size) > (node->addr + node->len)) {
            fprintf(stderr, "the pointer's size exceeds the allocated memory size\n");
            exit(-1);
        }
    }
}

void memcheck537(void* ptr, size_t size){
    memHelper(ptr, size, root);
}