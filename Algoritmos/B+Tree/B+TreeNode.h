#ifndef BPTREENODE_H
#define BPTREENODE_H

#include <stdbool.h>
#include "../../Estacion/Estacion.h"

#define BPT_ORDER 4

typedef struct BPTNode {

    bool es_hoja;
    int num_claves;
    double claves[BPT_ORDER - 1];
    struct BPTNode *hijos[BPT_ORDER];
    Estacion *datos[BPT_ORDER - 1];
    struct BPTNode *siguiente;
    struct BPTNode *padre; 
    
} BPTNode;

// Crear nodo

BPTNode* bptn_crear(bool es_hoja);

// Insertar en hoja

void bptn_insertar_en_hoja(BPTNode *hoja, Estacion *e);

#endif