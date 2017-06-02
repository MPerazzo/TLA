%{
	#include<stdio.h>
	int positiveInt = 0;
	int negativeInt = 0;
	int palabra = 0;

	void functionInitRecognizer(){
		printf("Encontre el comienzo de una funcion\n");
	}

%}

%%

[-][0-9]+ {negativeInt++;}
[+]?[0-9]+ {positiveInt++;}
[a-z][a-z]* {palabra++;}
function [a-z]*[(][)] start {palabra++}

%%

int main(int argc, char*argv[]) {

	if (argc =! 2)
		exit(0);

	// receiving testFile from input
	yyin=fopen(argv[1], "r");

	yylex();

        printf("%s\n",argv[1]);
	printf("Numbers of positive integers %d\n", positiveInt);
	printf("Numbers of negative integers %d\n", negativeInt);
	printf("Numbers of words %d\n", palabra);
}
