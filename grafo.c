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


void dfs(Grafo grafo, int origem, char **labirinto) {
    int visitados[grafo->numVertices]; // vetor de visitados
    for (int i = 0; i < grafo->numVertices; i++) visitados[i] = 0; // inicializa o vetor de visitados com 0
	// cria uma pilha
    Pilha pilha = criaPilha();
    push(&pilha, origem); // insere o vertice de origem na pilha

    int hold[4] = {-1, -1, -1, -1};
    int caminho[grafo->numVertices*grafo->numVertices];
    for (int i = 0; i < grafo->numVertices*grafo->numVertices; i++) caminho[i] = -1;


    int v;
    while (!pilhaVazia(pilha)) {
        v = top(pilha); // retira o vertice do topo da pilha
        pop(&pilha); // remove o vertice do topo da pilha
        if (visitados[v] == 0) {
            visitados[v] = 1; // marca o vertice como visitado
            int k = 0; // contador de adjacencias
            for (int i = 0; i < 4; i++) hold[i] = -1; // limpa o vetor hold

            // percorre a matriz de adjacencia do vertice
            for (int i = 0; i < grafo->numVertices; i++) {
                if (grafo->adj[v][i] != 0) { // se o vertice for adjacente do vertice do topo da pilha
                    for (int j = 0; j < 4; j++) {
                        if (hold[j] == -1) {
                            hold[j] = i;    
                            k++;
                            break;
                        }
                    }
                }
            }

            // adiciona os elementos do vetor hold na pilha de forma aleatoria
            for (int i = 0; i < k; i++) {
                int random = rand() % k;
                while (hold[random] == -1) random = rand() % k;
                if (visitados[hold[random]] == 0) push(&pilha, hold[random]);
                hold[random] = -1;
            }

            // imprimePilha(pilha);

            // verifica se o vertice do topo da pilha é adjacente ao vertice v
            // se for imprime

            // calcula a direção entre hold[random] e v
            int direcao = -1;
            int topo;
            while (direcao == -1) {
                topo = top(pilha);
                if (topo == v - 1) direcao = 0; // esquerda
                else if (topo == v + 1) direcao = 1; // direita
                else if (topo == v - grafo->colunas) direcao = 2; // cima
                else if (topo == v + grafo->colunas) direcao = 3; // baixo



                if (direcao != -1) { // adiciona topo da pilha no caminho
                    for (int i = 0; i < grafo->numVertices*grafo->numVertices; i++) { // adiciona o vertice do topo da pilha no caminho
                        if (caminho[i] == -1) { // se o caminho estiver vazio
                            caminho[i] = topo;
                            break;
                        }
                    } // caminho.append(topo)

                    // print caminho
                    for (int i = 0; i < grafo->numVertices*grafo->numVertices; i++) if (caminho[i] != -1) printf("%d ", caminho[i]);
                    printf("\n"); 
                } else { // adiciona o ultimo vertice do caminho á pilha
                    for (int i = 0; i < grafo->numVertices*grafo->numVertices; i++) { // adiciona o vertice do topo da pilha no caminho
                        if (caminho[i] == -1) { // se o caminho estiver vazio
                            push(&pilha, caminho[i-2]);
                            caminho[i-1] = -1;
                            break;
                        }
                    }
                }
            }

            if (direcao == 0) printf("quadrado:%d -> esquerda -> %d\n", v, topo);
            if (direcao == 1) printf("quadrado:%d -> direita -> %d\n", v, topo);
            if (direcao == 2) printf("quadrado:%d -> cima -> %d\n", v, topo);
            if (direcao == 3) printf("quadrado:%d -> baixo -> %d\n", v, topo);
            if (direcao == -1) printf("quadrado:%d -> %d\n", v, topo);
            // imprimePilha(pilha);

            /* Apaga Caminho */
            int linha = (v/grafo->colunas)*2;
            int coluna = (v%grafo->colunas)*4;

            if (direcao == 0) { // esquerda
                if (v % grafo->colunas != 0 && !visitados[v - 1]) { // se não for a primeira coluna e o vertice adjacente a esquerda já foi visitado
                    for (int i = 0; i < 3; i++) labirinto[linha + 1][coluna + i] = ' ';
                }
            } else if (direcao == 1) { // direita
                if (v % grafo->colunas != grafo->colunas - 1 && !visitados[v + 1]) { // se não for a ultima coluna e o vertice adjacente a direita já foi visitado
                    for (int i = 2; i < 5; i++) labirinto[linha + 1][coluna + i] = ' ';
                }
            } else if (direcao == 2) { // cima
                if (v >= grafo->colunas && !visitados[v - grafo->colunas]) { // se não for a primeira linha e o vertice adjacente a cima já foi visitado
                    for (int i = 1; i < 4; i++) labirinto[linha][coluna + i] = ' ';
                }
            } else if (direcao == 3) { // baixo
                if (v < grafo->numVertices - grafo->colunas && !visitados[v + grafo->colunas]) { // se não for a ultima linha e o vertice adjacente a baixo já foi visitado
                    for (int i = 1; i < 4; i++) labirinto[linha + 2][coluna + i] = ' ';
                }
            }
        }
    }
}