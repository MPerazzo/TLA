#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"

unsigned int create_hash(char *key){
    unsigned int hash, i;
    int len = 10;
    for(hash = i = 0; i < 10; ++i){
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

int check_var_exist(unsigned int hash_var_name){

	if(tot_var_defined == 0){
		return ACCEPTED;
	}

	for(int i = 0 ; i < tot_var_defined; i++){
		if( vars_names[i] == hash_var_name ){
			return DENNIED;
		}
	}
	return ACCEPTED;
}

int check(char* id){
	int hash = create_hash(id);
	
	for(int i = 0 ; i < tot_var_defined ; i++){
		if (vars_names[i] == hash)
			return ACCEPTED; 
	}

	return DENNIED;
}

int add_variable(char* key){
	unsigned int hash = create_hash(key);

	if(check_var_exist(hash) == ACCEPTED){
		vars_names[tot_var_defined] = hash;
		tot_var_defined++;
		return ACCEPTED;
	}else{
		printf("Already define %s variable name before\n",key);
		return DENNIED;
	}

}

void clear_vars(){

	for(int i = 0 ; i < tot_var_defined ; i++){
		vars_names[i] = 0;
	}

	tot_var_defined = 0;

	return;
}

void printIDNotFound(char* id){
	printf("Variable %s was not found\n",id);
}

int check_function_exist(char* function_name){
	int hash = create_hash(function_name);

	if( tot_functions_defined == 0 ){
		return DENNIED; //no existe la funcion!
	}

	for( int i = 0 ; i < tot_functions_defined ; i++){
		if (functions_names[i] == hash){
			return ACCEPTED;
		}
	}

	return DENNIED;

}

int add_function(char* function_name){

	if ( check_function_exist(function_name) == ACCEPTED ){
		return DENNIED;
	}

	int hash = create_hash(function_name);
	functions_names[tot_functions_defined] = hash;
	tot_functions_defined++;
	return ACCEPTED;

}