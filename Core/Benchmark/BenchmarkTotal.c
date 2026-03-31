#include <stdio.h>

#include "BenchmarkTotal.h"
#include "GeneradorDatos.h"
#include "BenchmarkHash.h"
#include "BenchmarkB+Tree.h"
#include "BenchmarkSpatialTree.h"
#include "BenchmarkGraph.h"
#include "Estacion.h"

void ejecutar_benchmark_total() {

    printf("\nBENCHMARK WEMAPS CORE\n");

    int n = 10000000;
    int estaciones = 100;

    Estacion *datos = generar_estaciones(n, estaciones);

    if (!datos) {
        printf("Error generando datos\n");
        return;
    }

    // Hash
    // Con este sacamos el objeto base a buscar, sus atributos nos servirán en las otras estructuras. 

    Estacion *res_hash = benchmark_hash(datos, n);

    if (!res_hash) {
        printf("Error: Hash no devolvió resultado\n");
        return;
    }

    double lat = res_hash->latitud;
    double lon = res_hash->longitud;

    Estacion *res_bpt = benchmark_bptree(datos, n, lat, lon);
    Estacion *res_spt = benchmark_spatial(datos, n, lat, lon);
    GraphNode *res_graph = benchmark_graph(datos, n, lat, lon);

    // Validación Global

    printf("\n=== VALIDACIÓN GLOBAL ===\n");

    if (res_hash && res_bpt &&
        res_hash->id_estacion == res_bpt->id_estacion) {
        printf("B+ Tree coincide con Hash \n");
    }

    if (res_hash && res_spt &&
        res_hash->id_estacion == res_spt->id_estacion) {
        printf("Spatial coincide con Hash\n");
    }

    if (res_graph && res_hash &&
        res_graph->data == res_hash) {
        printf("Graph coincide en puntero\n");
    }

    // Limpieza

    liberar_estaciones(datos);
    printf("\n=== FIN BENCHMARK ===\n");
}