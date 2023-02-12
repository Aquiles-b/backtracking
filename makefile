CC=gcc
CFLAGS=-g -Wall -o

presentes: natal.c
	$(CC) natal.c $(CFLAGS) presentes

run: presentes
	./presentes

clean: 
	rm presentes
