#ifndef ESTACION_STATUS_H
#define ESTACION_STATUS_H

// Establecemos los diferentes errores que pueden haber 

typedef enum {
    ESTACION_OK = 0,
    ESTACION_ERROR_NULL,
    ESTACION_ERROR_RANGO_LATITUD,
    ESTACION_ERROR_RANGO_LONGITUD,
    ESTACION_ERROR_RANGO_TEMPERATURA,
    ESTACION_ERROR_FECHA_INVALIDA,
    ESTACION_ERROR_ID_INVALIDO
} EstacionStatus;

// Esto nos permite pasar de numeros a un error concreto. 

const char* estacion_status_str(EstacionStatus status);

#endif