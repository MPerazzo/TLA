#ifndef VMANAGER_H
#define VNAMAGER_H

#define MAX_VARS 15

typedef enum {ACCEPTED=0, DENIED=100, VAR_REPEATED=101} token_state;

typedef struct{
    unsigned int hash;
    char * type;
}var;

unsigned int hash_var(char *key);
token_state check_var_exist(char * var_name);
token_state add_var(char* var_name);

#endif