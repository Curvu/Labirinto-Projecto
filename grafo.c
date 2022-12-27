#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pilha.h"

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
    // for (int i = 0; i < vertices; i++) {
    //     for (int j = 0; j < vertices; j++) {
    //         printf("%d ", grafo->adj[i][j]);
    //     }
    //     printf("\n");
    // }

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

// void dfs(Grafo grafo, int origem, char **labirinto) {
//     int visitados[grafo->numVertices]; // vetor de visitados
//     for (int i = 0; i < grafo->numVertices; i++) visitados[i] = 0; // inicializa o vetor de visitados com 0
// 	// cria uma pilha
//     Pilha pilha = criaPilha();
//     push(&pilha, origem); // insere o vertice de origem na pilha

//     while (!pilhaVazia(pilha)) { // enquanto a pilha nao estiver vazia
//         int vertice = top(pilha); // pega o vertice do topo da pilha
//         pop(&pilha); // remove o vertice do topo da pilha
//         if (!visitados[vertice]) { // se o vertice nao foi visitado
//             visitados[vertice] = 1; // marca como visitado
//             // Apaga o caminho, coluna ou linha



            
//             for (int i = 0; i < grafo->numVertices; i++) { // para cada vertice adjacente ao vertice atual
//                 if (grafo->adj[vertice][i]) { // se o vertice for adjacente
//                     push(&pilha, i); // insere o vertice adjacente na pilha
//                 }
//             }
//         }
//     }
// }