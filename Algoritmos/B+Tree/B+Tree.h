#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include <stdint.h>
#include "../../Estacion/Estacion.h"
#include "B+TreeNode.h"   


// Estructura del árbol

typedef struct {
    BPTNode *raiz;
} BPlusTree;

// Funciones principales

// Crear árbol

BPlusTree* bpt_crear();

// Insertar estación

void bpt_insertar(BPlusTree *tree, Estacion *e);
void bpt_buscar_rango(BPlusTree *tree, double lat_min, double lat_max);
Estacion* bpt_buscar_exacto(BPlusTree *tree, double lat, double lon);

// Destruir árbol

void bpt_destruir(BPlusTree *tree);

// Wrappers (para interfaz)

void bpt_insertar_wrapper(void *estructura, Estacion *e);
Estacion* bpt_buscar_exacto_wrapper(void *estructura, double lat, double lon);


#endif