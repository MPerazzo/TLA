%define parse.error verbose
%locations

%{
#include <stdio.h>
#include <stdlib.h>
#include "handler.h"
%}

%union 
{
        int number;
        char *string;
}

%token RUN
%token INTEGER_TYPE
%token IF FOR WHILE START END
%token LE GE EQ NE OR AND

%token <number> INTEGER
%token <string> ID

%right "="
%left OR AND
%left '>' '<' LE GE EQ NE
%left '+' '-'
%left '*' '/'
%right UMINUS
%left '!'
%start INIT

%%

INIT: 			RUN P
				;

P:				STATEMENTS 
				| P STATEMENTS 
				;

STATEMENTS:	
		 		 DECLARATION
				| ASSIGNMENT
				| STIF
				| STWHILE
				| STFOR
				| STATEMENTS ASSIGNMENT
				| STATEMENTS DECLARATION
				| STATEMENTS STIF
				| STATEMENTS STWHILE
				| STATEMENTS STFOR
				;

STIF:			IF '[' E ']' BODY
				;

STWHILE:		WHILE '[' E ']' BODY
				;

STFOR:			FOR '[' C_DECLARATION ';' E ';' ACTION ']' BODY

DECLARATION:	S_DECLARATION ';' | C_DECLARATION ';'
				;

S_DECLARATION:	TYPE ID {
										
					if (add_var($2)) {
						handlevRep(@2.last_line, $2);
						YYABORT;
					}
				}
				;

C_DECLARATION:	TYPE ID '=' E {
										
					if (add_var($2)) {
						handlevRep(@4.last_line, $2);
						YYABORT;
					}
				}
				;

ASSIGNMENT:		ID '=' E ';' {
					
					if (!check_var_exist($1)) {
						handlevMiss(@4.last_line, $1);
						YYABORT;
					}
				}
				;

TYPE:			INTEGER_TYPE
				;

VALUE:			INTEGER
				;

ACTION:			INCREASE | DECREASE

INCREASE:		'+' '+' ID | ID '+' '+'

DECREASE:		'-' '-' ID | ID '-' '-'

BODY:		START STATEMENTS END
		;
       
E:		E '=' E
		| E '<' E
		| E '>' E
		| E '+' E 
		| E '-' E
		| E '*' E
		| E '/' E 
		| E LE E
		| E GE E
		| E EQ E
		| E NE E
		| E OR E
		| E AND E
		| ID  
		| VALUE
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


