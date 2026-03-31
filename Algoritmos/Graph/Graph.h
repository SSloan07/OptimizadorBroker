#ifndef GRAPH_H
#define GRAPH_H

#include "GraphNode.h"

typedef struct {
    GraphNode **nodos;
    int cantidad;
    int capacidad;
} Graph;

// Crear

Graph* graph_crear(int capacidad);

// Insertar nodo

void graph_agregar_nodo(Graph *g, Estacion *e);

// Conectar nodos

void graph_conectar(Graph *g, GraphNode *a, GraphNode *b, double peso);

// Construir conexiones por proximidad

void graph_construir_local(Graph *g, int k);

// BFS / recorrido

void graph_bfs(Graph *g, GraphNode *inicio);

// Destructor

void graph_destruir(Graph *g);

#endif