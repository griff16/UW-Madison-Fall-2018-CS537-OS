/*
* CS537 Fall 2018
* Program Assignment 4
* Alexandra maas, maas, amaas4@wisc.edu, 9073795388
* Griff Zhang, griff, xzhang953@wisc.edu, 9078214609
*/

#include <stdlib.h>
#include "tuple.h"

void* malloc537(size_t size);

Tuple* freeHelper(void* ptr, Tuple* node);

void free537(void *ptr);

void* realloc537(void *ptr, size_t size);

void memHelper(void *ptr, size_t size, Tuple *root);

void memcheck537(void *ptr, size_t size);