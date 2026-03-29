#ifndef ESTRUCTURAOPS_H
#define ESTRUCTURAOPS_H

#include "../Estacion/Estacion.h"

typedef struct {
    void *estructura;
    void (*insertar)(void *estructura, Estacion *e);
    Estacion* (*buscar)(void *estructura, uint64_t id);
} EstructuraOps;

// Funciones

void insertar_masivo(EstructuraOps *ops, Estacion *datos, int cantidad);
Estacion* buscar(EstructuraOps *ops, uint64_t id); 

#endif