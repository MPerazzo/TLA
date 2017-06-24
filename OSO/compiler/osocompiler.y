%{
#include <stdio.h>
#include <stdlib.h>
#include <vmanager.h>
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

STIF:			IF '[' E ']' BODY
				;

STWHILE:		WHILE '[' E ']' BODY
				;

STFOR:			FOR '[' C_DECLARATION ';' E ';' ACTION ']' BODY

DECLARATION:	S_DECLARATION ';' | C_DECLARATION ';'
				;

S_DECLARATION:	TYPE ID
				;

C_DECLARATION:	TYPE ID '=' VALUE
				;		

TYPE:			INTEGER_TYPE
				;

VALUE:			INTEGER
				;

ACTION:			INCREASE | DECREASE

INCREASE:		'+' '+' ID | ID '+' '+'

DECREASE:		'-' '-' ID | ID '-' '-'

/* V_INT:			INTEGER_TYPE ID '=' INTEGER ';'	{
													printf("V_INT-> %s : %d\n",$2,$4);
													int value = add_variable($2,$4);
													if(value == DENIED)
														return DENIED;
												}
				;
*/

BODY:		START STATEMENTS END
		;

STATEMENTS:	
		  DECLARATION
		| STIF
		| STWHILE
		| STFOR
		| STATEMENTS DECLARATION
		| STATEMENTS STIF
		| STATEMENTS STWHILE
		| STATEMENTS STFOR
		;
       
E:		ID '=' E
		| E '+' E 
		| E '-' E
		| E '*' E
		| E '/' E
		| E '<' E
		| E '>' E {}
		| E LE E
		| E GE E
		| E EQ E
		| E NE E
		| E OR E
		| E AND E
		| E '+' '+' 
		| E '-' '-'
		| ID  
		| INTEGER
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

