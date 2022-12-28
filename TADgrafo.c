#include "TADgrafo.h"
#include "TADpilha.h"
#include <stdio.h>
#include <stdlib.h>

Grafo criaGrafo(int linhas, int colunas) {
    if (linhas <= 0 || colunas <= 0) return NULL; // se o numero de linhas ou colunas for menor ou igual a 0, retorna NULL
    int vertices = linhas * colunas; // variavel auxiliar para guardar o numero de vertices
    
    Grafo grafo = malloc(sizeof(struct Grafo)); // aloca memoria para o grafo
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

    return grafo;
}

int **criaMatriz(int linhas, int colunas) {
    int **matriz = malloc(linhas * sizeof(int*)); // aloca memoria para as linhas
    for (int i = 0; i < linhas; i++) { // aloca memoria para as colunas
        matriz[i] = malloc(colunas * sizeof(int));
        for (int j = 0; j < colunas; j++) matriz[i][j] = 0; // inicializa a matriz com 0
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


void dfs(Grafo grafo, int origem, char **labirinto) {
    int visitados[grafo->numVertices]; // vetor de visitados
    for (int i = 0; i < grafo->numVertices; i++) visitados[i] = 0; // inicializa o vetor de visitados com 0
	// cria uma pilha
    Pilha pilha = criaPilha();
    push(&pilha, origem); // insere o vertice de origem na pilha

    int adjacencia[4] = {-1, -1, -1, -1};
    int v, k, nVisitados = 0;

    while (nVisitados < grafo->numVertices) {
        v = top(pilha); // retira o vertice do topo da pilha
        visitados[v] = 1; // marca o vertice como visitado
        
        nVisitados = 0; // zera o contador de vertices visitados
        for (int i = 0; i < grafo->numVertices; i++) if (visitados[i] == 1) nVisitados++; // conta o numero de vertices visitados

        k = 0; // contador de adjacencias
        for (int i = 0; i < 4; i++) adjacencia[i] = -1; // limpa o vetor adjacencia

        // percorre a matriz de adjacencia do vertice
        for (int i = 0; i < grafo->numVertices; i++) {
            if (grafo->adj[v][i] != 0) { // se o vertice for adjacente ao vertice do topo da pilha
                for (int j = 0; j < 4; j++) {
                    if (adjacencia[j] == -1) {
                        adjacencia[j] = i; // adiciona o vertice adjacente ao vetor de adjacencias
                        k++; // incrementa o contador de adjacencias
                        break;
                    }
                }
            }
        }

        if (k > 0) { // se o vertice tiver adjacencias
            // calcula a direção entre adjacencia[random] e v
            int direcao = -1;
            int proxV = adjacencia[rand() % k]; // escolhe um vertice adjacente aleatoriamente

            if (proxV == v - 1) direcao = 0;                   // esquerda
            else if (proxV == v + 1) direcao = 1;              // direita
            else if (proxV == v - grafo->colunas) direcao = 2; // cima
            else if (proxV == v + grafo->colunas) direcao = 3; // baixo

            if (direcao != -1) push(&pilha, proxV); // insere o vertice adjacente na pilha

            /* Apaga Caminho */
            int linha = (v/grafo->colunas)*2;
            int coluna = (v%grafo->colunas)*4;

            if (direcao == 0) { // esquerda
                if (v % grafo->colunas != 0 && !visitados[v - 1]) { // se não for a primeira coluna e o vertice adjacente a esquerda ainda não foi visitado
                    for (int i = 0; i < 3; i++) labirinto[linha + 1][coluna + i] = ' ';
                }
            } else if (direcao == 1) { // direita
                if (v % grafo->colunas != grafo->colunas - 1 && !visitados[v + 1]) { // se não for a ultima coluna e o vertice adjacente a direita ainda não foi visitado
                    for (int i = 2; i < 5; i++) labirinto[linha + 1][coluna + i] = ' ';
                }
            } else if (direcao == 2) { // cima
                if (v >= grafo->colunas && !visitados[v - grafo->colunas]) { // se não for a primeira linha e o vertice adjacente a cima ainda não foi visitado
                    for (int i = 1; i < 4; i++) labirinto[linha][coluna + i] = ' ';
                }
            } else if (direcao == 3) { // baixo
                if (v < grafo->numVertices - grafo->colunas && !visitados[v + grafo->colunas]) { // se não for a ultima linha e o vertice adjacente a baixo ainda não foi visitado
                    for (int i = 1; i < 4; i++) labirinto[linha + 2][coluna + i] = ' ';
                }
            }
        } else { // se o vertice não tiver adjacencias
            pop(&pilha); // retira o vertice do topo da pilha
        }
    }
}