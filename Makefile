CC = gcc

SOURCES = main.c Lab3IO.c

all: main

main: server.c 
	gcc -g -Wall -o main main.c Lab3IO.c

clean:
	-rm -f *.o main

run:
	./main