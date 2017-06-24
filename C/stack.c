#include <stdio.h>
#include <stdlib.h>
//#include "tree.c"

#define MAX_STACK_ELEMS 100

struct Node* stack[MAX_STACK_ELEMS];
int tot_elems = 0;
int position = 0;

void add(struct Node* node);
struct Node* pop();
void printStack();

void add(struct Node* node){
	stack[position] = node;
	position++;
	tot_elems++;
}

struct Node* pop(){
	struct Node* n_pop;
	position--;
	tot_elems--;
	return stack[position];
	//printf("En pop(): %s\n",printNode(&stack[position-1]));
}

void printStack(){
	printf("Print Stack: \n");
	for(int i = 0 ; i < position ; i++){
		printf("*** i : %d *** \n",i);
		printTree(stack[i]);
		//printf("%s\n",printNode(&stack[i]));
		printf("******\n");
	}
	return;
}

/*
int main(void){
	struct Node n1 = createNewVariableIntegerNode("v1", 1);
	struct Node n2 = createNewVariableIntegerNode("v2", 2);
	struct Node n3 = createNewVariableIntegerNode("v3", 3);
	add(n1);
	add(n2);
	add(n3);
	printStack();
	struct Node n = pop();
	printStack();
	printf("POPEO: %s\n",printNode(&n));
}
*/