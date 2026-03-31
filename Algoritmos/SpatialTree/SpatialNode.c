#include <stdlib.h>
#include "SpatialNode.h"

// Crear nodo

SpatialNode* spn_crear(double lat_min, double lat_max, double lon_min, double lon_max) {
    SpatialNode *nodo = malloc(sizeof(SpatialNode));
    if (!nodo) return NULL;

    nodo->lat_min = lat_min;
    nodo->lat_max = lat_max;
    nodo->lon_min = lon_min;
    nodo->lon_max = lon_max;

    nodo->num_datos = 0;
    nodo->dividido = false;

    for (int i = 0; i < 4; i++)
        nodo->hijos[i] = NULL;

    return nodo;
}

// Determinar cuadrante

static int obtener_cuadrante(SpatialNode *nodo, Estacion *e) {
    double lat_mid = (nodo->lat_min + nodo->lat_max) / 2;
    double lon_mid = (nodo->lon_min + nodo->lon_max) / 2;

    bool norte = e->latitud >= lat_mid;
    bool este  = e->longitud >= lon_mid;

    if (norte && !este) return 0; // NW
    if (norte && este)  return 1; // NE
    if (!norte && !este) return 2; // SW
    return 3; // SE
}

// Subdividir nodo

static void subdividir(SpatialNode *nodo) {

    double lat_mid = (nodo->lat_min + nodo->lat_max) / 2;
    double lon_mid = (nodo->lon_min + nodo->lon_max) / 2;

    nodo->hijos[0] = spn_crear(lat_mid, nodo->lat_max, nodo->lon_min, lon_mid); // NW
    nodo->hijos[1] = spn_crear(lat_mid, nodo->lat_max, lon_mid, nodo->lon_max); // NE
    nodo->hijos[2] = spn_crear(nodo->lat_min, lat_mid, nodo->lon_min, lon_mid); // SW
    nodo->hijos[3] = spn_crear(nodo->lat_min, lat_mid, lon_mid, nodo->lon_max); // SE

    nodo->dividido = true;

    for (int i = 0; i < nodo->num_datos; i++) {
        Estacion *e = nodo->datos[i];
        int q = obtener_cuadrante(nodo, e);
        spn_insertar(nodo->hijos[q], e);
    }

    nodo->num_datos = 0; // limpiar nodo
}

// Insertar

void spn_insertar(SpatialNode *nodo, Estacion *e) {

    // fuera del área del nodo
    if (e->latitud < nodo->lat_min || e->latitud > nodo->lat_max ||
        e->longitud < nodo->lon_min || e->longitud > nodo->lon_max)
        return;

    // si no está dividido y hay espacio
    if (!nodo->dividido && nodo->num_datos < CAPACIDAD_NODO) {
        nodo->datos[nodo->num_datos++] = e;
        return;
    }

    // subdividir si es necesario
    if (!nodo->dividido) {
        subdividir(nodo);
    }

    // insertar en el cuadrante correcto
    int q = obtener_cuadrante(nodo, e);
    spn_insertar(nodo->hijos[q], e);
}