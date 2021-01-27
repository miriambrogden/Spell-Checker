CC = gcc
CFLAGS = -Wall -pedantic -std=c99 -Iinclude -c -o

main:
	$(CC) $(CFLAGS) bin/HashMap.o src/HashMap.c
	$(CC) $(CFLAGS) bin/LinkedList.o src/LinkedList.c
	$(CC) $(CFLAGS) bin/Dictionary.o src/Dictionary.c
	$(CC) $(CFLAGS) bin/Main.o src/Main.c
	$(CC) bin/Main.o bin/HashMap.o bin/Dictionary.o bin/LinkedList.o -o bin/runme

test:
	$(CC) $(CFLAGS) bin/HashMap.o src/HashMap.c
	$(CC) $(CFLAGS) bin/LinkedList.o src/LinkedList.c
	$(CC) $(CFLAGS) bin/Dictionary.o src/Dictionary.c
	$(CC) $(CFLAGS) bin/TestMain.o src/TestMain.c
	$(CC) bin/TestMain.o bin/HashMap.o bin/Dictionary.o bin/LinkedList.o -o bin/testme

clean:
	rm bin/*
