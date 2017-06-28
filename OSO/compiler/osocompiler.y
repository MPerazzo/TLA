%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex();
void yyerror(const char *s);

%}

%union 
{
        int number;
        char *string;
}

%token RUN
%token INTEGER_TYPE
%token IF FOR START END WHILE LOOP
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

INIT: 	RUN STATEMENTS 	{
							struct Node* main = createMainNode("FUNCION");
							printTree(main);
						}
		;

STIF:		IF '[' E ']' BODY { createIfNode(); }
		;

V_INT:		INTEGER_TYPE ID '=' INTEGER ';'	{ createNewVariableIntegerNode($2,$4); }
		;

BODY:		START STATEMENTS END {}
		;

STFOR:		FOR COND_FOR BODY { createForNode(); }
		;

STWHILE:	WHILE '['E']' BODY { createWhileNode(); }
		;

COND_FOR: '[' ID '=' INTEGER ':' INTEGER ']' { createFromToNode($2,$4,$6); }


STATEMENTS:	
		  V_INT
		| STIF
		| STFOR
		| STWHILE
		| V_INT STATEMENTS
		| STIF STATEMENTS
		| STFOR STATEMENTS
		| STWHILE STATEMENTS { }
		;
       
E:		ID '=' E
		| E '+' E 
		| E '-' E
		| E '*' E
		| E '/' E
		| E '<' E
		| E '>' E 			{ createCMPNode(">"); /*printf(">\n");*/ }
		| E LE E
		| E GE E
		| E EQ E
		| E NE E
		| E OR E
		| E AND E
		| E '+' '+' 
		| E '-' '-'
		| ID 				
		| INTEGER 			{ createIntegerNode($1); /*printf("%d\n",$1);*/}
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

