#ifndef DMANAGER_H
#define DAMANGER_H

#define MAX_VARIABLES 100
#define MAX_FUNCTIONS 100
#define ACCEPTED 0
#define DENNIED 1

unsigned int create_hash(char *key);
int check_var_exist(unsigned int hash_var_name);
int add_variable(char* key);
void clear_vars();
int check(char* id);
void printIDNotFound(char* id);
int check_function_exist(char* function_name);
int add_function(char* function_name);
int check_main_exist();
void printIDAlreadyCreated(char* id);
void to_ret_functions();
void printFunctionNotFound(char* function_name);


#endif