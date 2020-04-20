start: clean_file clean run open_file

run: compile
	./main

compile: main.o se_fichier.o
	gcc -Wall -g main.o se_fichier.o -L. -liof -o main

main.o: main.c
	gcc -Wall -g -c main.c

se_fichier.o:
	gcc -Wall -c -fPIC se_fichier.c
	ar rcs libiof.a se_fichier.o


run2: compile2
	./main-opt

compile2: main-opt.o se_fichier.o
	gcc -Wall -g main-opt.o se_fichier.o -L. -liof -o main-opt

main-opt.o: main-opt.c
	gcc -Wall -g -c main-opt.c

clean_file:
	clear
	rm -f *.log *.txt
	ls

open_file:
	sublime *.txt *.log

clean:
	rm -f *.o
	rm -f main
	rm -f main-opt
	ls
