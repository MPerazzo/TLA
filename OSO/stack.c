#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_ELEMS 500
#define EMPTY_STACK 13


struct Node* stack[MAX_STACK_ELEMS];
int position = 0;

void add(struct Node* node);
struct Node* pop();
void printStack();

void add(struct Node* node){
	stack[position] = node;
	position++;
}

struct Node* pop(){
	position--;
	return stack[position];
}

void printStack(){
	for(int i = 0 ; i < position ; i++){
		printTree(stack[i]);
	}
	printf("\n");
	return;
}

int get_tot_stack(){
	return position;
}