CC = gcc
CFLAGS = -Wall -g -pthread
OFLAGS = -Ofast

run : compile
	./exo1

compile: clean
	$(CC) $(CFLAGS) $(OFLAGS) exercice1.c -o exo1
	
clean:
	rm -f exo1
	ls
