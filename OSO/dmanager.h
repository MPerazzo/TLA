#include <stdio.h>
#include <stdlib.h>

#define MAX_VARIABLES 100
#define MAX_FUNCTIONS 100
#define ACCEPTED 0
#define DENNIED 1

unsigned int vars_names[MAX_VARIABLES] = {0};
unsigned int functions_names[MAX_FUNCTIONS] = {0};

int tot_functions_defined = 0;
int tot_var_defined = 0;

unsigned int create_hash(char *key);
int check_var_exist(unsigned int hash_var_name);
int add_variable(char* key);
void clear_vars();
int check(char* id);
void printIDNotFound(char* id);
int check_function_exist(char* function_name);
int add_function(char* function_name);
void printIDAlreadyCreated(char* id);
int check_main_exist();