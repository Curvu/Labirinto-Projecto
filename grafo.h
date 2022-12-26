/**********************************************/
/*      Tad grafo matriz de adjacencias       */
/**********************************************/
#if!defined GRAFO
#define GRAFO

struct Grafo {
    int linhas; // numero de linhas
    int colunas; // numero de colunas

    int numVertices; // numero de vertices
    int numArcos; // numero de arcos

    int** adj; // matriz de adjacencias
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
 * @brief Cria uma matriz de adjacencias
 * @param int numero de linhas
 * @param int numero de colunas
 * @return int** 
 */
int **criaMatriz(int, int);

/**
 * @brief Insere um arco no inicio da lista de adjacencia
 * @param struct Grafo* grafo
 * @param int coordenada x
 * @param int coordenada y
 */
void insereArco(Grafo, int, int);

/**
 * @brief Retira um arco da lista de adjacencia
 * @param struct Grafo* grafo
 * @param int coordenada x
 * @param int coordenada y
 */
void retiraArco(Grafo, int, int);

/**
 * @brief Verifica se o grafo está vazio
 * @return 1 se o grafo estiver vazio e 0 se não estiver
 */
int vazio(Grafo);

/**
 * @brief Insere um ao contador de arcos
 * @param Grafo grafo
 */
void insereNo(Grafo);

/**
 * @brief Retira um ao contador de arcos
 * @param Grafo grafo
 */
void retiraNo(Grafo);

/**
 * @brief Percorre o grafo em profundidade
 * @param Grafo grafo
 * @param int vertice de origem
 */
void percuroemprofundidade(Grafo g, int origem);

#endif