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
while 		return WHILE;
function	return FUNCTION;

integer		return INTEGER_TYPE;
string		return STRING_TYPE;
show		return SHOW;
set 		return SET;

start 		return START;
end			return END;


{digit}+	{
			yylval.number = atoi(yytext);
			return INTEGER;
			}

[a-zA-Z][a-zA-Z0-9]* 	{
						yylval.string = strdup(yytext);
						return ID;
						}

-[a-zA-Z0-9?! ]*- 		{
						yylval.string = strdup(yytext);
						return TEXT;
						}

"<="		return LE;
">="		return GE;
"=="		return EQ;
"!="		return NE;
"||"		return OR;
"&&"		return AND;
.			return yytext[0];

%%
