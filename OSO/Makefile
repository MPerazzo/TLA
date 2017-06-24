all:
	$(MAKE) -C compiler
	gcc -o osocompiler compiler/lex.yy.c compiler/y.tab.c -ly vmanager/vmanager.c -I./include
