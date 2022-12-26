#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Grafo criaGrafo(int linhas, int colunas) {
    if (linhas <= 0 || colunas <= 0) return NULL; // se o numero de linhas ou colunas for menor ou igual a 0, retorna NULL
    int vertices = linhas * colunas; // variavel auxiliar para guardar o numero de vertices
    
    Grafo grafo = malloc(sizeof(struct Grafo));
    grafo->linhas = linhas;
    grafo->colunas = colunas;
    grafo->numVertices = vertices;
    grafo->numArcos = 0;
    grafo->adj = malloc(vertices * sizeof(struct No*)); // aloca a lista de adjacencia
    for (int i = 0; i < vertices; i++) grafo->adj[i] = NULL; // inicializa a lista de adjacencia com NULL

    // gera a lista de adjacencia
    /*
        00 01 02 03
        04 05 06 04
        08 09 10 11
        12 13 14 15

        00 -> 01 -> 04
        01 -> 00 -> 02 -> 05
        02 -> 01 -> 03 -> 06
        03 -> 02 -> 07
        04 -> 00 -> 05 -> 08
        05 -> 01 -> 04 -> 06 -> 09
        06 -> 02 -> 05 -> 07 -> 10
        07 -> 03 -> 06 -> 11
        08 -> 04 -> 09 -> 12
        09 -> 05 -> 08 -> 10 -> 13
        10 -> 06 -> 09 -> 11 -> 14
        11 -> 07 -> 10 -> 15
        12 -> 08 -> 13
        13 -> 09 -> 12 -> 14
        14 -> 10 -> 13 -> 15
        15 -> 11 -> 14
    */
    for (int i = 0; i < vertices; i++) {
        if (i % colunas != 0) insereArco(grafo, i, i - 1); // insere o arco para a esquerda
        if (i % colunas != colunas - 1) insereArco(grafo, i, i + 1); // insere o arco para a direita
        if (i >= colunas) insereArco(grafo, i, i - colunas); // insere o arco para cima
        if (i < vertices - colunas) insereArco(grafo, i, i + colunas); // insere o arco para baixo
    }


    // printa a lista de adjacencia
    for (int i = 0; i < vertices; i++) {
        printf("%02d", i);
        No no = grafo->adj[i];
        while (no != NULL) {
            printf(" -> %02d", no->atual);
            no = no->prox;
        }
        printf("\n");
    }

    return grafo;
}

int vazio(struct Grafo* grafo) {
    if (grafo == NULL) return 1;
    return 0;
}

void insereArco(Grafo grafo, int v1, int v2) {
    grafo->adj[v1] = insereNo(v2, grafo->adj[v1]); // insere o arco na lista de adjacencia
    grafo->numArcos++; // incrementa o numero de arcos
}

No insereNo(int v, No prox) {
    No novo = malloc(sizeof(struct no));
    novo->atual = v;
    novo->prox = prox;
    return novo;
}