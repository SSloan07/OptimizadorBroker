#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "Graph.h"
#include "GraphNode.h"

// Crear grafo

Graph* graph_crear(int capacidad) {
    Graph *g = malloc(sizeof(Graph));
    if (!g) return NULL;

    g->nodos = malloc(sizeof(GraphNode*) * capacidad);
    g->cantidad = 0;
    g->capacidad = capacidad;

    return g;
}

// Agregar nodo

void graph_agregar_nodo(Graph *g, Estacion *e) {
    if (g->cantidad >= g->capacidad) return;

    GraphNode *nodo = gn_crear(e);
    nodo->indice = g->cantidad; 
    g->nodos[g->cantidad++] = nodo;
}

// Conectar nodos (bidireccional)

void graph_conectar(Graph *g, GraphNode *a, GraphNode *b, double peso) {
    (void)g;
    gn_agregar_arista(a, b, peso);
    gn_agregar_arista(b, a, peso);
}

// Distancia simple

static double distancia(Estacion *a, Estacion *b) {
    double dx = a->latitud - b->latitud;
    double dy = a->longitud - b->longitud;
    return sqrt(dx*dx + dy*dy);
}

void graph_construir_local(Graph *g, int k) {

    for (int i = 0; i < g->cantidad; i++) {

        for (int j = i + 1; j < i + k && j < g->cantidad; j++) {

            double d = distancia(
                g->nodos[i]->data,
                g->nodos[j]->data
            );

            graph_conectar(g, g->nodos[i], g->nodos[j], d);
        }
    }
}

// BFS

void graph_bfs(Graph *g, GraphNode *inicio) {
    if (!inicio) return;

    int *visitado = calloc(g->cantidad, sizeof(int));
    GraphNode **cola = malloc(sizeof(GraphNode*) * g->cantidad);

    int frente = 0, final = 0;

    cola[final++] = inicio;

    while (frente < final) {

        GraphNode *actual = cola[frente++];

        int idx = actual->indice;

        if (visitado[idx]) continue;

        visitado[idx] = 1;

        GraphEdge *edge = actual->adyacentes;

        while (edge) {
            int idx_dest = edge->destino->indice;

            if (!visitado[idx_dest] && final < g->cantidad) {
                cola[final++] = edge->destino;
            }

            edge = edge->siguiente;
        }
    }

    free(visitado);
    free(cola);
}   
// Destructor

void graph_destruir(Graph *g) {
    if (!g) return;

    for (int i = 0; i < g->cantidad; i++) {

        GraphEdge *edge = g->nodos[i]->adyacentes;

        while (edge) {
            GraphEdge *tmp = edge;
            edge = edge->siguiente;
            free(tmp);
        }

        free(g->nodos[i]);
    }

    free(g->nodos);
    free(g);
}