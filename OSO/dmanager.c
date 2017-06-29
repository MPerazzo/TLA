#include <stdio.h>
#include <stdlib.h>
#include "dmanager.h"
#include "stack.h"
#include "joutput.h"

unsigned int vars_names[MAX_VARIABLES] = {0};
unsigned int functions_names[MAX_FUNCTIONS] = {0};

int tot_functions_defined = 0;
int tot_var_defined = 0;

unsigned int create_hash(char *key){
    unsigned int hash, i;

    int counter = 0;
    while(key[counter] != '\0'){
    	counter++;
    }

    for(hash = i = 0; i < counter; ++i){
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

	int i;
	for(i = 0 ; i < tot_var_defined; i++){
		if( vars_names[i] == hash_var_name ){
			return DENNIED;
		}
	}
	return ACCEPTED;
}

int check(char* id){
	int hash = create_hash(id);
	
	int i;
	for(i = 0 ; i < tot_var_defined ; i++){
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

	int i;
	for(i = 0 ; i < tot_var_defined ; i++){
		vars_names[i] = 0;
	}

	tot_var_defined = 0;

	return;
}

void printIDNotFound(char* id){
	printf("Variable %s was not found\n",id);
}

void printIDAlreadyCreated(char* id){
	printf("Variable %s was initialized before\n",id);
}

int check_function_exist(char* function_name){
	int hash = create_hash(function_name);

	if( tot_functions_defined == 0 ){
		return DENNIED; //no existe la funcion!
	}

	int i;
	for( i = 0 ; i < tot_functions_defined ; i++){
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
	//printf("el HASH de %s : %d\n",function_name,hash);
	functions_names[tot_functions_defined] = hash;
	tot_functions_defined++;
	return ACCEPTED;

}

int check_main_exist(){
	int i = 0;
	int hash_main = create_hash("main");
	//printf("en check_main_exist: %d\n",hash_main);
	for( i = 0 ; i < tot_functions_defined ; i++){
		if( functions_names[i] == hash_main )
			return ACCEPTED;
	}
	return DENNIED;
}

void to_ret_functions(){
	int c = get_tot_functions();

	for(int i = 0 ; i < c ; i++){
		printf("%s\n",pop_function_stack()->jconv);
	}

}