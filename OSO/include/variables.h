#ifndef VAR_H
#define VAR_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_VARIABLES 100
#define ACCEPTED 0
#define DENNIED 1

unsigned int hash_variable(char *key);
int check_var_exist(unsigned int hash_var_name);
int add_variable(char* key);

#endif