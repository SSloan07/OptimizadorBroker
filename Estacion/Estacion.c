#include "Estacion.h"

// Setters

EstacionStatus set_id_estacion(Estacion *e, uint64_t id){
    if (e == NULL)
        return ESTACION_ERROR_NULL;

    if (id == 0)
        return ESTACION_ERROR_ID_INVALIDO;

    e->id_estacion = id;
    return ESTACION_OK; 
}
EstacionStatus set_latitud(Estacion *e, double lat){
    if (e == NULL)
        return ESTACION_ERROR_NULL;

    if (lat < -90.0 || lat > 90.0)
        return ESTACION_ERROR_RANGO_LATITUD;

    e->latitud = lat;
    return ESTACION_OK; 
}
EstacionStatus set_longitud(Estacion *e, double lon){
    if (e == NULL)
        return ESTACION_ERROR_NULL;

    if (lon < -180.0 || lon > 180.0)
        return ESTACION_ERROR_RANGO_LONGITUD;

    e->longitud = lon;
    return ESTACION_OK; 
}
EstacionStatus set_temperatura(Estacion *e, float temp){
    if (e == NULL)
        return ESTACION_ERROR_NULL;

    if (temp < -100.0 || temp > 100.0)
        return ESTACION_ERROR_RANGO_TEMPERATURA;

    e->temperatura = temp;
    return ESTACION_OK; 
}
EstacionStatus set_fecha(Estacion *e, time_t ts){
    if (e == NULL)
        return ESTACION_ERROR_NULL;

    if (ts < 0)
        return ESTACION_ERROR_FECHA_INVALIDA;

    e->fecha = ts;
    return ESTACION_OK; 
}

// Getters

uint64_t get_id_estacion(const Estacion *e){
    return e->id_estacion;
}
double get_latitud(const Estacion *e){
    return e->latitud;
}
double get_longitud(const Estacion *e){
    return e->longitud;
}
float get_temperatura(const Estacion *e){
    return e->temperatura;
}
time_t get_fecha(const Estacion *e){
    return e->fecha;
}

// Constructor

Estacion* crear_estacion(uint64_t id, double lat, double lon, float temp, time_t ts){
    Estacion *e = malloc(sizeof(Estacion));
    if (e == NULL)
        return NULL;

    EstacionStatus status = ESTACION_OK;

    do {
        status = set_id_estacion(e, id);
        if (status != ESTACION_OK) break;

        status = set_latitud(e, lat);
        if (status != ESTACION_OK) break;

        status = set_longitud(e, lon);
        if (status != ESTACION_OK) break;

        status = set_temperatura(e, temp);
        if (status != ESTACION_OK) break;

        status = set_fecha(e, ts);
        if (status != ESTACION_OK) break;

    } while (0);

    if (status != ESTACION_OK) {
        free(e);
        return NULL;
    }

    return e;
}

// Destructor

void destruir_estacion(Estacion *e){
    if (e == NULL)
        return;

    free(e);
}