#include <stdio.h>
#include <stdlib.h>

#define MAX_VARIABLES 100
#define ACCEPTED 0
#define DENNIED 1

unsigned int vars_names[MAX_VARIABLES] = {0}; //usado para verificar que el nombre de la variable haya sido registrada. Se podria eliminar
int tot_varint = 0;

unsigned int hash_variable(char *key);
int check_var_exist(unsigned int hash_var_name);
int add_variable(char* key);
void clear_vars();
int check(char* id);
void printIDNotFound(char* id);