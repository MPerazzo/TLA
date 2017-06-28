%{
#include <stdio.h>
#include <stdlib.h>

#include "tree.c"
#include "convert.c"

extern int yylex();
void yyerror(const char *s);

%}

%union 
{
        int number;
        char *string;
}

%token RUN FUNCTION
%token INTEGER_TYPE STRING_TYPE 
%token SHOW SET
%token IF FOR START END WHILE
%token LE GE EQ NE OR AND

%token <number> INTEGER
%token <string> ID
%token <string> TEXT

%right "="
%left OR AND
%left '>' '<' LE GE EQ NE
%left '+' '-'
%left '*' '/'
%right UMINUS
%left '!'
%start INIT

%%

INIT: 	RUN FUNS 	 	{ printf("OK\n"); }
		;

FUNS: 		FUN FUNS
			| FUN
			;

FUN:		FUNCTION INTEGER_TYPE ID '[' PARAMS ']' BODY 	{
															//struct Node* functionNode = createMainNode("int", $3);
															//printTree(functionNode);
															}
			| FUNCTION STRING_TYPE ID '[' PARAMS ']' BODY 	{

															}
			| FUNCTION INTEGER_TYPE ID BODY {
												printf("FUNCION %s\n",$3);
											}

			| FUNCTION STRING_TYPE ID BODY

			;

PARAMS: 	INTEGER_TYPE ID PARAMS 	{ //createFunParam("int", $2);
									}
			| STRING_TYPE ID PARAMS { //createFunParam("string", $2);
									}
			| INTEGER_TYPE ID 		{ //createFunParam("int", $2);	
									}
			| STRING_TYPE ID 		{ //createFunParam("string", $2);
									}
			;

STIF:		IF '[' BOOLEANS ']' BODY	{ //createIfNode();
 										}
			;

STWHILE:	WHILE '[' BOOLEANS ']' BODY 	{ //createWhileNode();
											}

STFOR:		FOR COND_FOR BODY		{ //createForNode();
									}
			;

STREAD:		':' ID ':' ';' {printf("READ\n");}
			;

STPRINT:	SHOW '(' INTEGER_TYPE ')' ID ';' {printf("SHOW\n");}
			| SHOW '(' STRING_TYPE ')' ID ';'
			| SHOW INTEGER ';'
			| SHOW TEXT ';'
			;

COND_FOR: 	'[' ID '=' INTEGER ':' INTEGER ']' 	{ //createFromToNode($2,$4,$6);
												}
			;

BODY:		START STATEMENTS END
			;

DECLARE_VAR: 	STRING_TYPE ID '=' TEXT ';'			{
														printf("string %s = %s \n",$2,$4);
													}
				| INTEGER_TYPE ID '=' INTEGER ';' 	{ 
														printf("int %s = %d\n",$2,$4);
														add_variable($2);
													}
				;

CHANGE_VAR: 	SET ID INTEGER ';' {printf("SET\n");}
				| SET ID TEXT ';'
				;

STATEMENTS:	
			  DECLARE_VAR
			| STIF
			| STFOR
			| STWHILE
			| STREAD
			| STPRINT
			| CHANGE_VAR
			| DECLARE_VAR STATEMENTS
			| STIF STATEMENTS
			| STFOR STATEMENTS
			| STWHILE STATEMENTS
			| STREAD STATEMENTS
			| STPRINT STATEMENTS
			| CHANGE_VAR STATEMENTS
			;
       
BOOL_CONDITION: 
				INTEGER '>' INTEGER
				| INTEGER '<' INTEGER
				| INTEGER '=''=' INTEGER
				| ID '>' INTEGER 				{	printf("%s > %d \n",$1,$3);
													if (check($1) == DENNIED) {printIDNotFound($1); return DENNIED;}
												}
				| ID '<' INTEGER 				{
													if (check($1) == DENNIED) {printIDNotFound($1); return DENNIED;}
												} 
				| ID '=''=' INTEGER 			{
													if (check($1) == DENNIED) {printIDNotFound($1); return DENNIED;}
												}
				| ID '>' ID 					{ 
													if (check($1) == DENNIED) {printIDNotFound($1); return DENNIED;}
													if (check($3) == DENNIED) {printIDNotFound($3); return DENNIED;}
												} 
				| ID '<' ID 					{
													if (check($1) == DENNIED) {printIDNotFound($1); return DENNIED;} 
													if (check($3) == DENNIED) {printIDNotFound($3); return DENNIED;}
												} 
				| ID '=''=' ID 					{
													if (check($1) == DENNIED) {printIDNotFound($1); return DENNIED;} 
													if (check($4) == DENNIED) {printIDNotFound($4); return DENNIED;}
												}
				| INTEGER '>' ID 				{
													if (check($3) == DENNIED) {printIDNotFound($3); return DENNIED;}
												}  
				| INTEGER '<' ID 				{
													if (check($3) == DENNIED) {printIDNotFound($3); return DENNIED;}
												} 
				| INTEGER '=''=' ID 			{
													if (check($4) == DENNIED) {printIDNotFound($4); return DENNIED;}
												}
				;

BOOLEANS:	'!' '(' BOOL_CONDITION ')' {printf("!\n");}
			| '(' BOOL_CONDITION '&''&' BOOL_CONDITION ')'
			| '(' BOOL_CONDITION '|''|' BOOL_CONDITION ')'
			| BOOL_CONDITION
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

