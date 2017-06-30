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

%token RUN FUNCTION EXIT CONST
%token INTEGER_TYPE STRING_TYPE 
%token SET LINE CALL
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
								if(check_main_exist()){
									printf("Compiled OSO\n");
									return true;

								} else{
									printf("Function MAIN missing!\n");
									return false;
								}
							}
		;

FUNS: 		FUN FUNS
			| FUN
			;

FUN:		FUNCTION INTEGER_TYPE ID '[' PARAMS ']' BODY 	{
																printf("Not supported in this version\n");
																return false;
															}
			| FUNCTION STRING_TYPE ID '[' PARAMS ']' BODY 	{
																printf("Not supported in this version\n");
																return true;
															}
			| FUNCTION INTEGER_TYPE ID BODY {
												struct Node* functionNode = createMainNode("void", $3);
												if(!add_function($3)){
													printf("Function %s already defined previously\n",$3);
													return false;
												}
												add_function_stack(functionNode);
											}

			| FUNCTION STRING_TYPE ID BODY	{
												struct Node* functionNode = createMainNode("void", $3);
												if(!add_function($3)){
													printf("Function %s already defined previously\n",$3);
													return false;
												}
												add_function_stack(functionNode);
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
			;								}

STFOR:		FOR COND_FOR BODY		{ createForNode();
									}
			;

STREAD:		':' ID ':' '.' 	{ 
								if(check($2))
									createReadNode($2);
								else{
									printIDNotFound($2);
									return false;
								}
							}
			;

STCONST: 	CONST ID INTEGER '.'	{
 										if(!check($2)){
 											createNewVariableIntegerNode($2, $3);
 										} else {
 											printIDNotFound($2);
 											return false;
 										}
 									}
 
STFUNCTION:	CALL ID '.'	{
							if(check_function_exist($2))
								createCallFunctionNode($2);
							else {
								printFunctionNotFound($2);
								return false;
							}
						}	

STPRINT:	'&' ID '&''.'					 	{	if(check($2))
														createShowStringNode($2);
													else{
														printIDNotFound($2);
														return false;
													}
												}
			| '&' INTEGER '&''.' 				{ 
													createShowIntegerNode($2);
												}
			| '&' TEXT  '&''.'					{ 	
													createShowStringNode($2);
												}
			| '&' LINE '&''.'					{
													createShowStringNode("System.lineSeparator()");
												}
			;

COND_FOR: 	'[' ID '=' INTEGER ':' INTEGER ']' 	{ createFromToNode($2,$4,$6);
												}
			| '[' ID '=' INTEGER ':' ID ']' 	{ 	if(!check($6)){
														printIDNotFound($6);
														return false;
													}
													createFromTo2Node($2,$4,$6);
												}
			| '[' ID '=' ID ':' ID ']' 			{ 	if(!check($6)){
														printIDNotFound($6);
														return false;
													}
													if(!check($4)){
														printIDNotFound($4);
														return false;
													}
													createFromTo3Node($2,$4,$6);
												}
			;

BODY:		START STATEMENTS END
			;

DECLARE_VAR: 	STRING_TYPE ID '=' TEXT '.'				{	if(!check($2))
															createNewVariableStringNode($2,$4);
														else{
															printIDAlreadyCreated($2);
															return false;
														}
													}
				| INTEGER_TYPE ID '=' INT_OPS '.' 	{ 	if(!check($2))
															createNewVariableInteger2Node($2);
														else{
															printIDAlreadyCreated($2);
															return false;
														}
													}
				;

CHANGE_VAR: 	SET ID INT_OPS '.'	{ 	if(check($2)){
											createSetInteger2Node($2);
										} else {
											printIDNotFound($2);
											return false;
										}
									}
				| SET ID TEXT '.'	{	if(check($2))
									 		createSetStringNode($2,$3);
									 	else{
									 		printIDNotFound($2);
									 		return false;
									 	}
									}
				;

STATEMENTS:		DECLARE_VAR
				| STIF
				| STFOR
				| STWHILE
				| STREAD
				| STPRINT
				| CHANGE_VAR
				| STFUNCTION
				| STCONST
				| DECLARE_VAR STATEMENTS
				| STIF STATEMENTS
				| STFOR STATEMENTS
				| STWHILE STATEMENTS
				| STREAD STATEMENTS
				| STPRINT STATEMENTS
				| CHANGE_VAR STATEMENTS
				| STFUNCTION STATEMENTS
				| STCONST STATEMENTS
				;

INT_OPS:		TYPOS '+' INT_OPS			{
												createOPNode("+");
											}
				| TYPOS '-' INT_OPS		{
												createOPNode("-");
											}
				| TYPOS '*' INT_OPS		{
												createOPNode("*");
											}
				| TYPOS '/' INT_OPS		{
												createOPNode("/");
											}
				| TYPOS '%' INT_OPS		{
												createOPNode("%");
											}
				| '(' INT_OPS ')'			{
												createParenthesisNode();
											}

				| TYPOS
				
				;
				
TYPOS:			INTEGER 					{
												createIntegerNode($1);
											}				

				| ID 						{
												if(check($1))
											 		createCallVariableNode($1);
											 	else{
											 		printIDNotFound($1);
											 		return false;
											 	}
											}
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
													if (!check($1)) {
														printIDNotFound($1); 
														return false;
													}
													createCMPNode(">",createVariableCreated($1), createIntegerNodeNoToStack($3));
												}
				| ID '<' INTEGER 				{
													if (!check($1)) {
														printIDNotFound($1); 
														return false;
													}
													createCMPNode("<",createVariableCreated($1), createIntegerNodeNoToStack($3));
												} 
				| ID '=''=' INTEGER 			{
													if (!check($1)) {
														printIDNotFound($1); 
														return false;
													}
													createCMPNode("==",createVariableCreated($1), createIntegerNodeNoToStack($4));
												}
				| ID '>' ID 					{ 
													if (!check($1)) {
														printIDNotFound($1); 
														return false;
													}
													if (!check($3)) {
														printIDNotFound($3); 
														return false;
													}
													createCMPNode(">",createVariableCreated($1), createVariableCreated($3));
												} 
				| ID '<' ID 					{
													if (!check($1)) {
														printIDNotFound($1); 
														return false;
													}
													if (!check($3)) {
														printIDNotFound($3); 
														return false;
													}
													createCMPNode("<",createVariableCreated($1), createVariableCreated($3));
												} 
				| ID '=''=' ID 					{
													if (!check($1)) {
														printIDNotFound($1); 
														return false;
													}
													if (!check($4)) {
														printIDNotFound($4); 
														return false;
													}
													createCMPNode("==",createVariableCreated($1), createVariableCreated($4));
												}
				| INTEGER '>' ID 				{
													if (!check($3)) {
														printIDNotFound($3); 
														return false;
													}
													createCMPNode(">",createIntegerNodeNoToStack($1), createVariableCreated($3));
												}  
				| INTEGER '<' ID 				{
													if (!check($3)) {
														printIDNotFound($3); 
														return false;
													}
													createCMPNode("<",createIntegerNodeNoToStack($1), createVariableCreated($3));
												} 
				| INTEGER '=''=' ID 			{
													if (!check($4)) {
														printIDNotFound($4); 
														return false;
													}
													createCMPNode("==",createIntegerNodeNoToStack($1), createVariableCreated($4));
												}
				;		


BOOLEANS:	'!' '(' BOOL_CONDITION ')' 							{ createCMPAuxiliarNode("!"); } //quiza aca, en yacc en vez de trabajar con BOOL_CONDITION me convenga trabajar con BOOLEANS
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

    if (yyparse()){
    	outputinit();
    	output("import java.util.Scanner;\n");
		output("public class output {\n");
    	to_ret_functions();
    	output("}\n");
    	outputfinish(); 
    }

} 

