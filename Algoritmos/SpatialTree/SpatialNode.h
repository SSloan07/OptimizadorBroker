#ifndef SPATIALNODE_H
#define SPATIALNODE_H

#include <stdbool.h>
#include "../../Estacion/Estacion.h"

#define CAPACIDAD_NODO 4

typedef struct SpatialNode {

    double lat_min, lat_max;
    double lon_min, lon_max;

    Estacion *datos[CAPACIDAD_NODO];
    int num_datos;

    struct SpatialNode *hijos[4]; // NW, NE, SW, SE

    bool dividido;

} SpatialNode;

SpatialNode* spn_crear(double lat_min, double lat_max, double lon_min, double lon_max);
void spn_insertar(SpatialNode *nodo, Estacion *e);

#endif