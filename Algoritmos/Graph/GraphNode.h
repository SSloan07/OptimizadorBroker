#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include "../../Estacion/Estacion.h"

// Forward declaration (importante)
typedef struct GraphNode GraphNode;

typedef struct GraphEdge {
    GraphNode *destino;
    double peso;
    struct GraphEdge *siguiente;
} GraphEdge;

struct GraphNode {
    Estacion *data;
    GraphEdge *adyacentes;
    int indice;
};


GraphNode* gn_crear(Estacion *e);
void gn_agregar_arista(GraphNode *origen, GraphNode *destino, double peso);

#endif