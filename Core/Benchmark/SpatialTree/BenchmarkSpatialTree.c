#include <stdio.h>
#include <time.h>

#include "SpatialTree.h"
#include "BenchmarkSpatialTree.h"

#include "EstructuraOps.h"
#include "MotorConsultas.h"

Estacion* benchmark_spatial(Estacion *datos, int n, double lat, double lon) {

    printf("\n=== SPATIAL TREE ===\n");

    // Crear árbol
    SpatialTree *spt = spt_crear(-90, 90, -180, 180);

    EstructuraOps ops = {
        .estructura = spt,
        .insertar = spt_insertar_wrapper,
        .buscar_id = NULL,
        .buscar_coord = spt_buscar_exacto_wrapper,
        .buscar_rango = spt_buscar_rango_wrapper
    };

    // Inserción masiva
    double tiempo_insert = ejecutar_insercion(&ops, datos, n);

    printf("Inserción Spatial Tree: %f segundos\n", tiempo_insert);

    // Búsqueda exacta
    Estacion *resultado = NULL;

    double tiempo_busqueda =ejecutar_busqueda_coord(&ops, lat, lon, &resultado);
    printf("Tiempo búsqueda Spatial Tree: %f segundos\n", tiempo_busqueda);

    if (!resultado) {
        printf("Spatial Tree no encontró el elemento\n");
    }

    // Búsqueda por rango
    double lat_min = lat - 0.2;
    double lat_max = lat + 0.2;
    double lon_min = lon - 0.2;
    double lon_max = lon + 0.2;

    clock_t inicio = clock();

    ops.buscar_rango(
        ops.estructura,
        lat_min, lat_max,
        lon_min, lon_max
    );

    clock_t fin = clock();

    double tiempo_rango =
        (double)(fin - inicio) / CLOCKS_PER_SEC;

    printf("Spatial Tree rango ejecutado en: %f segundos\n", tiempo_rango);

    // Liberar memoria
    spt_destruir(spt);

    return resultado;
}