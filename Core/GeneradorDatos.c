#include <stdlib.h>
#include <time.h>
#include "GeneradorDatos.h"

Estacion* generar_estaciones(int cantidadFrecuencias, int cantidadEstaciones) {
    Estacion *datos = malloc(sizeof(Estacion) * cantidadFrecuencias);
    if (datos == NULL)
        return NULL;

    time_t inicio = time(NULL);

    for (int i = 0; i < cantidadFrecuencias; i++) {

        int id_estacion = i ; // No estamos usando cantidadEstaciones porque genera NO determinismo cuando buscamos por latitud y longitud

        datos[i].id_estacion = i + 1;  

        datos[i].latitud = 10.0 + id_estacion * 0.01;
        datos[i].longitud = -75.0 + id_estacion * 0.01;
        datos[i].temperatura = 20.0 + (rand() % 30);
        datos[i].fecha = inicio + (i / cantidadEstaciones) * 60;
        
    }

    return datos;
}

void liberar_estaciones(Estacion *datos) {
    free(datos);
}