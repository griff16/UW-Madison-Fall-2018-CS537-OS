/*
* CS537 Fall 2018
* Program Assignment 4
* Alexandra maas, maas, amaas4@wisc.edu, 9073795388
* Griff Zhang, griff, xzhang953@wisc.edu, 9078214609
*/

// inspiration from https://www.geeksforgeeks.org/avl-tree-set-2-deletion/

#include <stdlib.h>
#include <stdio.h>
#include "tuple.h"
#include "AVLTree.h"

int getMax(int a, int b) {
    return (a > b) ? a : b;
}

int getHeight(Tuple *tuple) {
    return tuple == NULL ? 0 : tuple->height;
}

int getFactor(Tuple *tuple) {  // get balance factor of the tuple
    return tuple == NULL ? 0 : (getHeight(tuple->left) - getHeight(tuple->right));
}

Tuple* maxVal(Tuple *tuple) {  // max val on the left sub tree of tuple
    if (tuple->right != NULL) return maxVal(tuple->right);
    else return tuple;
}

Tuple *leftRotate(Tuple *node) {
    Tuple *pivot = node->right;
    Tuple *sub = pivot->left;

    // rotate
    pivot->left = node;
    node->right = sub;

    // update height
    node->height = getMax(getHeight(node->left), getHeight(node->right)) + 1;
    pivot->height = getMax(getHeight(pivot->left), getHeight(pivot->right)) + 1;
    return pivot;
}

Tuple *rightRotate(Tuple *node) {
    Tuple *pivot = node->left;
    Tuple *sub = pivot->right;

    // rotate
    pivot->right = node;
    node->left = sub;

    // update height
    node->height = getMax(getHeight(node->left), getHeight(node->right)) + 1;
    pivot->height = getMax(getHeight(pivot->left), getHeight(pivot->right)) + 1;
    return pivot;
}

Tuple* findTuple(Tuple* root, Tuple* tuple) {  // find the tuple from the tree starting from root
    if (root == NULL || tuple == NULL) return NULL;  // base case 1
    if (tuple->addr == root->addr) return root;  // base case 2

    if (tuple->addr < root->addr) return findTuple(root->left, tuple);  // go left
    else return findTuple(root->right, tuple);  // go right
}

Tuple* find(Tuple* root, void* ptr) {
    if (root == NULL || ptr == NULL) return NULL;  // base case 1
    if (root->addr == ptr) return root;  // base case 2

    if (ptr < root->addr) return find(root->left, ptr);  // go left
    else return find(root->right, ptr);  // go right
}

Tuple* removeTuple(Tuple *root, Tuple *tuple) {  // remove the tuple from the tree starting from root
    if (root == NULL) {
        fprintf(stderr, " removeTuple function is trying to deleting a node that does not exist in the tree\n");
        exit(-1);
    }

    if (tuple->addr < root->addr) root->left = removeTuple(root->left, tuple);  // going left
    else if (tuple->addr > root->addr) root->right = removeTuple(root->right, tuple);  // going right
    else {  // found the tuple and deleting it
        // no child
        if (root->left == NULL && root->right == NULL) {
            freeTuple(root);
            free(root);
            return NULL;
        } else if (root->left == NULL || root->right == NULL) {  // one successor
            freeTuple(root);
            root = root->left ? root->left : root->right;
        } else {  // two successors
            Tuple* temp = maxVal(root->left);
            tuplecpy(root, temp);  // copies addr, len, freestat, alloc
            root->left = removeTuple(root->left, temp);
        }
    }

    // update height
    root->height = getMax(getHeight(root->left), getHeight(root->right)) + 1;

    // balance the node
    int bFactor = getFactor(root);
    if (bFactor == 2 && getFactor(root->left) == 1) {  // left left
        return rightRotate(root);
    }
    if (bFactor == -2 && getFactor(root->right) == -1) {  // right right
        return leftRotate(root);
    }
    if (bFactor == 2 && getFactor(root->left) == -1) {  // left right
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (bFactor == -2 && getFactor(root->right) == 1) {  // right left
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

Tuple* insertTuple(Tuple* tuple, Tuple* newTuple) {

    // finding the right place to insert
    if (tuple == NULL) {
        return (newTuple);
    }
    if (newTuple->addr < tuple->addr) {  // go left
        tuple->left = insertTuple(tuple->left, newTuple);
    } else if (newTuple->addr > tuple->addr) {  // go right
        tuple->right = insertTuple(tuple->right, newTuple);
    } else {  // inserting a pointer that already exists in a tree
        if (tuple->freeStat == 1) {  // is occupied
            fprintf(stderr, "memory conflicts, trying to allocate a memory to an existing memory place\n");
            exit(-1);
        } else {  // allocating to a freed position
            tuple = removeTuple(tuple, newTuple);
            return insertTuple(tuple, newTuple);
        }
    }

    // update node's height
    tuple->height = getMax(getHeight(tuple->left), getHeight(tuple->right)) + 1;

    // balance the tree
    int bFactor = getFactor(tuple);
    if (bFactor == 2 && getFactor(tuple->left) == 1) {  // left left
        return rightRotate(tuple);
    }
    if (bFactor == -2 && getFactor(tuple->right) == -1) {  // right right
        return leftRotate(tuple);
    }
    if (bFactor == 2 && getFactor(tuple->left) == -1) {  // left right
        tuple->left = leftRotate(tuple->left);
        return rightRotate(tuple);
    }
    if (bFactor == -2 && getFactor(tuple->right) == 1) {  // right left
        tuple->right = rightRotate(tuple->right);
        return leftRotate(tuple);
    }
    return tuple;
}

void print2DUtil(Tuple* root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += 10;

    // Process right child first
    print2DUtil(root->right, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%d\n", root->addr);

    // Process left child
    print2DUtil(root->left, space);
}


