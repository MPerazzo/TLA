#include <stdio.h>
#include "stack.h"
#include "handler.h"

bool handle_main() {
	if (check_main_exist()){
		handle_compile_success();
		return true;

	} else{
		handle_main_missing();
		return false;
	}
}

bool handle_funDeclaration(char * id) {
	struct Node* functionNode = createMainNode("void", id);
	if (!add_function(id)) {
		handle_funRep(id);
		return false;
	}
	
	add_function_stack(functionNode);
	return true;
}

bool handle_string_varDeclaration(char * id, char * string) {
	if (!check(id)) {
		createNewVariableStringNode(id, string);
		return true;
	}
	handle_varRep(id);
	return false;
}

bool handle_int_varDeclaration(char * id) {
	if (!check(id)) {
		createNewVariableInteger2Node(id);
		return true;
	}
	handle_varRep(id);
	return false;
}

bool handle_int_set(char * id) {
	if (check(id)){
		createSetInteger2Node(id);
		return true;
	} 
	handle_var_undefined(id);
	return false;
}

bool handle_string_set(char * id, char * string) {
	if (check(id)){
		createSetStringNode(id, string);
		return true;
	} 
	handle_var_undefined(id);
	return false;
}

bool handle_funCall(char * id) {
	if (check_function_exist(id)) {
		createCallFunctionNode(id);
		return true;
	}
	handle_fun_undefined(id);
	return false;
}

bool handle_stdRead(char * id) {
	if (check(id)) {
		createReadNode(id);
		return true;
	}
	handle_var_undefined(id);
	return false;
}

bool handle_var_stdWrite(char * id) {
	if (check(id)) {
		createShowStringNode(id);
		return true;
	}
	handle_var_undefined(id);
	return false;
}

void handle_int_stdWrite(int value) {
	createShowIntegerNode(value);
}

void handle_string_stdWrite(char * string) {
	createShowStringNode(string);
}

bool handle_constInteger(char * id, int value) {
	if (!check(id)){
		createNewVariableIntegerNode(id, value);
		return true;
	} 
	handle_var_undefined(id);
	return false;
}

void handle_int_op(char * op) {
	createOPNode(op);
}

void handle_parenthesis() {
	createParenthesisNode();
}

void handle_if() {
	createIfNode();
}

void handle_while() {
	createWhileNode();
}

void handle_for() {
	createForNode();
}

 void handle_condFor(char * id, int value, int limit) {
 	createFromToNode(id, value, limit);
 }

 bool handle_condFor_varLimit(char * id, int value, char * var_limit) {
 	if (!check(var_limit)){
		handle_var_undefined(var_limit);
		return false;
	}
	createFromTo2Node(id, value, var_limit);
	return true;
 } 

bool handle_condFor_allVar(char * id, char * var_value, char * var_limit) {
	if (!check(var_limit)){
		handle_var_undefined(var_limit);
		return false;
	}
	if (!check(var_value)){
		handle_var_undefined(var_value);
		return false;
	}
	createFromTo3Node(id, var_value, var_limit);
}

void handle_int(int value) {
	createIntegerNode(value);
}

bool handle_var(char * id) {
	if (check(id)) {
		createCallVariableNode(id);
		return true;
	}
	handle_var_undefined(id);
	return false;
}

void handle_int_cmp(char * logic_op, int val1, int val2) {
	createCMPNode(logic_op, createIntegerNodeNoToStack(val1), createIntegerNodeNoToStack(val2));
}

bool handle_int_var_cmp(char * logic_op, char * id, int value) {
	if (!check(id)) {
		handle_var_undefined(id); 
		return false;
	}
	createCMPNode(logic_op, createVariableCreated(id), createIntegerNodeNoToStack(value));
	return true;
}

bool handle_var_var_cmp(char * logic_op, char * id1, char * id2) {
	if (!check(id1)) {
		handle_var_undefined(id1); 
		return false;
	}
	if (!check(id2)) {
		handle_var_undefined(id2); 
		return false;
	}
	createCMPNode(logic_op, createVariableCreated(id1), createVariableCreated(id2));
	return true;
}

void handle_params_notSupported() {
	printf("Function arguments not supported in this version\n");
}

void handle_fun_undefined(char* function_name){
	printf("Function '%s' not defined\n",function_name);
}

void handle_funRep(char * id) {
	printf("Function %s already defined previously\n",id);
}

void handle_var_undefined(char* id){
	printf("Variable '%s' not defined\n",id);
}

void handle_varRep(char* id){
	printf("Variable '%s' already defined\n",id);
}

void handle_compile_success() {
	printf("Compiled OSO\n");
}

void handle_main_missing() {
	printf("Function MAIN missing!\n");
}