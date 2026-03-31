#include <stdio.h>
#include <time.h>
#include <math.h>

#include "BenchmarkGraph.h"


#include "Graph.h"
#include "Estacion.h"

GraphNode* benchmark_graph(Estacion *datos, int n, double lat, double lon) {

    printf("\n=== GRAPH ===\n");

    // Crear grafo
    Graph *g = graph_crear(n);

    // Inserción de nodos
    clock_t inicio_insert = clock();

    for (int i = 0; i < n; i++) {
        graph_agregar_nodo(g, &datos[i]);
    }

    clock_t fin_insert = clock();

    printf("Inserción Graph: %f segundos\n",
        (double)(fin_insert - inicio_insert) / CLOCKS_PER_SEC);

    // Construcción de conexiones
    clock_t inicio_build = clock();

    graph_construir_local(g, 10); // k vecinos
    // Esta vaina lo que hace es conectar un nodo a 10, es como conectar un pueblito con 10 y solo 10 carreteras, donde cada carretera lleva a un unico pueblito

    clock_t fin_build = clock();

    printf("Construcción conexiones Graph: %f segundos\n",
        (double)(fin_build - inicio_build) / CLOCKS_PER_SEC);

    // Búsqueda del nodo (por coordenadas)
    GraphNode *nodo = NULL;

    clock_t inicio_search = clock();

    for (int i = 0; i < g->cantidad; i++) {
        Estacion *e = g->nodos[i]->data;

        if (fabs(e->latitud - lat) < 0.00001 &&
            fabs(e->longitud - lon) < 0.00001) {

            nodo = g->nodos[i];
            break;
        }
    }

    clock_t fin_search = clock();

    printf("Tiempo búsqueda Graph: %f segundos\n",
        (double)(fin_search - inicio_search) / CLOCKS_PER_SEC);

    // Recorrido BFS
    if (nodo) {

        clock_t inicio_bfs = clock();

        graph_bfs(g, nodo);

        clock_t fin_bfs = clock();

        printf("Graph recorrido ejecutado en: %f segundos\n",
            (double)(fin_bfs - inicio_bfs) / CLOCKS_PER_SEC);

    } else {
        printf("Nodo no encontrado en Graph\n");
    }

    // Liberar memoria
    graph_destruir(g);

    return nodo;
}