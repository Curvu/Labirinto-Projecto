#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"
#include "pilha.h"
#include <time.h>

void imprimeLabirinto(char** labirinto, struct Grafo* grafo) {
    // imprime o labirinto
    for (int i = 0; i < grafo->linhas*2 + 1; i++) {
        for (int j = 0; j < grafo->colunas * 4 + 1; j++) {
            printf("%c", labirinto[i][j]);
        }
        printf("\n");
    }
}

static int visited[1000];

void reachR(Grafo grafo, int v, char** labirinto) {
    visited[v] = 1;

    // randomiza escolhe uma direção randomica para o vertice
    int direcao = rand() % 4;
    int direcoes[4] = {0, 1, 2, 3};
    for (int i = 0; i < 4; i++) {
        int aux = direcoes[i];
        int j = rand() % 4;
        direcoes[i] = direcoes[j];
        direcoes[j] = aux;
    }

    for (int i = 0; i < 4; i++) {
        int direcao = direcoes[i];
        if (direcao == 0) { // esquerda
            if (v % grafo->colunas != 0 && !visited[v - 1]) {
                labirinto[(v/grafo->colunas)*2 + 1][(v%grafo->colunas)*4] = ' ';
                labirinto[(v/grafo->colunas)*2 + 1][(v%grafo->colunas)*4 + 1] = ' ';
                labirinto[(v/grafo->colunas)*2 + 1][(v%grafo->colunas)*4 + 2] = ' ';
                reachR(grafo, v - 1, labirinto);
            }
        }
        if (direcao == 1) { // direita
            if (v % grafo->colunas != grafo->colunas - 1 && !visited[v + 1]) {
                labirinto[(v/grafo->colunas)*2 + 1][(v%grafo->colunas)*4 + 2] = ' ';
                labirinto[(v/grafo->colunas)*2 + 1][(v%grafo->colunas)*4 + 3] = ' ';
                labirinto[(v/grafo->colunas)*2 + 1][(v%grafo->colunas)*4 + 4] = ' ';
                reachR(grafo, v + 1, labirinto);
            }
        }
        if (direcao == 2) { // cima
            if (v >= grafo->colunas && !visited[v - grafo->colunas]) {
                labirinto[(v/grafo->colunas)*2][(v%grafo->colunas)*4 + 1] = ' ';
                labirinto[(v/grafo->colunas)*2][(v%grafo->colunas)*4 + 2] = ' ';
                labirinto[(v/grafo->colunas)*2][(v%grafo->colunas)*4 + 3] = ' ';
                reachR(grafo, v - grafo->colunas, labirinto);
            }
        }
        if (direcao == 3) { // baixo
            if (v < grafo->numVertices - grafo->colunas && !visited[v + grafo->colunas]) {
                labirinto[(v/grafo->colunas)*2 + 2][(v%grafo->colunas)*4 + 1] = ' ';
                labirinto[(v/grafo->colunas)*2 + 2][(v%grafo->colunas)*4 + 2] = ' ';
                labirinto[(v/grafo->colunas)*2 + 2][(v%grafo->colunas)*4 + 3] = ' ';
                reachR(grafo, v + grafo->colunas, labirinto);
            }
        }
    }
}

            // if (v + 1 == i) { // se o vertice adjacente for o da direita
            //     labirinto[(v/grafo->colunas)*2 + 1][(v%grafo->colunas)*4 + 2] = ' ';
            //     labirinto[(v/grafo->colunas)*2 + 1][(v%grafo->colunas)*4 + 3] = ' ';
            //     labirinto[(v/grafo->colunas)*2 + 1][(v%grafo->colunas)*4 + 4] = ' ';
            // }
            // if (v - 1 == i) { // se o vertice adjacente for o da esquerda
            //     labirinto[(v/grafo->colunas)*2 + 1][(v%grafo->colunas)*4] = ' ';
            //     labirinto[(v/grafo->colunas)*2 + 1][(v%grafo->colunas)*4 + 1] = ' ';
            //     labirinto[(v/grafo->colunas)*2 + 1][(v%grafo->colunas)*4 + 2] = ' ';
            // }
            // if (v + grafo->colunas == i) { // se o vertice adjacente for o de baixo
            //     labirinto[(v/grafo->colunas)*2 + 2][(v%grafo->colunas)*4 + 1] = ' ';
            //     labirinto[(v/grafo->colunas)*2 + 2][(v%grafo->colunas)*4 + 2] = ' ';
            //     labirinto[(v/grafo->colunas)*2 + 2][(v%grafo->colunas)*4 + 3] = ' ';
            // }
            // if (v - grafo->colunas == i) { // se o vertice adjacente for o de cima
            //     labirinto[(v/grafo->colunas)*2][(v%grafo->colunas)*4 + 1] = ' ';
            //     labirinto[(v/grafo->colunas)*2][(v%grafo->colunas)*4 + 2] = ' ';
            //     labirinto[(v/grafo->colunas)*2][(v%grafo->colunas)*4 + 3] = ' ';
            // }
    //         reachR(grafo, i, labirinto);
    // random direction
    
// }

int GRAPHreach(Grafo grafo, int inicio, int fim, char** labirinto) {
    for (int i = 0; i < grafo->numVertices; i++) visited[i] = 0;
    reachR(grafo, inicio, labirinto);
    if (visited[fim] == 0) return 0;
    else return 1;
}

void dfs(Grafo grafo, int origem, char **labirinto) {
    int visitados[grafo->numVertices]; // vetor de visitados
    for (int i = 0; i < grafo->numVertices; i++) visitados[i] = 0; // inicializa o vetor de visitados com 0
	// cria uma pilha
    Pilha pilha = criaPilha();
    push(&pilha, origem); // insere o vertice de origem na pilha

    int hold[4] = {-1, -1, -1, -1};

    while (!pilhaVazia(pilha)) {
        int vertice = top(pilha); // pega o vertice do topo da pilha
        pop(&pilha); // remove o vertice do topo da pilha

        if (!visitados[vertice]) { // se o vertice não foi visitado
            visitados[vertice] = 1; // marca o vertice como visitado
            
            // remove as paredes
            if (vertice - 1 >= 0 && vertice % grafo->colunas != 0 && !visitados[vertice - 1]) { // se o vertice adjacente for o da esquerda
                labirinto[(vertice/grafo->colunas)*2 + 1][(vertice%grafo->colunas)*4] = ' ';
                labirinto[(vertice/grafo->colunas)*2 + 1][(vertice%grafo->colunas)*4 + 1] = ' ';
                labirinto[(vertice/grafo->colunas)*2 + 1][(vertice%grafo->colunas)*4 + 2] = ' ';
            }
            if (vertice + 1 < grafo->numVertices && (vertice + 1) % grafo->colunas != 0 && !visitados[vertice + 1]) { // se o vertice adjacente for o da direita
                labirinto[(vertice/grafo->colunas)*2 + 1][(vertice%grafo->colunas)*4 + 2] = ' ';
                labirinto[(vertice/grafo->colunas)*2 + 1][(vertice%grafo->colunas)*4 + 3] = ' ';
                labirinto[(vertice/grafo->colunas)*2 + 1][(vertice%grafo->colunas)*4 + 4] = ' ';
            }
            if (vertice + grafo->colunas < grafo->numVertices && !visitados[vertice + grafo->colunas]) { // se o vertice adjacente for o de baixo
                labirinto[(vertice/grafo->colunas)*2 + 2][(vertice%grafo->colunas)*4 + 1] = ' ';
                labirinto[(vertice/grafo->colunas)*2 + 2][(vertice%grafo->colunas)*4 + 2] = ' ';
                labirinto[(vertice/grafo->colunas)*2 + 2][(vertice%grafo->colunas)*4 + 3] = ' ';
            }
            if (vertice - grafo->colunas >= 0 && !visitados[vertice - grafo->colunas]) { // se o vertice adjacente for o de cima
                labirinto[(vertice/grafo->colunas)*2][(vertice%grafo->colunas)*4 + 1] = ' ';
                labirinto[(vertice/grafo->colunas)*2][(vertice%grafo->colunas)*4 + 2] = ' ';
                labirinto[(vertice/grafo->colunas)*2][(vertice%grafo->colunas)*4 + 3] = ' ';
            }
            

            // percorre a lista de adjacencia do vertice
            for (int i = 0; i < grafo->numVertices; i++) {
                if (grafo->adj[vertice][i] != 0) { // se o vertice for adjacente do vertice do topo da pilha
                    for (int j = 0; j < 4; j++) {
                        if (hold[j] == -1) {
                            hold[j] = i;
                            break;
                        }
                    }
                }
            }

            int direcao = rand() % 4; // gera um numero aleatorio entre 0 e 3
            while (hold[direcao] == -1) direcao = rand() % 4; // enquanto o vertice adjacente for -1
            
            for (int i = 0; i < 4; i++) {
                if (hold[i] != -1) push(&pilha, hold[i]); // insere os vertices adjacentes na pilha
                hold[i] = -1; // limpa holder
            }
        }

    }
}

// gerar o desenho do labirinto
void geraLabirinto(struct Grafo* grafo, int inicio, int fim) {
    if ((inicio >= grafo->colunas || inicio < 0 ) || fim >= grafo->colunas) {
        printf("Vértice final ou inicial inválido\n");
        exit(1);
    }

    // cria um array de string que vai guardar cada linha do labirinto
    char* labirinto[grafo->linhas*2 + 1]; // é preciso 2 linhas para cada linha do labirinto e +1 no final para o simbolo +
    for (int i = 0; i < grafo->linhas*2 + 1; i++) {
        labirinto[i] = malloc(grafo->colunas * 4 + 1); // Pura matemática (é preciso 4 espaços para cada coluna e +1 no final para o simbolo +)
        memset(labirinto[i], ' ', grafo->colunas * 4 + 1); // preenche o array com espaços, memset é mais rápido do que `for loop`
        labirinto[i][grafo->colunas * 2] = '\0';
    }

    // preenche o labirinto com as paredes
    for (int i = 0; i < grafo->linhas*2 + 1; i++) {
        for (int j = 0; j < grafo->colunas * 4 + 1; j++) {
            if (i % 2 == 0) { // linha par +---+
                if (j % 4 == 0) labirinto[i][j] = '+'; // de 4 em 4 colunas é um +
                else labirinto[i][j] = '-'; // senão é um -
            } else { // linha impar |   |
                if (j % 4 == 0) labirinto[i][j] = '|';
                else labirinto[i][j] = ' ';
            }
        }
    }

    // remove as paredes do inicio e do fim a partir do id
    for (int i = 1; i < 4; i++) {
        labirinto[0][inicio * 4 + i] = ' ';
        labirinto[grafo->linhas*2][fim * 4 + i] = ' ';
    } // Mathematic is fun 😒

    //TODO: gerar o caminho
    // geraCaminho(grafo);
    dfs(grafo, inicio, labirinto);
    // GRAPHreach(grafo, inicio, fim, labirinto);

    imprimeLabirinto(labirinto, grafo);
}



int main() {
    srand(time(NULL));

    int inicio = 2, fim = 1;
    struct Grafo* grafo = criaGrafo(6, 6);

    // printGraph(grafo);

    printf("\n\n");

    geraLabirinto(grafo, inicio, fim);
    return 0;
}