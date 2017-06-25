#include <stdio.h>
#include "handler.h"

void handlevRep(int line, char * var_name) {
	printf("Error at line %d : variable '%s' already defined previously\n", line, var_name);
}

void handlevMiss(int line, char * var_name) {
	printf("Error at line %d : variable '%s' undeclared\n", line, var_name);
}