#ifndef STACK_H
#define STACK_H

#include "tree.h"

void add(struct Node* node);
struct Node* pop();
void printStack();
int get_tot_stack();

#endif