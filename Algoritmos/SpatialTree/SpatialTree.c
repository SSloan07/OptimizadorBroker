#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "SpatialTree.h"
#include "SpatialNode.h"

#define EPS 0.00001

// Crear árbol

SpatialTree* spt_crear(double lat_min, double lat_max, double lon_min, double lon_max) {
    SpatialTree *tree = malloc(sizeof(SpatialTree));
    if (!tree) return NULL;

    tree->raiz = spn_crear(lat_min, lat_max, lon_min, lon_max);
    return tree;
}

// Insertar

void spt_insertar(SpatialTree *tree, Estacion *e) {
    if (!tree || !e) return;

    spn_insertar(tree->raiz, e);
}

// Wrappers

void spt_insertar_wrapper(void *estructura, Estacion *e) {
    spt_insertar((SpatialTree*)estructura, e);
}

void spt_buscar_rango_wrapper(
    void *estructura,
    double lat_min, double lat_max,
    double lon_min, double lon_max
) {
    spt_buscar_rango(
        (SpatialTree*)estructura,
        lat_min, lat_max,
        lon_min, lon_max
    );
}

Estacion* spt_buscar_exacto_wrapper(void *estructura, double lat, double lon) {
    return spt_buscar_exacto((SpatialTree*)estructura, lat, lon);
}

// Muy Importante - Permite obtener lo que viene siendo los cuadrantes en los que está nuestra estación

static int obtener_cuadrante(SpatialNode *nodo, double lat, double lon) {
    double lat_mid = (nodo->lat_min + nodo->lat_max) / 2;
    double lon_mid = (nodo->lon_min + nodo->lon_max) / 2;

    bool norte = lat >= lat_mid;
    bool este  = lon >= lon_mid;

    if (norte && !este) return 0; // NW
    if (norte && este)  return 1; // NE
    if (!norte && !este) return 2; // SW
    return 3; // SE
}

// busqueda por rango

static void buscar_rango_nodo(
    SpatialNode *nodo,
    double lat_min, double lat_max,
    double lon_min, double lon_max
) {
    if (!nodo) return;

    // No intersecta sino que cortar
    if (nodo->lat_max < lat_min || nodo->lat_min > lat_max ||
        nodo->lon_max < lon_min || nodo->lon_min > lon_max)
        return;

    // Revisar datos
    for (int i = 0; i < nodo->num_datos; i++) {
        Estacion *e = nodo->datos[i];

        if (e->latitud >= lat_min && e->latitud <= lat_max &&
            e->longitud >= lon_min && e->longitud <= lon_max) {

            volatile double temp = e->temperatura;
            (void)temp;
        }
    }

    // Bajar a hijos
    if (nodo->dividido) {
        for (int i = 0; i < 4; i++) {
            buscar_rango_nodo(
                nodo->hijos[i],
                lat_min, lat_max,
                lon_min, lon_max
            );
        }
    }
}

// Busqueda exacta

static Estacion* buscar_exacto_nodo(SpatialNode *nodo, double lat, double lon) {
    if (!nodo) return NULL;

    // Fuera de rango
    if (lat < nodo->lat_min || lat > nodo->lat_max ||
        lon < nodo->lon_min || lon > nodo->lon_max)
        return NULL;

    // Buscar en datos del nodo
    for (int i = 0; i < nodo->num_datos; i++) {
        Estacion *e = nodo->datos[i];

        if (fabs(e->latitud - lat) < EPS &&
            fabs(e->longitud - lon) < EPS)
            return e;
    }

    // Bajar a hijos
    if (nodo->dividido) {
        int q = obtener_cuadrante(nodo, lat, lon);
        return buscar_exacto_nodo(nodo->hijos[q], lat, lon);
    }

    return NULL;
}

Estacion* spt_buscar_exacto(SpatialTree *tree, double lat, double lon) {
    if (!tree) return NULL;
    return buscar_exacto_nodo(tree->raiz, lat, lon);
}

// Rango

void spt_buscar_rango(
    SpatialTree *tree,
    double lat_min, double lat_max,
    double lon_min, double lon_max
) {
    if (!tree) return;

    buscar_rango_nodo(
        tree->raiz,
        lat_min, lat_max,
        lon_min, lon_max
    );
}

// Destructor

static void destruir_nodo(SpatialNode *nodo) {
    if (!nodo) return;

    if (nodo->dividido) {
        for (int i = 0; i < 4; i++) {
            destruir_nodo(nodo->hijos[i]);
        }
    }

    free(nodo);
}

void spt_destruir(SpatialTree *tree) {
    if (!tree) return;

    destruir_nodo(tree->raiz);
    free(tree);
}