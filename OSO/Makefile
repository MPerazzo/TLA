all:
	yacc -d osocompiler.y
	lex osocompiler.l 
	gcc -o osocompiler lex.yy.c y.tab.c -ly ansioso.c
