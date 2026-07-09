#ifndef TAD_GRAFO_H
#define TAD_GRAFO_H
#include <stdbool.h>

typedef struct No {
    int vertice;
    struct No* prox;
} No;

typedef struct Grafo {
    int V; 
    int E_totais; 
    No** adj; 
} Grafo;

Grafo* criar_grafo(int V);

bool existe_aresta(Grafo* g, int u, int v);

void adicionar_aresta(Grafo* g, int u, int v);

Grafo* gerar_grafo_conexo(int V, float grau_conectividade);

void bfs_arvore(Grafo* g, int inicio, bool imprimir);

void testar_tempos_bfs(Grafo* g, int qtd_buscas);

void imprimir_grafo(Grafo* g);

void liberar_grafo(Grafo* g);

void todos_os_caminhos(Grafo* g, int origem);

void dfs_todos_caminhos(Grafo *g, int atual, int *visitado, int *caminho, int tamanhoCaminho, int *contador);

#endif // TAD_GRAFO_H