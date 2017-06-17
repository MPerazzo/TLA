#include <stdio.h>
#include <stdlib.h>
#include "ansioso.h"

int vars_values[MAX_VARS] = {0};
unsigned int vars_names[MAX_VARS] = {0};
int tot_vars = 0;

void print(){
	printf("***%d***\n",tot_vars);
}


unsigned int hash_variable(char *key){
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
	for(int i = 0 ; i < tot_vars; i++){
		if( vars_names[i] == hash_var_name ){
			return DENIED;
		}
	}
	return ACCEPTED;
}

int add_variable(char* var_name, int var_val){

	unsigned int hash_name = hash_variable(var_name);

	if(check_var_exist(hash_name) == DENIED){
		printf("Variable %s already defined previously\n",var_name);
		return DENIED;
	}

	vars_values[tot_vars] = var_val;
	vars_names[tot_vars] = hash_name;
	tot_vars++;
	return ACCEPTED;
}
