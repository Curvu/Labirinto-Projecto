#include <stdio.h>
#include <stdlib.h>
#include "TADpilha.h"

Pilha criaPilha() {
	return (NULL);
}

void push(Pilha *p, int elem) {
	Pilha aux;
	
	aux = (Pilha) malloc(sizeof(struct no)); // aloca memoria para o no
	aux->elem = elem;
	aux->prox = (*p);
	(*p) = aux; // atualiza o topo da pilha
}

void pop(Pilha *p) {
	Pilha aux;
	
	aux = (*p);
	(*p) = (*p)->prox;
	free(aux);
}
	
int top(Pilha p) {
	return (p->elem);
}

int pilhaVazia(Pilha p) {
	return (p == NULL);
}
