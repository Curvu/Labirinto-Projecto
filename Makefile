# Makefile
main: main.o TADgrafo.o TADpilha.o
	gcc -o main main.o TADgrafo.o TADpilha.o
main.o: main.c
	gcc -c main.c
TADgrafo.o: TADgrafo.c
	gcc -c TADgrafo.c
TADpilha.o: TADpilha.c
	gcc -c TADpilha.c