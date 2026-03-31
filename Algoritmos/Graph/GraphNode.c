#include <stdlib.h>
#include "GraphNode.h"

// Crear nodo

GraphNode* gn_crear(Estacion *e) {
    GraphNode *nodo = malloc(sizeof(GraphNode));
    if (!nodo) return NULL;

    nodo->data = e;
    nodo->adyacentes = NULL;

    return nodo;
}

// Crear arista

GraphEdge* ge_crear(GraphNode *destino, double peso) {
    GraphEdge *edge = malloc(sizeof(GraphEdge));
    if (!edge) return NULL;

    edge->destino = destino;
    edge->peso = peso;
    edge->siguiente = NULL;

    return edge;
}

// Agregar arista (lista enlazada)

void gn_agregar_arista(GraphNode *origen, GraphNode *destino, double peso) {
    GraphEdge *edge = ge_crear(destino, peso);

    edge->siguiente = origen->adyacentes;
    origen->adyacentes = edge;
}