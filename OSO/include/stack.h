#ifndef STACK_H
#define STACK_H

#define MAX_STACK_ELEMS 500
#define EMPTY_STACK 13

#include "tree.h"

void add(struct Node* node);
struct Node* pop();
void printStack();
int get_tot_stack();

#endif