#ifndef VMANAGER_H
#define VNAMAGER_H

#define MAX_VARS 15

typedef enum { false, true } bool;

typedef struct{
    unsigned int hash;
    char * type;
}var;

unsigned int hash_var(const char *key);
int check_var_exist(const char * var_name);
bool check_var_type(const char * var_name, const char * type, const int var_position);
bool add_var(const char* var_name, const char* type);

#endif