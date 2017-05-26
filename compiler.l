%{
#include<stdio.h>
int positiveInt = 0;
int negativeInt = 0;
%}

%%

[-][0-9]+ {negativeInt++;}
[+]?[0-9]+ {positiveInt++;}

%%

main(int argc, char*argv[]) {

	if (argc =! 2)
		exit(0);

	// receiving testFile from input
	yyin=fopen(argv[1], "r");

	yylex();

        printf("%s\n",argv[1]);
	printf("Numbers of positive integers %d\n", positiveInt);
	printf("Numbers of negative integers %d\n", negativeInt);
}
