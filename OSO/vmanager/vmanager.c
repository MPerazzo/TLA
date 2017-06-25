#include <stdlib.h>
#include "vmanager.h"

int vars_values[MAX_VARS] = {0};
unsigned int vars_names[MAX_VARS] = {0};
int tot_vars = 0;

unsigned int hash_var(char *key){
    unsigned int hash, i;
    int len = 10;
    for (hash = i = 0; i < 10; ++i){
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

token_state check_var_exist(char * var_name){

	unsigned int hash_var_name = hash_var(var_name);

	int i;	
	for(i = 0 ; i < tot_vars; i++){
		if (vars_names[i] == hash_var_name)
			return VAR_REPEATED;
	}
	return ACCEPTED;
}

token_state add_varv(char* var_name, int var_val){

	if (check_var_exist(var_name))
		return VAR_REPEATED;

	vars_values[tot_vars] = var_val;
	vars_names[tot_vars] = hash_var(var_name);
	tot_vars++;
	return ACCEPTED;
}

token_state add_var(char* var_name) {
	return add_varv(var_name, 0);
}
