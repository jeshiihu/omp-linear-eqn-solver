CC = gcc

SOURCES = main.c Lab3IO.c datagen.c serialtester.c

all: main datagen serialtester

main: main.c 
	gcc -g -Wall -fopenmp -o main main.c Lab3IO.c 

datagen: datagen.c
	gcc -g -Wall -o datagen datagen.c Lab3IO.c

serialtester: serialtester.c
	gcc -g -Wall -o serialtester serialtester.c Lab3IO.c -lm

clean:
	-rm -f *.o main datagen serialtester

run:
	./main ./datagen ./serialtester
