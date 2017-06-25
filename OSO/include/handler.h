#ifndef HANDLER_H
#define HANDLER_H

#include "vmanager.h"

bool handlevAssign(const char * var_name, const char * type, int line);
bool handlevDeclare(const char * var_name, const char * type, int line);
void handlevRep(const int line, const char * var_name);
void handlevMiss(const int line, const char * var_name);
void handlevInvtype(const int line, const char * var_name, const char * wrongtype);

#endif