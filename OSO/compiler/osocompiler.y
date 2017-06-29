%{
#include <stdio.h>
#include <stdlib.h>

#include "dmanager.h"
#include "tree.h"
#include "joutput.h"
#include "stack.h"

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
								if( check_main_exist() == ACCEPTED ){
									printf("OK\n");
									printf("TOTAL DE FUNCIONES DECLARADAS: %d \n ", get_tot_functions());

									to_ret_functions();
									return 127;

								} else{
									printf("MAIN NOT CREATED\n");
									YYABORT;
								}
							}
		;

FUNS: 		FUN FUNS
			| FUN
			;

FUN:		FUNCTION INTEGER_TYPE ID '[' PARAMS ']' BODY 	{
																printf("Not supported in this version\n");
																YYABORT;
															}
			| FUNCTION STRING_TYPE ID '[' PARAMS ']' BODY 	{
																printf("Not supported in this version\n");
																YYABORT;
															}
			| FUNCTION INTEGER_TYPE ID BODY {
												struct Node* functionNode = createMainNode("Integer", $3);
												if(add_function($3) == DENNIED){
													printf("Function %s already defined previously\n",$3);
													YYABORT;
												}
												add_function($3); //agrega la funcion al dmanager
												add_function_stack(functionNode);
												//output(functionNode->jconv);
											}

			| FUNCTION STRING_TYPE ID BODY	{
												struct Node* functionNode = createMainNode("String", $3);
												if(add_function($3) == DENNIED){
													printf("Function %s already defined previously\n",$3);
													YYABORT;
												}
												add_function($3);
												add_function_stack(functionNode);
												//output(functionNode->jconv);
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
								else{
									printIDNotFound($2);
									YYABORT;
								}
							}
			;

STPRINT:	SHOW '(' INTEGER_TYPE ')' ID '.' 	{	if(check($5) == ACCEPTED)
														createShowNode("int",$5);
													else{
														printIDNotFound($5);
														YYABORT;
													}
												}
			| SHOW '(' STRING_TYPE ')' ID '.' 	{	if(check($5) == ACCEPTED)
														createShowNode("string",$5);
													else{
														printIDNotFound($5);
														YYABORT;
													}
												}
			| SHOW INTEGER '.' 					{ /*TO DO*/
												}
			| SHOW TEXT '.' 					{ 	createShowNode("string",$2);
												}
			;

COND_FOR: 	'[' ID '=' INTEGER ':' INTEGER ']' 	{ createFromToNode($2,$4,$6);
												}
			;

BODY:		START STATEMENTS END
			;

DECLARE_VAR: 	STRING_TYPE ID '=' TEXT '.'			{	if(check($2) == DENNIED)
															createNewVariableStringNode($2,$4);
														else{
															printIDAlreadyCreated($2);
															YYABORT;
														}
													}
				| INTEGER_TYPE ID '=' INTEGER '.' 	{ 	if(check($2) == DENNIED)
															createNewVariableIntegerNode($2,$4);
														else{
															printIDAlreadyCreated($2);
															YYABORT;
														}
													}
				;

CHANGE_VAR: 	SET ID INTEGER '.'	{ 	if( check($2) == ACCEPTED )
											createSetIntegerNode($2,$3);
										else{
											printIDNotFound($2);
											YYABORT;
										}
									}
				| SET ID TEXT '.'	{	if( check($2) == ACCEPTED )
									 		createSetStringNode($2,$3);
									 	else{
									 		printIDNotFound($2);
									 		YYABORT;
									 	}
									}
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
													if (check($1) == DENNIED) {printIDNotFound($1); YYABORT;}
													createCMPNode(">",createVariableCreated($1), createIntegerNodeNoToStack($3));
												}
				| ID '<' INTEGER 				{
													if (check($1) == DENNIED) {printIDNotFound($1); YYABORT;}
													createCMPNode("<",createVariableCreated($1), createIntegerNodeNoToStack($3));
												} 
				| ID '=''=' INTEGER 			{
													if (check($1) == DENNIED) {printIDNotFound($1); YYABORT;}
													createCMPNode("==",createVariableCreated($1), createIntegerNodeNoToStack($4));
												}
				| ID '>' ID 					{ 
													if (check($1) == DENNIED) {printIDNotFound($1); YYABORT;}
													if (check($3) == DENNIED) {printIDNotFound($3); YYABORT;}
													createCMPNode(">",createVariableCreated($1), createVariableCreated($3));
												} 
				| ID '<' ID 					{
													if (check($1) == DENNIED) {printIDNotFound($1); YYABORT;} 
													if (check($3) == DENNIED) {printIDNotFound($3); YYABORT;}
													createCMPNode("<",createVariableCreated($1), createVariableCreated($3));
												} 
				| ID '=''=' ID 					{
													if (check($1) == DENNIED) {printIDNotFound($1); YYABORT;} 
													if (check($4) == DENNIED) {printIDNotFound($4); YYABORT;}
													createCMPNode("==",createVariableCreated($1), createVariableCreated($4));
												}
				| INTEGER '>' ID 				{
													if (check($3) == DENNIED) {printIDNotFound($3); YYABORT;}
													createCMPNode(">",createIntegerNodeNoToStack($1), createVariableCreated($3));
												}  
				| INTEGER '<' ID 				{
													if (check($3) == DENNIED) {printIDNotFound($3); YYABORT;}
													createCMPNode("<",createIntegerNodeNoToStack($1), createVariableCreated($3));
												} 
				| INTEGER '=''=' ID 			{
													if (check($4) == DENNIED) {printIDNotFound($4); YYABORT;}
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
    outputinit();
	output("public class output {\n");

    int id = yyparse();
    printf("LO QUE DEVUELVE YYPARSE(): %d\n",id);

    output("}\n");
    outputfinish(); 
} 

