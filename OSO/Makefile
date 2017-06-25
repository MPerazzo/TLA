all:
	cd compiler && \
		make all

	gcc -o osocompiler compiler/lex.yy.c compiler/y.tab.c -ly vmanager.c handler.c -I./include -I./compiler/

	cd compiler && \
	make clean

clean:

	rm -f osocompiler