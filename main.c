#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

void geraCaminho(struct Grafo* grafo) {


    // gera o caminho
    // for (int i = 0; i < grafo->linhas; i++) {
    //     for (int j = 0; j < grafo->colunas; j++) {
    //         if (j < grafo->colunas - 1) insereArco(grafo, i * grafo->colunas + j, i * grafo->colunas + j + 1); // insere o arco para a direita
    //         if (i < grafo->linhas - 1) insereArco(grafo, i * grafo->colunas + j, (i + 1) * grafo->colunas + j); // insere o arco para baixo
    //     }
    // }

    // printa a matriz adjacente
    // for (int i = 0; i < grafo->linhas; i++) {
    //     for (int j = 0; j < grafo->colunas; j++) {
    //         printf("%d ", grafo->adj[i][j].id);
    //     }
    //     printf("\n");
    // }
}

void imprimeLabirinto(char** labirinto, struct Grafo* grafo) {
    // imprime o labirinto
    for (int i = 0; i < grafo->linhas*2 + 1; i++) {
        for (int j = 0; j < grafo->colunas * 4 + 1; j++) {
            printf("%c", labirinto[i][j]);
        }
        printf("\n");
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
    geraCaminho(grafo);

    imprimeLabirinto(labirinto, grafo);
}

int main() {
    int incio = 2, fim = 1;
    struct Grafo* grafo = criaGrafo(4, 4);

    // printGraph(grafo);

    printf("\n\n");

    geraLabirinto(grafo, incio, fim);
    return 0;
}