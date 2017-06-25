#include <stdio.h>
#include <stdlib.h>

#include "tree.h"
#include "variables.c"
#include "stack.c"


void printTree(struct Node* node){

	int tot = node->tot_nodes;
	printf("%s\n",printNode(node));

	for(int i = 0 ; i < tot ; i++){
		printTree(node->nodes[i]);
	}
	
}

char* printNode(struct Node* n){
	printf("Entro a printNode");
	char* to_ret;
	to_ret = malloc(sizeof(char) * MAX_LENGTH);
	sprintf(to_ret, "Type: %d - Value: %s - Total Leaves: %d",n->type,n->value,n->tot_nodes);
	return to_ret;
}

struct Node* createNewVariableIntegerNode(char* name, int value){

	struct Node* n = malloc(sizeof(struct Node));

	if ( add_variable(name) == DENNIED ){
		return n;
	}

	char* v;
	v = malloc(sizeof(char) * MAX_LENGTH);
	sprintf(v,"Integer %s = %d;",name, value);

	n->type = VINT;
	n->value = v;
	n->tot_nodes = 0;

	add(n);
	return n;
}

struct Node* createIntegerNode(int value){
	struct Node* n = malloc(sizeof(struct Node));

	n->type = INTEGERNODE;

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

	add(n);

	return n;
}

struct Node* createIfNode(){
	struct Node* n = malloc(sizeof(struct Node));

	n->type = IFNODE;

	int condition_while = 0;

	while(condition_while == 0){
		struct Node* node_pop = pop();
		
		if(node_pop->type == CMP){
			condition_while = 1;
		}

		addLeaves(n,node_pop);

	}

	add(n);
	return n;
}

struct Node* createMainNode(char* function_name){ 
	struct Node* main_node = malloc(sizeof(struct Node));
	main_node->type = MAIN;
	main_node->value = function_name;

	int t_nodes = get_tot_stack(); 

	while (get_tot_stack() != 0){
		struct Node* node_pop = pop();
		t_nodes--;
		addLeaveAtPosition(main_node, node_pop, t_nodes);
	}

	return main_node;

}

void addLeaveAtPosition(struct Node* root, struct Node* leave, int pos){
	root->nodes[pos] = leave;
	root->tot_nodes++;
	return;
}

void addLeaves(struct Node* root, struct Node* leave){
	addLeaveAtPosition(root,leave,root->tot_nodes);
	return;
}