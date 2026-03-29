#ifndef GENERADOR_DATOS_H
#define GENERADOR_DATOS_H

#include "../Estacion/Estacion.h"


Estacion* generar_estaciones(int cantidadFrecuencias, int cantidadEstaciones); 

void liberar_estaciones(Estacion *datos);

#endif