%{
#include <stdio.h>
#include <stdlib.h>

#include "dmanager.h"
#include "tree.h"
#include "joutput.h"

extern int yylex();
void yyerror(const char *s);

%}

%union 
{
        int number;
        char *string;
}

%token RUN FUNCTION EXIT
%token INTEGER_TYPE STRING_TYPE 
%token SHOW SET
%token IF FOR START END WHILE

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

INIT: 	RUN FUNS EXIT	 	{ 
								printf("OK\n");
							}
		;

FUNS: 		FUN FUNS
			| FUN
			;

FUN:		FUNCTION INTEGER_TYPE ID '[' PARAMS ']' BODY 	{
																printf("Not supported in this version\n");
																return DENNIED;
															}
			| FUNCTION STRING_TYPE ID '[' PARAMS ']' BODY 	{
																printf("Not supported in this version\n");
																return DENNIED;
															}
			| FUNCTION INTEGER_TYPE ID BODY {
												struct Node* functionNode = createMainNode("Integer", $3);
												if(add_function($3) == DENNIED){
													printf("Function %s already defined previously\n",$3);
													return DENNIED;
												}
												output(functionNode->cconv);
											}

			| FUNCTION STRING_TYPE ID BODY	{
												struct Node* functionNode = createMainNode("String", $3);
												if(add_function($3) == DENNIED){
													printf("Function %s already defined previously\n",$3);
													return DENNIED;
												}
												output(functionNode->cconv);
											}

			;

PARAMS: 	INTEGER_TYPE ID PARAMS 	{ createFunParam("int", $2);
									}
			| STRING_TYPE ID PARAMS { createFunParam("string", $2);
									}
			| INTEGER_TYPE ID 		{ createFunParam("int", $2);	
									}
			| STRING_TYPE ID 		{ createFunParam("string", $2);
									}
			;

STIF:		IF '[' BOOLEANS ']' BODY	{ createIfNode();
 										}
			;

STWHILE:	WHILE '[' BOOLEANS ']' BODY 	{ createWhileNode();
											}

STFOR:		FOR COND_FOR BODY		{ createForNode();
									}
			;

STREAD:		':' ID ':' '.' 	{ 
								if(check($2) == ACCEPTED)
									createReadNode($2);
								else
									printIDNotFound($2);
							}
			;

STPRINT:	SHOW '(' INTEGER_TYPE ')' ID '.' { createShowNode("int",$5); }
			| SHOW '(' STRING_TYPE ')' ID '.' { createShowNode("string",$5); }
			| SHOW INTEGER '.' { /*TO DO*/ }
			| SHOW TEXT '.' { createShowNode("string",$2); }
			;

COND_FOR: 	'[' ID '=' INTEGER ':' INTEGER ']' 	{ createFromToNode($2,$4,$6);
												}
			;

BODY:		START STATEMENTS END
			;

DECLARE_VAR: 	STRING_TYPE ID '=' TEXT '.'			{
														createNewVariableStringNode($2,$4);
													}
				| INTEGER_TYPE ID '=' INTEGER '.' 	{ 
														createNewVariableIntegerNode($2,$4);
													}
				;

CHANGE_VAR: 	SET ID INTEGER '.'	{ createSetIntegerNode($2,$3); }
				| SET ID TEXT '.'	{ createSetStringNode($2,$3); }
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
				INTEGER '>' INTEGER 			{
													createCMPNode(">",createIntegerNodeNoToStack($1),createIntegerNodeNoToStack($3));
												}
				| INTEGER '<' INTEGER  			{
													createCMPNode("<",createIntegerNodeNoToStack($1),createIntegerNodeNoToStack($3));
												}
				| INTEGER '=''=' INTEGER 		{
													createCMPNode("==",createIntegerNodeNoToStack($1),createIntegerNodeNoToStack($4));
												}
				| ID '>' INTEGER 				{	
													if (check($1) == DENNIED) {printIDNotFound($1); return DENNIED;}
													createCMPNode(">",createVariableCreated($1), createIntegerNodeNoToStack($3));
												}
				| ID '<' INTEGER 				{
													if (check($1) == DENNIED) {printIDNotFound($1); return DENNIED;}
													createCMPNode("<",createVariableCreated($1), createIntegerNodeNoToStack($3));
												} 
				| ID '=''=' INTEGER 			{
													if (check($1) == DENNIED) {printIDNotFound($1); return DENNIED;}
													createCMPNode("==",createVariableCreated($1), createIntegerNodeNoToStack($4));
												}
				| ID '>' ID 					{ 
													if (check($1) == DENNIED) {printIDNotFound($1); return DENNIED;}
													if (check($3) == DENNIED) {printIDNotFound($3); return DENNIED;}
													createCMPNode(">",createVariableCreated($1), createVariableCreated($3));
												} 
				| ID '<' ID 					{
													if (check($1) == DENNIED) {printIDNotFound($1); return DENNIED;} 
													if (check($3) == DENNIED) {printIDNotFound($3); return DENNIED;}
													createCMPNode("<",createVariableCreated($1), createVariableCreated($3));
												} 
				| ID '=''=' ID 					{
													if (check($1) == DENNIED) {printIDNotFound($1); return DENNIED;} 
													if (check($4) == DENNIED) {printIDNotFound($4); return DENNIED;}
													createCMPNode("==",createVariableCreated($1), createVariableCreated($4));
												}
				| INTEGER '>' ID 				{
													if (check($3) == DENNIED) {printIDNotFound($3); return DENNIED;}
													createCMPNode(">",createIntegerNodeNoToStack($1), createVariableCreated($3));
												}  
				| INTEGER '<' ID 				{
													if (check($3) == DENNIED) {printIDNotFound($3); return DENNIED;}
													createCMPNode("<",createIntegerNodeNoToStack($1), createVariableCreated($3));
												} 
				| INTEGER '=''=' ID 			{
													if (check($4) == DENNIED) {printIDNotFound($4); return DENNIED;}
													createCMPNode("==",createIntegerNodeNoToStack($1), createVariableCreated($4));
												}
				;

BOOLEANS:	'!' '(' BOOL_CONDITION ')' 							{ createCMPAuxiliarNode("!"); }
			| '(' BOOL_CONDITION '&''&' BOOL_CONDITION ')'		{ createCMPAuxiliar2Node("&&"); }
			| '(' BOOL_CONDITION '|''|' BOOL_CONDITION ')'		{ createCMPAuxiliar2Node("||"); }
			| BOOL_CONDITION
			;

%%

int yywrap()
{
        return 1;
} 

int main() {
    //printf("Enter the expression:\n");
    outputinit();
    yyparse();
    outputfinish(); 
} 

