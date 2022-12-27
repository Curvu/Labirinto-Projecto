# Makefile
main: main.o grafo.o pilha.o
	gcc -o main main.o grafo.o pilha.o
main.o: main.c
	gcc -c main.c
grafo.o: grafo.c
	gcc -c grafo.c
pilha.o: pilha.c
	gcc -c pilha.c