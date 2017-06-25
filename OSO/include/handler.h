#ifndef HANDLER_H
#define HANDLER_H

#include "vmanager.h"

void handlevRep(int line, char * varname);
void handlevMiss(int line, char * var_name);
void handlevType(int line, char * var_name, char * wrongtype);

#endif