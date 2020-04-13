CC = gcc
CFLAGS = -Wall -g -pthread
OFLAGS = -Ofast

run : compile
	./reduction 5 10 +

exo1 : compile
	./exo1

compile: clean
	$(CC) $(CFLAGS) $(OFLAGS) exercice1.c -o exo1
	$(CC) $(CFLAGS) $(OFLAGS) reduc.c -o reduction
	
clean:
	rm -f exo1
	rm -f reduction
	ls
