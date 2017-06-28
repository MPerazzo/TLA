#include <stdio.h>
#include <stdlib.h>
#include "variables.h"

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

	if(tot_varint == 0){
		return ACCEPTED;
	}

	for(int i = 0 ; i < tot_varint; i++){
		if( vars_names[i] == hash_var_name ){
			return DENNIED;
		}
	}
	return ACCEPTED;
}

int check(char* id){
	int hash = hash_variable(id);
	
	for(int i = 0 ; i < tot_varint ; i++){
		if (vars_names[i] == hash)
			return ACCEPTED; 
	}

	return DENNIED;
}

int add_variable(char* key){
	unsigned int hash = hash_variable(key);

	if(check_var_exist(hash) == ACCEPTED){
		vars_names[tot_varint] = hash;
		tot_varint++;
		//printf("TOTAL NOW: %d\n", tot_varint);
		return ACCEPTED;
	}else{
		printf("Already define %s variable name before\n",key);
		return DENNIED;
	}

}

void clear_vars(){

	for(int i = 0 ; i < tot_varint ; i++){
		vars_names[i] = 0;
	}

	tot_varint = 0;

	return;
}

void printIDNotFound(char* id){
	printf("Variable %s was not found\n",id);
}