run: compile
	./main
	
compile: main.o fct.o
	gcc -Wall -g main.o fct.o -o main
	
main.o: main.c
	gcc -Wall -g -c main.c

fct.o:
	gcc -Wall -g -c fct.c

clean:
	rm -f *.o
	rm -f main
	ls
