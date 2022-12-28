#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADgrafo.h"
#include "TADpilha.h"
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

// gerar o desenho do labirinto
void geraLabirinto(struct Grafo* grafo, int inicio, int fim) {
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
    } //! Mathematic is fun 😒

    dfs(grafo, inicio, labirinto); // chama a função dfs para remover as paredes do labirinto

    imprimeLabirinto(labirinto, grafo);
}



int main() {
    srand(time(NULL));

    int inicio, fim, linhas, colunas;

    printf("Digite o número de linhas: ");
    scanf("%d", &linhas);
    printf("Digite o número de colunas: ");
    scanf("%d", &colunas);
    printf("Digite o vértice inicial: ");
    scanf("%d", &inicio);
    printf("Digite o vértice final: ");
    scanf("%d", &fim);

    if (linhas < 1 || colunas < 1) {
        printf("Número de linhas ou colunas inválido\n");
        exit(1);
    }
    if (inicio < 0 || inicio >= colunas || fim < 0 || fim >= colunas) {
        printf("Vértice inicial ou final inválido\n");
        exit(1);
    }

    printf("\n");

    struct Grafo* grafo = criaGrafo(linhas, colunas);

    geraLabirinto(grafo, inicio, fim);
    return 0;
}