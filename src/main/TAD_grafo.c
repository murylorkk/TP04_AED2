#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "TAD_grafo.h" 

// ============================================================================
// ESTRUTURAS OCULTAS (Encapsulamento real)
// Nenhuma função fora deste ficheiro sabe o que o Grafo tem por dentro.
// ============================================================================

typedef struct No {
    int vertice;
    struct No* prox;
} No;

struct Grafo {
    int V; 
    int E_totais; 
    No** adj; 
};

// ============================================================================
// FUNÇÕES GETTER
// ============================================================================

int obter_num_vertices(Grafo* g) {
    return g->V;
}

int obter_num_arestas(Grafo* g) {
    return g->E_totais;
}

// ============================================================================
// IMPLEMENTAÇÃO DAS OPERAÇÕES
// ============================================================================

// cria um grafo com V vértices
Grafo* criar_grafo(int V) {
    Grafo* g = (Grafo*)malloc(sizeof(Grafo));
    if (g == NULL) {
        printf("Erro de alocacao de memoria para o grafo.\n");
        exit(1);
    }
    
    g->V = V;
    g->E_totais = 0;
    g->adj = (No**)malloc(V * sizeof(No*));
    
    for (int i = 0; i < V; i++) {
        g->adj[i] = NULL;
    }
    return g;
}

bool existe_aresta(Grafo* g, int u, int v) {
    No* atual = g->adj[u];
    while (atual != NULL) {
        if (atual->vertice == v) return true;
        atual = atual->prox;
    }
    return false;
}

// Adiciona aresta não direcionada entre u e v
void adicionar_aresta(Grafo* g, int u, int v) {
    if (u == v || existe_aresta(g, u, v)) return;

    // Adiciona v na lista de u
    No* novo_no = (No*)malloc(sizeof(No));
    novo_no->vertice = v;
    novo_no->prox = g->adj[u];
    g->adj[u] = novo_no;

    // Adiciona u na lista de v (grafo não direcionado)
    novo_no = (No*)malloc(sizeof(No));
    novo_no->vertice = u;
    novo_no->prox = g->adj[v];
    g->adj[v] = novo_no;

    g->E_totais++;
}

// cria grafos conexos com diferentes quantidades de vértices e graus de conectividade
Grafo* gerar_grafo_conexo(int V, float grau_conectividade) {
    Grafo* g = criar_grafo(V);
    
    // garantindo que o grafo não seja desconexo criando um caminho base 
    for (int i = 0; i < V - 1; i++) {
        adicionar_aresta(g, i, i + 1);
    }

    // adicionando arestas até atingir o grau de conectividade desejado
    int max_arestas = (V * (V - 1)) / 2;
    int arestas_alvo = (int)(max_arestas * grau_conectividade);

    while (g->E_totais < arestas_alvo) {
        int u = rand() % V;
        int v = rand() % V;
        adicionar_aresta(g, u, v);
    }

    return g;
}

// busca em Largura que mostra a árvore resultante do caminhamento 
void bfs_arvore(Grafo* g, int inicio, bool imprimir) {
    bool* visitados = (bool*)calloc(g->V, sizeof(bool));
    int* pai = (int*)malloc(g->V * sizeof(int));
    int* fila = (int*)malloc(g->V * sizeof(int));
    
    for(int i = 0; i < g->V; i++) pai[i] = -1;

    int inicio_fila = 0, fim_fila = 0;
    int contador_print = 0;

    visitados[inicio] = true;
    fila[fim_fila++] = inicio;

    if (imprimir) {
        printf("Arvore BFS gerada a partir do vertice %d:\n", inicio);
    }

    while (inicio_fila < fim_fila) {
        int u = fila[inicio_fila++];

        No* adjacente = g->adj[u];
        while (adjacente != NULL) {
            int v = adjacente->vertice;
            if (!visitados[v]) {
                visitados[v] = true;
                pai[v] = u;
                fila[fim_fila++] = v;
                
                // Só imprime na tela se a "chave" estiver ligada
                if (imprimir) {
                    printf("(%d -> %d) ", u, v);
                    contador_print++;
                    if (contador_print % 10 == 0) printf("\n"); 
                }
            }
            adjacente = adjacente->prox;
        }
    }
    
    if (imprimir) printf("\n");

    free(visitados);
    free(pai);
    free(fila);
}

// marca tempo de execução de cada busca e a média das buscas
void testar_tempos_bfs(Grafo* g, int qtd_buscas) {
    double tempo_total = 0.0;

    printf("\n--- Testando %d Buscas em Largura ---\n", qtd_buscas);
    
    for (int i = 0; i < qtd_buscas; i++) {
        int origem = rand() % g->V;
        
        clock_t start = clock();
        bfs_arvore(g, origem, false);
        clock_t end = clock();
        
        double tempo_gasto = (double)(end - start) / CLOCKS_PER_SEC;
        tempo_total += tempo_gasto;
        
        printf("Busca %d (Origem %d): %f segundos\n", i + 1, origem, tempo_gasto);
    }
    
    printf("\n=> Tempo medio das buscas em largura: %f segundos\n", tempo_total / qtd_buscas);
}

void imprimir_grafo(Grafo* g) {
    printf("Estrutura do Grafo (%d vertices, %d arestas):\n", g->V, g->E_totais);
    for (int i = 0; i < g->V; i++) {
        printf("Vertice %d:", i);
        No* atual = g->adj[i];
        while (atual != NULL) {
            printf(" -> %d", atual->vertice);
            atual = atual->prox;
        }
        printf("\n");
    }
}

void liberar_grafo(Grafo* g) {
    for (int i = 0; i < g->V; i++) {
        No* atual = g->adj[i];
        while (atual != NULL) {
            No* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(g->adj);
    free(g);
}

void imprimir_caminho(int *caminho, int tamanho, int *contador) {
    (*contador)++;
    printf("Caminho %d: ", *contador);
    for (int i = 0; i < tamanho; i++) {
        printf("%d", caminho[i]);
        if (i < tamanho - 1) printf(" -> ");
    }
    printf("\n");
}

// função recursiva com Backtracking
void dfs_todos_caminhos(Grafo *g, int atual, int *visitado, int *caminho, int tamanhoCaminho, int *contador) {
    visitado[atual] = 1;
    caminho[tamanhoCaminho] = atual;
    tamanhoCaminho++;

    // se o caminho atingiu o total de vértices, imprime
    if (tamanhoCaminho == g->V) {
        imprimir_caminho(caminho, tamanhoCaminho, contador);
    } else {
        // Tenta continuar por cada vizinho não visitado
        No *vizinho = g->adj[atual];
        while (vizinho != NULL) {
            if (!visitado[vizinho->vertice]) {
                dfs_todos_caminhos(g, vizinho->vertice, visitado, caminho, tamanhoCaminho, contador);
            }
            vizinho = vizinho->prox;
        }
    }
    // Backtracking: desmarca para permitir que o vértice participe de outras rotas
    visitado[atual] = 0;
}

void todos_os_caminhos(Grafo *g, int origem) {
    int *visitado = (int*) calloc(g->V, sizeof(int));
    int *caminho = (int*) malloc(g->V * sizeof(int));
    int contador = 0;

    dfs_todos_caminhos(g, origem, visitado, caminho, 0, &contador);

    if (contador == 0) {
        printf("Nenhum caminho encontrado que visite todos os vertices a partir do vertice %d.\n", origem);
    } else {
        printf("Total de caminhos completos encontrados: %d\n", contador);
    }

    free(visitado);
    free(caminho);
}

void dfs_recursiva(Grafo* g, int u, bool* visitados, bool imprimir) {
    visitados[u] = true;
    if (imprimir) {
        printf("%d ", u);
    }
    
    No* adjacente = g->adj[u];
    while (adjacente != NULL) {
        int v = adjacente->vertice;
        if (!visitados[v]) {
            dfs_recursiva(g, v, visitados, imprimir);
        }
        adjacente = adjacente->prox;
    }
}

void dfs_profundidade(Grafo* g, int inicio, bool imprimir) {
    bool* visitados = (bool*)calloc(g->V, sizeof(bool));
    dfs_recursiva(g, inicio, visitados, imprimir);
    if (imprimir) {
        printf("\n");
    }
    free(visitados);
}

void testar_tempos_dfs(Grafo* g, int qtd_buscas) {
    double tempo_total = 0.0;
    printf("\n--- Testando %d Buscas em Profundidade ---\n", qtd_buscas);
    for (int i = 0; i < qtd_buscas; i++) {
        int origem = rand() % g->V;
        
        clock_t start = clock();
        dfs_profundidade(g, origem, false); 
        clock_t end = clock();
        
        double tempo_gasto = (double)(end - start) / CLOCKS_PER_SEC;
        tempo_total += tempo_gasto;
        
        printf("Busca %d (Origem %d): %f segundos\n", i + 1, origem, tempo_gasto);
    }
    printf("\n=> Tempo medio das buscas em profundidade: %f segundos\n", tempo_total / qtd_buscas);
}

bool dfs_detecta_ciclo(Grafo *g, int atual, int pai, bool *visitado) {
    visitado[atual] = true;

    No *vizinho = g->adj[atual];
    while (vizinho != NULL) {
        int v = vizinho->vertice;

        if (!visitado[v]) {
            if (dfs_detecta_ciclo(g, v, atual, visitado)) {
                return true;
            }
        }
        else if (v != pai) {
            return true;
        }

        vizinho = vizinho->prox;
    }

    return false;
}

bool grafo_tem_ciclo(Grafo *g) {
    bool *visitado = (bool*) calloc(g->V, sizeof(bool));

    for (int i = 0; i < g->V; i++) {
        if (!visitado[i]) {
            if (dfs_detecta_ciclo(g, i, -1, visitado)) {
                free(visitado);
                return true;
            }
        }
    }

    free(visitado);
    return false;
}