#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

struct Node* stack[MAX_STACK_ELEMS];
int position = 0;

void add(struct Node* node){
	stack[position] = node;
	position++;
}

struct Node* pop(){
	position--;
	return stack[position];
}

int get_tot_stack(){
	return position;
}