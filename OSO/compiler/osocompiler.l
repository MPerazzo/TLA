%option yylineno

%{
	#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno;
	#include <stdio.h>
	#include <string.h>
    #include "y.tab.h"
%}

alpha [A-Za-z]
digit [0-9]

%%

[\t \n]

run-oso		return RUN;
for			return FOR;
if			return IF;
while		return WHILE;

int			return INTEGER_TYPE;
float 		return FLOAT_TYPE;
string 		return STRING_TYPE;

start 		return START;
end			return END;

{digit}+	{
				yylval.number = atoi(yytext);
				return INTEGER;
			}

{digit}+.{digit}+ { return FLOAT;}

[a-zA-Z][a-zA-Z0-9]* 	{
							yylval.string = strdup(yytext);
							return ID;
						}

\"(\\.|[^\\"])*\" 		{
							return STRING;
						}

"<="		return LE;
">="		return GE;
"=="		return EQ;
"!="		return NE;
"||"		return OR;
"&&"		return AND;
.			return yytext[0];

%%

void yyerror(const char *str)
{
    fprintf(stderr,"Error at line %d : %s\n",yylineno, str);
}