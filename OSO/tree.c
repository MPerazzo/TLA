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
	sprintf(v,"int %s = %d;",name, value);

	n->type = VINT;
	n->value = v;
	n->tot_nodes = 0;

	add(n);
	return n;
}

struct Node* createNewVariableStringNode(char* name, char* value){

	struct Node* n = malloc(sizeof(struct Node));

	if ( add_variable(name) == DENNIED ){
		return n;
	}

	char* v;
	v = malloc(sizeof(char) * MAX_LENGTH);
	sprintf(v,"string %s = %s;",name, value);

	n->type = VSTRING;
	n->value = v;
	n->tot_nodes = 0;

	add(n);
	return n;
}

struct Node* createIntegerNode(int value){
	struct Node* n = createIntegerNodeNoToStack(value);
	add(n);
	return n;

}

struct Node* createIntegerNodeNoToStack(int value){
	struct Node* n = malloc(sizeof(struct Node));

	n->type = INTEGERNODE;

	char* v;
	v = malloc(sizeof(char) * MAX_LENGTH);
	sprintf(v,"%d",value);
	n->value = v;
	n->tot_nodes = 0;

	return n;

}

struct Node* createStringNode(char* v){
	struct Node* n = createStringNodeNoToStack(v);
	add(n);
	return n;
}

struct Node* createStringNodeNoToStack(char* v){
	struct Node* n = malloc(sizeof(struct Node));

	n->type = STRINGNODE;
	n->value = v;
	n->tot_nodes = 0;

	return n;

}

struct Node* createVariableCreated(char* v){
	struct Node* n = createStringNodeNoToStack(v);
	n->type = VVAR;
	return n;
}


struct Node* createCMPNode(char* symbol, struct Node* left, struct Node* right){
	struct Node* n = malloc(sizeof(struct Node));

	n->type = CMP;

	n->value = symbol;
	n->tot_nodes = 0;
	addLeaves(n,left);
	addLeaves(n,right);

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

struct Node* createMainNode(char* ret, char* function_name){ 
	struct Node* main_node = malloc(sizeof(struct Node));
	main_node->type = MAIN;
	char* v;
	v = malloc(sizeof(char) * MAX_LENGTH);
	sprintf(v,"%s %s", ret, function_name);

	main_node->value = v;

	int t_nodes = get_tot_stack(); 

	while (get_tot_stack() != 0){
		struct Node* node_pop = pop();
		t_nodes--;
		addLeaveAtPosition(main_node, node_pop, t_nodes);
	}

	clear_vars();

	return main_node;

}

struct Node* createFromToNode(char* name, int from, int to){

	struct Node* n = malloc(sizeof(struct Node));

	if ( add_variable(name) == DENNIED ){
		return n;
	}

	n->type=FROMTO;

	addLeaves(n,createIntegerNodeNoToStack(from));
	addLeaves(n,createIntegerNodeNoToStack(to));

	add(n);
	return n;

}

struct Node* createForNode(){
	struct Node* n = malloc(sizeof(struct Node));

	n->type = FORNODE;

	int condition_while = 0;

	while(condition_while == 0){
		struct Node* node_pop = pop();
		
		if(node_pop->type == FROMTO){
			condition_while = 1;
		}

		addLeaves(n,node_pop);

	}

	add(n);
	return n;
}

struct Node* createWhileNode(){

	struct Node* n = malloc(sizeof(struct Node));

	n->type = WHILENODE;

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

struct Node* createFunParam(char* t, char* name){
	struct Node* n = malloc(sizeof(struct Node));

	n->type = FUNPARAM;

	char* v;
	v = malloc(sizeof(char) * MAX_LENGTH);
	sprintf(v,"%s %s", t, name);

	n->value = v;
	n->tot_nodes = 0;

	add(n);
	return n;

}

struct Node* createReadNode(char* var_to_read){
	struct Node* n = malloc(sizeof(struct Node));

	n->type = READNODE;
	n->value = var_to_read;
	n->tot_nodes = 0;

	add(n);
	return n;
}

struct Node* createShowNode(char* tipo, char* var_to_show){
	struct Node* n = malloc(sizeof(struct Node));

	n->type = SHOWNODE;

	char* v = malloc(sizeof(char) * MAX_LENGTH);
	sprintf(v,"%s %s",tipo,var_to_show);
	n->value = v;
	n->tot_nodes = 0;

	add(n);
	return n;
}

struct Node* createSetIntegerNode(char* var_to_set, int val){
	struct Node* n = malloc(sizeof(struct Node));

	n->type = SETNODE;
	char* v = malloc(sizeof(char) * MAX_LENGTH);
	sprintf(v,"%s = %d",var_to_set,val);
	n->value = v;
	n->tot_nodes = 0;

	add(n);
	return n;
}

struct Node* createSetStringNode(char* var_to_set, char* val){
	struct Node* n = malloc(sizeof(struct Node));

	n->type = SETNODE;
	char* v = malloc(sizeof(char) * MAX_LENGTH);
	sprintf(v,"%s = %s",var_to_set,val);
	n->value = v;
	n->tot_nodes = 0;

	add(n);
	return n;
}

struct Node* createCMPAuxiliarNode(char* symbol){
	struct Node* n = malloc(sizeof(struct Node));

	n->type = CMP;
	n->value = symbol;
	n->tot_nodes = 0;

	struct Node* node_pop = pop();
	addLeaves(n,node_pop);

	add(n);
	return n;

}

struct Node* createCMPAuxiliar2Node(char* symbol){
	struct Node* n = malloc(sizeof(struct Node));

	n->type = CMP;
	n->value = symbol;
	n->tot_nodes = 0;

	struct Node* node_pop1 = pop();
	struct Node* node_pop2 = pop();
	addLeaves(n,node_pop1);
	addLeaves(n,node_pop2);

	add(n);
	return n;

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