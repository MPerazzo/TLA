#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "variables.c"
#include "stack.c"

void printTree(struct Node* node){

	int tot = node->tot_nodes;
	printf("ME: %s\n",printNode(node));

	for(int i = 0 ; i < tot ; i++){
		//printf("IMPRIMO HIJO %d\n",i);
		printTree(node->nodes[i]);
	}
	
}

char* printNode(struct Node* n){
	char* to_ret;
	to_ret = malloc(sizeof(char) * MAX_LENGTH);
	sprintf(to_ret, "Type: %d - Value: %s - Total Leaves: %d",n->type,n->value,n->tot_nodes);
	return to_ret;
}

struct Node createNewVariableIntegerNode(char* name, int value){

	struct Node n;

	if ( add_variable(name) == DENNIED ){
		return n;
	}

	char* v;
	v = malloc(sizeof(char) * MAX_LENGTH);
	sprintf(v,"Integer %s = %d;",name, value);

	n.type = VINT;
	n.value = v;
	n.tot_nodes = 0;

	add(&n); //agrega al stack!!!
	//printf("CREATE: %s\n",printNode(&n));
	return n;
}

struct Node* createIntegerNode(int value){
	struct Node* n = malloc(sizeof(struct Node));

	n->type = INTEGER;

	char* v;
	v = malloc(sizeof(char) * MAX_LENGTH);
	sprintf(v,"%d",value);
	n->value = v;
	n->tot_nodes = 0;

	add(n);
	return n;

}

struct Node* createCMPNode(char* symbol){
	struct Node* n = malloc(sizeof(struct Node));

	n->type = CMP;
	struct Node* int2 = pop();
	struct Node* int1 = pop();
	
	n->value = symbol;
	n->tot_nodes = 0;
	addLeaves(n,int1);
	addLeaves(n,int2);

	//printf(" ::: IMPRIMO EL ARBOL EN createCMPNode ::: \n");
	//printTree(&n);
	
	add(n);
	//printf("Ahora agrego al stack\n");
	return n;
}

void addLeaves(struct Node* root, struct Node* leave){
	root->nodes[root->tot_nodes] = leave;
	printf("ADD LEAVES %s\n",printNode(root->nodes[root->tot_nodes]));
	root->tot_nodes++;
	return;
}