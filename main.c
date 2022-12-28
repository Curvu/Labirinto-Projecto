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
    for (int i = 0; i < 4; i++) { // embaralha o vetor de direcoes
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

int GRAPHreach(Grafo grafo, int inicio, int fim, char** labirinto) {
    for (int i = 0; i < grafo->numVertices; i++) visited[i] = 0;
    reachR(grafo, inicio, labirinto);
    if (visited[fim] == 0) return 0;
    else return 1;
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