#ifndef MOTORCONSULTAS_H
#define MOTORCONSULTAS_H
#include "EstructuraOps.h"

#include <stdint.h>



// Inserción
double ejecutar_insercion(EstructuraOps *ops, Estacion *datos, int cantidad);

// Búsquedas
double ejecutar_busqueda_id(EstructuraOps *ops, uint64_t id, Estacion **resultado);
double ejecutar_busqueda_coord(EstructuraOps *ops, double lat, double lon, Estacion **resultado);

#endif