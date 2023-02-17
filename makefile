CC=gcc
CFLAGS=-g -Wall -o

trab: main.c
	$(CC) main.c $(CFLAGS) trab

run: trab
	./trab

clean: 
	rm trab
