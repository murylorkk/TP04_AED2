#ifndef TAD_GRAFO_H
#define TAD_GRAFO_H
#include <stdbool.h>

// TAD Opaco: A estrutura está escondida. A main apenas conhece o "nome" Grafo.
typedef struct Grafo Grafo;

// --- Funções Getter (Novas) ---
int obter_num_vertices(Grafo* g);
int obter_num_arestas(Grafo* g);

// --- Operações do TAD ---
Grafo* criar_grafo(int V);

bool existe_aresta(Grafo* g, int u, int v);

void adicionar_aresta(Grafo* g, int u, int v);

Grafo* gerar_grafo_conexo(int V, float grau_conectividade);

void bfs_arvore(Grafo* g, int inicio, bool imprimir);

void testar_tempos_bfs(Grafo* g, int qtd_buscas);

void imprimir_grafo(Grafo* g);

void liberar_grafo(Grafo* g);

void todos_os_caminhos(Grafo* g, int origem);

void dfs_profundidade(Grafo* g, int inicio, bool imprimir);

void testar_tempos_dfs(Grafo* g, int qtd_buscas);

bool grafo_tem_ciclo(Grafo *g);

#endif // TAD_GRAFO_H