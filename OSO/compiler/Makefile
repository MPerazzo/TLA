all:
	yacc -d osocompiler.y
	lex osocompiler.l
	mv lex.yy.c lib
	mv y.tab.c lib
	mv y.tab.h include
