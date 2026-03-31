#ifndef ESTRUCTURAOPS_H
#define ESTRUCTURAOPS_H

#include "../Estacion/Estacion.h"

typedef void (*BuscarRangoFunc)(
    void *estructura,
    double lat_min, double lat_max,
    double lon_min, double lon_max
);

typedef struct {
    void *estructura;
    void (*insertar)(void *estructura, Estacion *e);
    Estacion* (*buscar_id)(void *estructura, uint64_t id);
    Estacion* (*buscar_coord)(void *estructura, double lat, double lon);
    BuscarRangoFunc buscar_rango;
} EstructuraOps;

// Funciones

void insertar_masivo(EstructuraOps *ops, Estacion *datos, int cantidad);
Estacion* buscar_id(EstructuraOps *ops, uint64_t id); 
Estacion* buscar_coord(EstructuraOps *ops, double lat, double lon);

#endif