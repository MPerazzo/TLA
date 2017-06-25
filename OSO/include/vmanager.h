#ifndef VMANAGER_H
#define VNAMAGER_H

#define MAX_VARS 15

typedef enum { false, true } bool;

typedef struct{
    unsigned int hash;
    char * type;
}var;

unsigned int hash_var(char *key);
bool check_var_exist(char * var_name);
bool check_var_type(char * var_name, char * type);
bool add_var(char* var_name, char* type);

#endif