# Makefile
main: main.o grafo.o
	gcc -o main main.o grafo.o
main.o: main.c
	gcc -c main.c
grafo.o: grafo.c
	gcc -c grafo.c