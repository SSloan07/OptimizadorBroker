#include <stdio.h>
#include <time.h>

#include "BenchmarkB+Tree.h"
#include "B+Tree.h"
#include "EstructuraOps.h"
#include "MotorConsultas.h"
#include "Estacion/Estacion.h"

Estacion* benchmark_bptree(Estacion *datos, int n, double lat, double lon) {

    // Crear estructura
    BPlusTree *bpt = bpt_crear();

    EstructuraOps ops = {
        .estructura = bpt,
        .insertar = bpt_insertar_wrapper,
        .buscar_id = NULL,
        .buscar_coord = bpt_buscar_exacto_wrapper
    };

    // Inserción masiva
    double tiempo_insert =
        ejecutar_insercion(&ops, datos, n);

    printf("Inserción B+ Tree: %f segundos\n", tiempo_insert);

    // Búsqueda exacta
    Estacion *resultado = NULL;

    double tiempo_busqueda =
        ejecutar_busqueda_coord(&ops, lat, lon, &resultado);

    printf("Tiempo búsqueda B+ Tree: %f segundos\n", tiempo_busqueda);

    // Búsqueda por rango
    double lat_min = lat - 0.2;
    double lat_max = lat + 0.2;

    clock_t inicio = clock();

    bpt_buscar_rango(bpt, lat_min, lat_max);

    clock_t fin = clock();

    double tiempo_rango =
        (double)(fin - inicio) / CLOCKS_PER_SEC;

    printf("B+ Tree rango ejecutado en: %f segundos\n", tiempo_rango);

    // Liberar memoria
    bpt_destruir(bpt);

    return resultado;
}