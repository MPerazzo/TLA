#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dmanager.h"
#include "stack.h"

void printTree(struct Node* node){

	int tot = node->tot_nodes;
	printf("%s\n",printNode(node));

	int i;
	for(i = 0 ; i < tot ; i++){
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

	char* to_conv = malloc(sizeof(char) * MAX_CCONV);
	sprintf(to_conv, "Integer %s = %d; \n", name, value);
	n->cconv = to_conv;

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


	char* to_conv = malloc(sizeof(char) * MAX_CCONV);
	sprintf(to_conv, "String %s = \"%s\";\n", name, value);
	n->cconv = to_conv;

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

	char* to_conv = malloc(sizeof(char) * MAX_CCONV);
	sprintf(to_conv,"%d",value);
	n->cconv = to_conv;

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

	n->cconv = v;

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

	char* to_conv = malloc(sizeof(char) * MAX_CCONV);
	sprintf(to_conv, "%s %s %s", left->cconv, symbol, right->cconv);
	n->cconv = to_conv;

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

	char* to_conv = malloc(sizeof(char) * MAX_CCONV);
	sprintf(to_conv, "if ( %s ){ \n", n->nodes[n->tot_nodes - 1]->cconv);
	
	int i;
	for(i = n->tot_nodes - 2 ; i >= 0; i--){
		sprintf(to_conv, "%s %s", to_conv, n->nodes[i]->cconv); //OJO ACA!!! HAY QUE REVISARLO!!!
	}

	sprintf(to_conv, "%s %s \n", to_conv, "}");
	n->cconv = to_conv;

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

	char* to_conv = malloc(sizeof(char) * MAX_CCONV);
	if (strcmp(function_name,"main") == 0 ){
		sprintf(to_conv, "public static void main(String[] args) { \n");	
	} else {
		sprintf(to_conv, "public static %s %s() { \n",ret,function_name);
	}

	while (get_tot_stack() != 0){
		struct Node* node_pop = pop();
		t_nodes--;
		addLeaveAtPosition(main_node, node_pop, t_nodes);
	}

	int i;
	for(i = 0 ; i < main_node->tot_nodes ; i++){
		sprintf(to_conv,"%s %s", to_conv, main_node->nodes[i]->cconv);
	}

	sprintf(to_conv,"%s %s\n",to_conv,"}");
	main_node->cconv = to_conv;

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

	char* to_conv = malloc(sizeof(char) * MAX_CCONV);
	sprintf(to_conv,"int %s = %d ; %s < %d ; %s++",name,from,name,to,name);
	n->cconv = to_conv;

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

	int tot_elems = n->tot_nodes;
	char* to_conv = malloc(sizeof(char) * MAX_CCONV);
	sprintf(to_conv,"for ( %s ) { \n", n->nodes[tot_elems - 1]->cconv);

	int i;
	for(i = tot_elems - 2 ; i >= 0 ; i--){
		sprintf(to_conv,"%s %s",to_conv,n->nodes[i]->cconv);
	}

	sprintf(to_conv,"%s %s\n",to_conv,"}");
	n->cconv = to_conv;

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

	char* to_conv = malloc(sizeof(char) * MAX_CCONV);
	sprintf(to_conv,"scanf();\n");
	n->cconv = to_conv;

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

	char* to_conv = malloc(sizeof(char) * MAX_CCONV);
	sprintf(to_conv,"printf();\n");
	n->cconv = to_conv;	

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

	char* to_conv = malloc(sizeof(char) * MAX_CCONV);
	sprintf(to_conv,"%s = %d\n",var_to_set,val);
	n->cconv = to_conv;	

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

	char* to_conv = malloc(sizeof(char) * MAX_CCONV);
	sprintf(to_conv,"setString();\n");
	n->cconv = to_conv;	

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

	char* to_conv = malloc(sizeof(char) * MAX_CCONV);
	sprintf(to_conv,"%s ( %s )",symbol, node_pop->cconv);
	n->cconv = to_conv;	

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

	char* to_conv = malloc(sizeof(char) * MAX_CCONV);
	sprintf(to_conv,"%s  %s %s\n",node_pop1->cconv,symbol,node_pop2->cconv);
	n->cconv = to_conv;	

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