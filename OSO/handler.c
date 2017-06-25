#include <stdio.h>
#include "handler.h"

bool handlevAssign(const char * var_name, const char * type, int line) {

	if (!check_var_exist(var_name)) {
		handlevMiss(line, var_name);
		return false;
	}

	if (!check_var_type(var_name, type)) {
		handlevInvtype(line, var_name, type);
		return false;
	}

	return true;
}

bool handlevDeclare(const char * var_name, const char * type, int line) {

	if (!add_var(var_name, type)) {
		handlevRep(line, var_name);
		return false;
	}

	return true;
}


void handlevRep(const int line, const char * var_name) {
	printf("Error at line %d : variable '%s' already defined previously\n", line, var_name);
}

void handlevMiss(const int line, const char * var_name) {
	printf("Error at line %d : variable '%s' undeclared\n", line, var_name);
}

void handlevInvtype(const int line, const char * var_name, const char * wrongtype) {
	printf("Error at line %d : variable '%s' type missmatch. It´s type is not %s\n", line, var_name, wrongtype);
}