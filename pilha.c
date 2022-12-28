#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

Pilha criaPilha() {
	return (NULL);
}

void push(Pilha *p, int elem) {
	Pilha aux;
	
	aux = (Pilha) malloc(sizeof(struct no));
	aux->elem = elem;
	aux->prox = (*p);
	(*p) = aux;
}

void pop(Pilha *p) {
	Pilha aux;
	
	aux = (*p);
	(*p) = (*p)->prox;
	free(aux);
}
	
int top(Pilha p) {
	return(p->elem);
}

int pilhaVazia(Pilha p) {
	return (p == NULL);
}

void imprimePilha(Pilha p) {
	Pilha aux;
	
	aux = p;
	while (aux != NULL) {
		printf("%d ", aux->elem);
		aux = aux->prox;
	}
	printf("\n");
}