%define parse.error verbose
%locations

%{
#include <stdio.h>
#include <stdlib.h>
#include "handler.h"

static const char STRING_T[] = "string";
static const char INT_T[] = "int";
static const char FLOAT_T[] = "float";
%}

%union 
{
        char *string;
        char *type;
}
%token RETURN
%token RUN
%token <type> INTEGER_TYPE 
%token <type> FLOAT_TYPE 
%token <type> STRING_TYPE
%token IF FOR WHILE START END
%token LE GE EQ NE OR AND

%token FLOAT
%token INTEGER
%token STRING
%token <string> ID

%right "="
%left OR AND
%left '(' ')'
%left '>' '<' LE GE EQ NE
%left '+' '-'
%left '*' '/'
%right UMINUS
%left '!'
%start INIT

%%

INIT: 			RUN FUNCTIONS P
				;

FUNCTIONS:		  FUNCTIONS D_FUNCTION
				| D_FUNCTION
				;

P:				  STATEMENTS 
				| P STATEMENTS 
				;

STATEMENTS:	
		 		  DECLARATION
				| ASSIGNMENT
				| RETURN OP
				| C_FUNCTION
				| STIF
				| STWHILE
				| STFOR
				;

STIF:			IF '[' E ']' BODY
				;

STWHILE:		WHILE '[' E ']' BODY
				;

STFOR:			FOR '[' S_DECLARATION ';' E ';' ACTION ']' BODY
				;

DECLARATION:	C_DECLARATION ';' | S_DECLARATION ';'
				;

C_DECLARATION:	TYPE ID
				;

S_DECLARATION:  TYPE ID '=' OP
				;

D_FUNCTION:		TYPE ID '('D_ARGS')' BODY
				;

C_FUNCTION:		ID'('C_ARGS')'
				;

C_ARGS:			OP | OP ',' C_ARGS
				;

D_ARGS:			TYPE ID | TYPE ID ',' D_ARGS
				;

TYPE:			INTEGER_TYPE | FLOAT_TYPE | STRING_TYPE
				; 

ASSIGNMENT:		ID '=' OP ';'
				;

ACTION:			INCREASE | DECREASE
				;

INCREASE:		'+' '+' ID | ID '+' '+'
				;

DECREASE:		'-' '-' ID | ID '-' '-'
				;

BODY:			START P END
				;
       
E: 			      E OR E
				| E AND E
				| E '<' E
				| E '>' E
				| E LE E
				| E GE E
				| E EQ E
				| E NE E
				| OP
				;

OP:			  	  OP '+' OP 
				| OP '-' OP
				| OP '*' OP
				| OP '/' OP
				| '(' OP ')'
				| ID
				| INTEGER
				| FLOAT
				| STRING
				;
%%

int yywrap()
{
        return 1;
} 

int main() {
    //printf("Enter the expression:\n");
    yyparse();
}


