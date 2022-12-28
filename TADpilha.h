/* ********************************************/
/*   Tad pilha                                  */
/* **********************************************/
#if!defined PILHA
#define PILHA


//Estrutura de uma pilha 
typedef struct no {//no de uma pilha 
	int elem;//o elemento
	struct no* prox;//ponteiro para o proximo elemento
} No;
typedef No * Pilha; // conjunto de nos 

/**
 * @brief Cria uma pilha
 * @return Pilha 
 */
Pilha criaPilha();

/**
 * @brief Insere um elemento no topo da pilha
 * @param Pilha* pilha
 * @param int elemento
 */
void push(Pilha*, int);

/**
 * @brief Devolve o elemento do topo da pilha
 * @param Pilha pilha
 * @return int 
 */
int top(Pilha);

/**
 * @brief Retira o elemento do topo da pilha
 * @param Pilha* pilha
 */
void pop(Pilha*);

/**
 * @brief Verifica se a pilha está vazia
 * @param Pilha pilha
 * @return int 
 */
int pilhaVazia(Pilha);

#endif