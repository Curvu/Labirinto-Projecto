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
    grafo->adj = criaMatriz(vertices, vertices);

    // gera a lista de adjacencia
    /*
        00 01 02 03
        04 05 06 04
        08 09 10 11
        12 13 14 15

        ⁰ ¹ ² ³ ⁴ ...
        ¹ 0 1 0 0
        ² 1 0 1 0
        ³ 0 1 0 1
        ⁴ 0 0 1 0
        ...
    */
    for (int i = 0; i < vertices; i++) {
        if (i % colunas != 0) insereArco(grafo, i, i - 1);             // insere o arco para a esquerda
        if (i % colunas != colunas - 1) insereArco(grafo, i, i + 1);   // insere o arco para a direita
        if (i >= colunas) insereArco(grafo, i, i - colunas);           // insere o arco para cima
        if (i < vertices - colunas) insereArco(grafo, i, i + colunas); // insere o arco para baixo
    }


    // print matriz de adjacencia
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            printf("%d ", grafo->adj[i][j]);
        }
        printf("\n");
    }

    return grafo;
}

int **criaMatriz(int linhas, int colunas) {
    int **matriz = malloc(linhas * sizeof(int*));
    for (int i = 0; i < linhas; i++) {
        matriz[i] = malloc(colunas * sizeof(int));
        for (int j = 0; j < colunas; j++) {
            matriz[i][j] = 0;
        }
    }
    return matriz;
}

int vazio(struct Grafo* grafo) {
    if (grafo == NULL) return 1;
    return 0;
}

void insereArco(Grafo grafo, int v1, int v2) {
    grafo->adj[v1][v2] = 1;
    insereNo(grafo);
}

void retiraArco(Grafo grafo, int v1, int v2) {
    grafo->adj[v1][v2] = 0;
    retiraNo(grafo);
}

void insereNo(Grafo grafo) {
    grafo->numArcos++;
}

void retiraNo(Grafo grafo) {
    grafo->numArcos--;
}

void percuroemprofundidade(Grafo g, int origem){
	// int i,j,pos;
	
	// Pilha p;
	
	// int marcados[g]; //LISTA DE NOS JA VISITADOS 
	
	
	// for(i=0;i < MAXNOS;i++) marcados[i]=0;
    // criarpilha(&p); //INDICIALIZA A PILHA
	// pos = origem;
	// printf("%d",pos);
	// marcados[pos]=1;
	
    // do{
	// 	j=0;
	// 	while(((g.matrizdj[pos][j]==0)||(marcados[j]==1) )&& (j<g.numNos)) j++;
	// 	if(j!=g.numNos){
	// 		if(marcados[j]==0) {
	// 			printf("%d",j);
	// 			marcados[j] = 1;
    //         }
    //         push(pos, &p);
    //         pos=j;
    //     } else{
    //         pos=top(p);
    //         pop(&p);
    //     }
    // } while(!pilhavazia(p));
}