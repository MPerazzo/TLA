#include <stdio.h>
#include <stdlib.h>

#define MAX_VARS 15
#define DENIED 0
#define ACCEPTED 1

void print();
unsigned int hash_variable(char *key);
int check_var_exist(unsigned int hash_var_name);
int add_variable(char* var_name, int var_val);