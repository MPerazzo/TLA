%define parse.error verbose
%locations

%{
#include <stdio.h>
#include <stdlib.h>
#include "handler.h"
%}

%union 
{
        char *string;
        char *type;
}

%token RUN
%token <type> INTEGER_TYPE 
%token <type> FLOAT_TYPE 
%token <type> STRING_TYPE
%token IF FOR WHILE START END
%token LE GE EQ NE OR AND

%token FLOAT
%token INTEGER
%token <string> ID
%token STRING

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

INIT: 			RUN P
				;

P:				  STATEMENTS 
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

C_DECLARATION:	INTEGER_TYPE ID '=' INT_OP | FLOAT_TYPE ID '=' INT_OP | FLOAT_TYPE ID '=' FLOAT_OP | STRING_TYPE ID '=' STRING
				| STRING_TYPE ID '=' ID {
										
					if (add_var($2)) {
						handlevRep(@4.last_line, $2);
						YYABORT;
					}
				}
				; 

ASSIGNMENT:		ID '=' FLOAT_OP ';' | ID '=' INT_OP ';' | ID '=' STRING ';' {
					
					if (!check_var_exist($1)) {
						handlevMiss(@4.last_line, $1);
						YYABORT;
					}
				}
				;

ACTION:			INCREASE | DECREASE

INCREASE:		'+' '+' ID | ID '+' '+'

DECREASE:		'-' '-' ID | ID '-' '-'

BODY:			START STATEMENTS END
				;
       
E: 				E OR E
				|  E AND E
				| '(' E ')'
				|  INT_E  
				|  FLOAT_E
				;

INT_E:			
				  INT_E '<'  INT_E
				| INT_E '>'  INT_E
				| INT_E  LE  INT_E
				| INT_E  GE  INT_E
				| INT_E  EQ  INT_E
				| INT_E  NE  INT_E
				| INT_E  OR  INT_E
				| INT_E  AND INT_E
				| '(' INT_E ')'
				| ID  
				| INTEGER
				| INT_OP
				;

FLOAT_E:		  
				  FLOAT_E '<'  FLOAT_E
				| FLOAT_E '>'  FLOAT_E
				| FLOAT_E LE   FLOAT_E
				| FLOAT_E GE   FLOAT_E
				| FLOAT_E EQ   FLOAT_E
				| FLOAT_E NE   FLOAT_E
				| FLOAT_E OR   FLOAT_E
				| FLOAT_E AND  FLOAT_E
				| '(' FLOAT_E ')'
				| ID  
				| FLOAT
				| FLOAT_OP
				;

INT_OP:			  INT_OP  '+'  INT_OP 
				| INT_OP '-'  INT_OP
				| INT_OP '*'  INT_OP
				| INT_OP '/'  INT_OP
				| '(' INT_OP ')'
				| ID
				| INTEGER
				;

FLOAT_OP:		FLOAT_OP  '+' FLOAT_OP 
				| FLOAT_OP '-' FLOAT_OP
				| FLOAT_OP '*' FLOAT_OP
				| FLOAT_OP '/' FLOAT_OP
				| '(' FLOAT_OP ')'
				| ID
				| FLOAT
				;

TYPE:			INTEGER_TYPE FLOAT_TYPE STRING_TYPE

%%

int yywrap()
{
        return 1;
} 

int main() {
    //printf("Enter the expression:\n");
    yyparse();
}


