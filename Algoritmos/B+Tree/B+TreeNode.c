#include <stdlib.h>
#include "B+TreeNode.h"

// Crear nodo

BPTNode* bptn_crear(bool es_hoja) {
    BPTNode *nodo = malloc(sizeof(BPTNode));
    if (!nodo) return NULL;

    nodo->es_hoja = es_hoja;
    nodo->num_claves = 0;
    nodo->siguiente = NULL;
    nodo->padre = NULL;

    for (int i = 0; i < BPT_ORDER; i++)
        nodo->hijos[i] = NULL;

    return nodo;
}

// Insertar en hoja (ordenado)

void bptn_insertar_en_hoja(BPTNode *hoja, Estacion *e) {
    double clave = e->latitud;

    int i = hoja->num_claves - 1;

    while (i >= 0 && hoja->claves[i] > clave) {
        hoja->claves[i + 1] = hoja->claves[i];
        hoja->datos[i + 1] = hoja->datos[i];
        i--;
    }

    hoja->claves[i + 1] = clave;
    hoja->datos[i + 1] = e;
    hoja->num_claves++;
}