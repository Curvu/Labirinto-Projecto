/**********************************************/
/*      Tad grafo matriz de adjacencias       */
/**********************************************/
#if!defined GRAFO
#define GRAFO

typedef struct no *No;
struct no {
    int atual; // vertice atual
    No prox; // proximo no
};

struct Grafo {
    int linhas; // numero de linhas
    int colunas; // numero de colunas

    int numVertices; // numero de vertices
    int numArcos; // numero de arcos

    No* adj; // lista de adjacencia
};
typedef struct Grafo* Grafo;


/**
 * @brief Cria um grafo
 * @param int numero de linhas
 * @param int numero de colunas
 * @return struct Grafo* 
 */
Grafo criaGrafo(int, int);

/**
 * @brief Insere um arco no inicio da lista de adjacencia
 * @param struct Grafo* grafo
 * @param int origem
 * @param int destino
 */
void insereArco(Grafo, int, int);

/**
 * @brief Retira um arco da lista de adjacencia
 * @param struct Grafo* grafo
 * @param int origem
 * @param int vertice a ser retirado
 */
void retiraArco(Grafo, int, int);

/**
 * @brief Verifica se o grafo está vazio
 * @return 1 se o grafo estiver vazio e 0 se não estiver
 */
int vazio(Grafo);

/**
 * @brief Insere um no no inicio da lista de adjacencia
 * @param int vertice
 * @param No lista
 * @return No*
 */
No insereNo(int, No);

/**
 * @brief Retira um no da lista de adjacencia
 * @param No* lista
 * @param int vertice
 * @return No*
 */


#endif