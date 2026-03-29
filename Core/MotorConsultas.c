#include <time.h>
#include "MotorConsultas.h"
#include "EstructuraOps.h"

// Inserción masiva

double ejecutar_insercion(EstructuraOps *ops, Estacion *datos, int cantidad) {
    if (!ops || !datos) return 0;

    clock_t inicio = clock();

    insertar_masivo(ops, datos, cantidad);

    clock_t fin = clock();

    return (double)(fin - inicio) / CLOCKS_PER_SEC;
}

// Búsqueda por ID

double ejecutar_busqueda_id(EstructuraOps *ops, uint64_t id, Estacion **resultado) {
    if (!ops || !resultado || !ops->buscar_id) return 0;

    clock_t inicio = clock();

    *resultado = ops->buscar_id(ops->estructura, id);

    clock_t fin = clock();

    return (double)(fin - inicio) / CLOCKS_PER_SEC;
}

// Búsqueda por coordenadas

double ejecutar_busqueda_coord(EstructuraOps *ops, double lat, double lon, Estacion **resultado) {
    if (!ops || !resultado || !ops->buscar_coord) return 0;

    clock_t inicio = clock();

    *resultado = ops->buscar_coord(ops->estructura, lat, lon);
    

    clock_t fin = clock();

    return (double)(fin - inicio) / CLOCKS_PER_SEC;
}