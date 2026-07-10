#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tad_grafo.h"

int main() {
    srand(time(NULL));
    int opcao = -1;

    do {
        printf("\n==================================================\n");
        printf(" TRABALHO PRATICO 4 - AED 2 (Busca em Grafos)\n");
        printf("==================================================\n");
        printf("1 - Questao 1: Gerar Grafo e Mostrar Estrutura\n");
        printf("2 - Questao 2: Busca em Largura (Mostrar Arvore Resultante)\n");
        printf("4 - Questao 4: Todos os caminhos usando busca em profundidade\n");        
        printf("0 - Sair\n");
        printf("==================================================\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n');
            opcao = -1; 
        }

        switch (opcao) {
            case 1: {
                printf("\n--- EXECUTANDO QUESTAO 1 ---\n");
                printf("Demonstrando a criacao com multiplos tamanhos e graus:\n\n");

                // Diferentes quantidades de vértices exigidas pela questão
                int tamanhos_q1[] = {5, 10, 50, 100}; 
                float graus_q1[] = {0.25, 0.50, 0.75, 1.00}; 
                
                for (int t = 0; t < 4; t++) {
                    for (int g = 0; g < 4; g++) {
                        Grafo* grafo_q1 = gerar_grafo_conexo(tamanhos_q1[t], graus_q1[g]);
                        
                        printf("Grafo gerado -> Vertices: %3d | Conectividade: %3.0f%% | Arestas: %d\n", 
                               grafo_q1->V, graus_q1[g] * 100, grafo_q1->E_totais);
                        
                        // Imprime a lista de adjacência apenas de um grafo bem pequeno para prova visual
                        if (tamanhos_q1[t] == 5 && graus_q1[g] == 0.50) {
                            printf("\n  [Demonstracao Visual da Estrutura (V=5, 50%%)]\n");
                            imprimir_grafo(grafo_q1); 
                            printf("\n");
                        }
                        
                        liberar_grafo(grafo_q1);
                    }
                    printf("--------------------------------------------------\n");
                }
                break;
            }
            case 2: {
                printf("\n--- EXECUTANDO QUESTAO 2: BUSCA EM LARGURA ---\n");
                
                // EXIGÊNCIA A: Mostrar a árvore resultante do caminhamento
                printf("\nParte A: Arvore Resultante (Grafo de 10 vertices, 50%% conectividade)\n");
                Grafo* g_visual = gerar_grafo_conexo(10, 0.50);
                
                // O 'true' liga a impressão da árvore na tela
                bfs_arvore(g_visual, 0, true); 
                liberar_grafo(g_visual);

                // EXIGÊNCIA B: Marcar tempo de execução e a média das buscas
                printf("\nParte B: Analise de Tempo (Grafo de 250 vertices)\n");
                int V_grande = 250;
                float graus_q2[] = {0.25, 0.50, 0.75, 1.00};
                
                for (int i = 0; i < 4; i++) {
                    printf("\n> Testando Conectividade %.0f%%:\n", graus_q2[i] * 100);
                    Grafo* g_tempo = gerar_grafo_conexo(V_grande, graus_q2[i]);
                    
                    // A função testar_tempos_bfs roda o loop 10 vezes, imprime os tempos individuais e a média.
                    // ATENÇÃO: Dentro dela, a chamada deve ser bfs_arvore(g_tempo, origem, false);
                    testar_tempos_bfs(g_tempo, 10); 
                    
                    liberar_grafo(g_tempo);
                }
                break;
            }
            case 4: {
                printf("\n--- EXECUTANDO QUESTAO 4: TODOS OS CAMINHOS ---\n");
                
                printf("\n> Exemplo 1: Grafo em linha (0-1-2-3)\n");
                Grafo *g_linha = criar_grafo(4);
                adicionar_aresta(g_linha, 0, 1);
                adicionar_aresta(g_linha, 1, 2);
                adicionar_aresta(g_linha, 2, 3);
                todos_os_caminhos(g_linha, 0);
                liberar_grafo(g_linha);

                printf("\n> Exemplo 2: Grafo completo K4 (Todos conectados a todos)\n");
                Grafo *g_completo = criar_grafo(4);
                adicionar_aresta(g_completo, 0, 1);
                adicionar_aresta(g_completo, 0, 2);
                adicionar_aresta(g_completo, 0, 3);
                adicionar_aresta(g_completo, 1, 2);
                adicionar_aresta(g_completo, 1, 3);
                adicionar_aresta(g_completo, 2, 3);
                todos_os_caminhos(g_completo, 0);
                liberar_grafo(g_completo);

                printf("\n> Exemplo 3: Grafo com 5 vertices (Gerado automaticamente)\n");
                Grafo *g_auto = gerar_grafo_conexo(5, 0.50);
                imprimir_grafo(g_auto); // Mostra a estrutura para conferência
                todos_os_caminhos(g_auto, 0);
                liberar_grafo(g_auto);
                
                break;
            }
            case 0:
                printf("\nEncerrando...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}
