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
        freeHelper(ptr, node->left);
    } else if (ptr > (node->addr + node->len)) {
        freeHelper(ptr, node->right);
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

void* realloc537(void* ptr, size_t size) {
    if (ptr != NULL && size == 0) {
        free537(ptr);
        return ptr;
    }
    if (ptr == NULL) return malloc537(size);

    Tuple* temp = find(root, ptr);
    void* val;

    if (size < temp->len) {
        temp->addr = realloc(ptr, size);
        temp->len = size;
        val = temp->addr;
    } else {
        Tuple* tuple = (Tuple*) malloc(sizeof(Tuple));
        initTuple(tuple, size);
        tuplecpy(tuple, temp);
        tuple->len = size;

        root = removeTuple(root, temp);
        root = insertTuple(root, tuple);
        val = tuple->addr;
    }

    return val;
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
            fprintf(stderr, "the pointer is pointing to an already freed memory positon\n");
            exit(-1);
        }
    }
}

void memcheck537(void* ptr, size_t size){
    memHelper(ptr, size, root);
}