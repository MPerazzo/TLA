%{
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

integer		return INTEGER_TYPE;

start 		return START;
end			return END;

[ \t\n]		;


{digit}+	{
			yylval.number = atoi(yytext);
			return INTEGER;
			}

[a-zA-Z][a-zA-Z0-9]* 	{
						yylval.string = strdup(yytext);
						return ID;
						}

"<="		return LE;
">="		return GE;
"=="		return EQ;
"!="		return NE;
"||"		return OR;
"&&"		return AND;
.			return yytext[0];

%%
