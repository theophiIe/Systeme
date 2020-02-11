run: compile
	./main
	
compile: main.o io_file.o
	gcc -Wall -g main.o io_file.o -L. -liof -o main
	
main.o: main.c
	gcc -Wall -g -c main.c

io_file.o:
	gcc -Wall -c -fPIC io_file.c
	ar rcs libiof.a io_file.o
	
run2: compile2
	./main_opt
	
compile2: main_opt.o io_file.o
	gcc -Wall -g main_opt.o io_file.o
	
main_opt.o: main_opt.c
	gcc -Wall -g -c main_opt.c
	
clean:
	rm -f *.o
	rm -f main.o
	rm -f main.opt
	ls
