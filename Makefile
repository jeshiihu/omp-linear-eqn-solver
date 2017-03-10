#http://stackoverflow.com/questions/28546288/omp-h-not-found-os-x-yosemite-not-using-newest-gcc-version
CC=gcc-6

SOURCES = main.c Lab3IO.c datagen.c serialtester.c

all: main datagen serialtester

main: main.c 
	$(CC) -g -Wall -fopenmp -o main main.c Lab3IO.c 

datagen: datagen.c
	$(CC) -g -Wall -o datagen datagen.c Lab3IO.c

serialtester: serialtester.c
	$(CC) -g -Wall -o serialtester serialtester.c Lab3IO.c -lm

clean:
	-rm -f *.o main datagen serialtester

run:
	./main ./datagen ./serialtester
