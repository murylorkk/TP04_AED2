#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "TAD_grafo.h"

int main() {
    srand(time(NULL));
    int opcao = -1;

    do {
        printf("\n==================================================\n");
        printf(" TRABALHO PRATICO 4 - AED 2 (Busca em Grafos)\n");
        printf("==================================================\n");
        printf("1 - Questao 1: Gerar Grafo e Mostrar Estrutura\n");
<<<<<<< HEAD
        printf("2 - Questao 2: Busca em Largura\n");
        printf("3 - Questao 3: Busca em Profundidade\n");
        printf("4 - Questao 4: Todos os caminhos usando DFS\n");
        printf("5 - Questao 5: Deteccao de ciclos\n");
=======
        printf("2 - Questao 2: Busca em Largura (Mostrar Arvore Resultante)\n");
        printf("4 - Questao 4: Todos os caminhos usando busca em profundidade\n");        
>>>>>>> b79da79ecd42fdcff8474b26a7a59721cf4b7262
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

                int tamanhos_q1[] = {5, 10, 50, 100};
                float graus_q1[] = {0.25, 0.50, 0.75, 1.00};

                for (int t = 0; t < 4; t++) {
                    for (int g = 0; g < 4; g++) {
                        Grafo* grafo_q1 = gerar_grafo_conexo(
                            tamanhos_q1[t],
                            graus_q1[g]
                        );

                        // Substituição aqui: O uso direto foi trocado pelos Getters
                        printf(
                            "Grafo gerado -> Vertices: %3d | "
                            "Conectividade: %3.0f%% | Arestas: %d\n",
                            obter_num_vertices(grafo_q1),
                            graus_q1[g] * 100,
                            obter_num_arestas(grafo_q1)
                        );

                        if (
                            tamanhos_q1[t] == 5 &&
                            graus_q1[g] == 0.50
                        ) {
                            printf(
                                "\n[Demonstracao Visual da Estrutura "
                                "(V=5, 50%%)]\n"
                            );

                            imprimir_grafo(grafo_q1);
                            printf("\n");
                        }

                        liberar_grafo(grafo_q1);
                    }

                    printf(
                        "--------------------------------------------------\n"
                    );
                }

                break;
            }

            case 2: {
                printf(
                    "\n--- EXECUTANDO QUESTAO 2: "
                    "BUSCA EM LARGURA ---\n"
                );

                printf(
                    "\nParte A: Arvore Resultante "
                    "(Grafo de 10 vertices, 50%% conectividade)\n"
                );

                Grafo* g_visual = gerar_grafo_conexo(10, 0.50);

                bfs_arvore(g_visual, 0, true);

                liberar_grafo(g_visual);

                printf(
                    "\nParte B: Analise de Tempo "
                    "(Grafo de 250 vertices)\n"
                );

                int V_grande = 250;
                float graus_q2[] = {0.25, 0.50, 0.75, 1.00};

                for (int i = 0; i < 4; i++) {
                    printf(
                        "\n> Testando Conectividade %.0f%%:\n",
                        graus_q2[i] * 100
                    );

                    Grafo* g_tempo = gerar_grafo_conexo(
                        V_grande,
                        graus_q2[i]
                    );

                    testar_tempos_bfs(g_tempo, 10);

                    liberar_grafo(g_tempo);
                }

                break;
            }

            case 3: {
                printf(
                    "\n--- EXECUTANDO QUESTAO 3: "
                    "BUSCA EM PROFUNDIDADE ---\n"
                );

                printf(
                    "\nParte A: Sequencia de vertices visitados "
                    "(Grafo de 10 vertices, 50%% conectividade)\n"
                );

                Grafo* g_visual_dfs = gerar_grafo_conexo(10, 0.50);

                printf("\nEstrutura do grafo utilizado:\n");
                imprimir_grafo(g_visual_dfs);

                printf("\nResultado da Busca em Profundidade:\n");

                dfs_profundidade(g_visual_dfs, 0, true);

                liberar_grafo(g_visual_dfs);

                printf(
                    "\nParte B: Analise de Tempo "
                    "(Grafos de 250 vertices)\n"
                );

                int V_dfs = 250;

                float graus_q3[] = {
                    0.25,
                    0.50,
                    0.75,
                    1.00
                };

                for (int i = 0; i < 4; i++) {
                    printf(
                        "\n> Testando Conectividade %.0f%%:\n",
                        graus_q3[i] * 100
                    );

                    Grafo* g_tempo_dfs = gerar_grafo_conexo(
                        V_dfs,
                        graus_q3[i]
                    );

                    testar_tempos_dfs(g_tempo_dfs, 10);

                    liberar_grafo(g_tempo_dfs);
                }

                break;
            }

            case 4: {
                printf(
                    "\n--- EXECUTANDO QUESTAO 4: "
                    "TODOS OS CAMINHOS ---\n"
                );

                printf(
                    "\n> Exemplo 1: Grafo em linha (0-1-2-3)\n"
                );

                Grafo* g_linha = criar_grafo(4);

                adicionar_aresta(g_linha, 0, 1);
                adicionar_aresta(g_linha, 1, 2);
                adicionar_aresta(g_linha, 2, 3);

                todos_os_caminhos(g_linha, 0);

                liberar_grafo(g_linha);

                printf(
                    "\n> Exemplo 2: Grafo completo K4 "
                    "(Todos conectados a todos)\n"
                );

                Grafo* g_completo = criar_grafo(4);

                adicionar_aresta(g_completo, 0, 1);
                adicionar_aresta(g_completo, 0, 2);
                adicionar_aresta(g_completo, 0, 3);
                adicionar_aresta(g_completo, 1, 2);
                adicionar_aresta(g_completo, 1, 3);
                adicionar_aresta(g_completo, 2, 3);

                todos_os_caminhos(g_completo, 0);

                liberar_grafo(g_completo);

                printf(
                    "\n> Exemplo 3: Grafo com 5 vertices "
                    "(Gerado automaticamente)\n"
                );

                Grafo* g_auto = gerar_grafo_conexo(5, 0.50);

                imprimir_grafo(g_auto);
                todos_os_caminhos(g_auto, 0);

                liberar_grafo(g_auto);

                break;
            }
            case 5: {
                printf("\n--- EXECUTANDO QUESTAO 5: DETECCAO DE CICLOS ---\n");

                printf("\n> Exemplo 1: Triangulo (0-1-2-0) -> Tem ciclo de tamanho 3\n");
                Grafo *g1 = criar_grafo(3);
                adicionar_aresta(g1, 0, 1);
                adicionar_aresta(g1, 1, 2);
                adicionar_aresta(g1, 2, 0);
                printf("Resultado: %s\n", grafo_tem_ciclo(g1) ? "TEM ciclo" : "NAO tem ciclo");
                liberar_grafo(g1);

                printf("\n> Exemplo 2: Arvore (0-1, 1-2, 1-3) -> Nao tem ciclo\n");
                Grafo *g2 = criar_grafo(4);
                adicionar_aresta(g2, 0, 1);
                adicionar_aresta(g2, 1, 2);
                adicionar_aresta(g2, 1, 3);
                printf("Resultado: %s\n", grafo_tem_ciclo(g2) ? "TEM ciclo" : "NAO tem ciclo");
                liberar_grafo(g2);

                printf("\n> Exemplo 3: Quadrado (0-1-2-3-0) -> Tem ciclo de tamanho 4\n");
                Grafo *g3 = criar_grafo(4);
                adicionar_aresta(g3, 0, 1);
                adicionar_aresta(g3, 1, 2);
                adicionar_aresta(g3, 2, 3);
                adicionar_aresta(g3, 3, 0);
                printf("Resultado: %s\n", grafo_tem_ciclo(g3) ? "TEM ciclo" : "NAO tem ciclo");
                liberar_grafo(g3);

                printf("\n> Exemplo 4: Grafo desconexo, um componente com ciclo\n");
                Grafo *g4 = criar_grafo(6);
                adicionar_aresta(g4, 0, 1);
                adicionar_aresta(g4, 1, 2);
                adicionar_aresta(g4, 3, 4);
                adicionar_aresta(g4, 4, 5);
                adicionar_aresta(g4, 5, 3);
                printf("Resultado: %s\n", grafo_tem_ciclo(g4) ? "TEM ciclo" : "NAO tem ciclo");
                liberar_grafo(g4);

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
