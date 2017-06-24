all:
	$(MAKE) -C compiler
	gcc -o osocompiler compiler/lib/lex.yy.c compiler/lib/y.tab.c -ly vmanager/vmanager.c -I./include -I./compiler/include