#ifndef SPATIALTREE_H
#define SPATIALTREE_H

#include "../../Estacion/Estacion.h"
#include "SpatialNode.h"

// Estructura

typedef struct {
    SpatialNode *raiz;
} SpatialTree;

// Crear

SpatialTree* spt_crear(double lat_min, double lat_max, double lon_min, double lon_max);

// Insertar

void spt_insertar(SpatialTree *tree, Estacion *e);

// Buscar exacto (lat, lon)

Estacion* spt_buscar_exacto(SpatialTree *tree, double lat, double lon);

// Buscar rango espacial

void spt_buscar_rango(
    SpatialTree *tree,
    double lat_min, double lat_max,
    double lon_min, double lon_max
);

// Destruir

void spt_destruir(SpatialTree *tree);

// Wrappers 

void spt_insertar_wrapper(void *estructura, Estacion *e);
Estacion* spt_buscar_exacto_wrapper(void *estructura, double lat, double lon);
void spt_buscar_rango_wrapper(void *estructura,double lat_min, double lat_max,double lon_min, double lon_max);

#endif