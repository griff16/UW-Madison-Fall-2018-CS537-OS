/*
* CS537 Fall 2018
* Program Assignment 4
* Alexandra maas, maas, amaas4@wisc.edu, 9073795388
* Griff Zhang, griff, xzhang953@wisc.edu, 9078214609
*/

#ifndef LIST_H
#define LIST_H

#include "tuple.h"

int getMax(int a, int b);

int getHeight(Tuple *tuple);

int getFactor(Tuple *tuple);

Tuple* maxVal(Tuple *tuple);

Tuple* leftRotate(Tuple *node);

Tuple* rightRotate(Tuple *node);

Tuple* findTuple(Tuple *tuple, Tuple *root);

Tuple* find(Tuple* root, void* ptr);

Tuple* removeTuple(Tuple *tuple, Tuple *root);

Tuple* insertTuple(Tuple *tuple, Tuple *root);

void printTree(Tuple *root);

#endif