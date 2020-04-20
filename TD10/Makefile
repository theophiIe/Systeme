CC = gcc
CFLAGS = -Wall -g -pthread
OFLAGS = -Ofast

run : compile
	./exo2 5 10

compile: clean
	$(CC) $(CFLAGS) $(OFLAGS) exercice1.c -o reduction
	$(CC) $(CFLAGS) $(OFLAGS) exercice2.c -o exo2

	
clean:
	rm -f exo2
	rm -f reduction
	ls

