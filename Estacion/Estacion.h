#ifndef ESTACION_H
#define ESTACION_H

#include <stdint.h>
#include <time.h>
#include "estacion_status.h"
#include <stdlib.h>

// Definición de la estructura

typedef struct {
    uint64_t id_estacion;
    double latitud;
    double longitud;
    float temperatura;
    time_t fecha;
} Estacion;

// Setters

/*
    Para lo que son las variables establecimos unos rangos, para que la información sea realmente confiable(real). 
    En este sentido, para cada una de las variables mostraremos a continuación las reglas que ya hemos establecido:
    
    1) Latitud - [-90,90]
    2) Longitud - [-180,180]
    3) Temperatura - [-100,100] 
    4) Fecha - Timestamp valido. Es decir >= 0. 

    La temperatura es así porque lo estamos midiendo en grados Centigrados.
*/ 

EstacionStatus set_id_estacion(Estacion *e, uint64_t id); 
EstacionStatus set_latitud(Estacion *e, double lat);
EstacionStatus set_longitud(Estacion *e, double lon);
EstacionStatus set_temperatura(Estacion *e, float temp);
EstacionStatus set_fecha(Estacion *e, time_t ts);

// Getters

uint64_t get_id_estacion(const Estacion *e);
double get_latitud(const Estacion *e);
double get_longitud(const Estacion *e);
float get_temperatura(const Estacion *e);
time_t get_fecha(const Estacion *e);

// Constructor / Destructor

Estacion* crear_estacion(uint64_t id, double lat, double lon, float temp, time_t ts);
void destruir_estacion(Estacion *e);

#endif