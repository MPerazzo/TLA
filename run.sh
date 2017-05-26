#!/bin/bash

rm a.out
rm lex.yy.c
lex compiler.l
gcc lex.yy.c -lfl
./a.out testfile.txt

