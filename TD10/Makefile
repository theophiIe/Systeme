CC = gcc
CFLAGS = -Wall -g -pthread
OFLAGS = -Ofast

run : compile
	./reduction 5 10 +

compile: clean
	$(CC) $(CFLAGS) $(OFLAGS) exercice1.c -o reduction
	
clean:
	rm -f reduction
	ls

