all: frequency

frequency: main.o node.o
	gcc -o frequency main.o node.o -Wall

node.o: node.c
	gcc -c node.c -Wall

main.o: main.c
	gcc -c main.c -Wall

clean: 
	rm -f frequency *.o
