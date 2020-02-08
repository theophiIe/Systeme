#!/bin/sh
release=0
debug=1

cd /home/user/Bureau/S4/Systeme/TD2

if [ $release -eq 0 ]
then
	gcc -Wall -o mystery-code mystery-code.c
	./mystery-code

elif [ $debug -eq 1 ]
then
	gcc -Wall -o mystery-code mystery-code.c -g
	gdb ./mystery-code
fi
