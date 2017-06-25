#include <stdlib.h>
#include <string.h>
#include "vmanager.h"

var vars[MAX_VARS] = {0};
int tot_vars = 0;

unsigned int hash_var(const char *key){
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

bool check_var_exist(const char * var_name){

	unsigned int hash_var_name = hash_var(var_name);

	int i;	
	for(i = 0 ; i < tot_vars; i++){
		if (vars[i].hash == hash_var_name)
			return false;
	}
	return true;
}

bool check_var_type(const char * var_name, const char * type){

	unsigned int hash_var_name = hash_var(var_name);

	int i;	
	for(i = 0 ; i < tot_vars; i++){
		if (vars[i].hash == hash_var_name && !strcmp(type, vars[i].type))
			return true;
	}
	return false;

}

bool add_var(const char* var_name, const char * type){

	if (check_var_exist(var_name))
		return false;

	vars[tot_vars].hash = hash_var(var_name);
	vars[tot_vars].type = malloc(strlen(type) + 1);
	strcpy(vars[tot_vars].type, type);
	tot_vars++;
	return true;
}