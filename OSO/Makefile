all:
	cd compiler && \
		make all

	gcc -o osocompiler compiler/lex.yy.c compiler/y.tab.c -ly tree.c variables.c stack.c -I./include -I./compiler/

	cd compiler && \
	make clean

clean:

	rm -f osocompiler