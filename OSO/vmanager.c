#include <stdlib.h>
#include "vmanager.h"

var vars[MAX_VARS] = {0};
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
		if (vars[i].hash == hash_var_name)
			return VAR_REPEATED;
	}
	return ACCEPTED;
}

token_state add_var(char* var_name){

	if (check_var_exist(var_name))
		return VAR_REPEATED;

	vars[tot_vars].hash = hash_var(var_name);
	tot_vars++;
	return ACCEPTED;
}