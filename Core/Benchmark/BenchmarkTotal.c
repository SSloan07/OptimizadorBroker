#include <stdio.h>

#include "BenchmarkTotal.h"
#include "GeneradorDatos.h"
#include "BenchmarkHash.h"
#include "BenchmarkB+Tree.h"
#include "BenchmarkSpatialTree.h"
#include "BenchmarkGraph.h"
#include "Estacion.h"

#define RESET   "\x1b[0m"
#define ROJO    "\x1b[31m"
#define VERDE   "\x1b[32m"
#define AMARILLO "\x1b[33m"
#define AZUL    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define NEGRITA "\x1b[1m"
#define SEPARADOR "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"

void ejecutar_benchmark_total() {

    printf(NEGRITA CYAN "\n%s\n" RESET, SEPARADOR);
    printf(NEGRITA CYAN "   BENCHMARK WEMAPS CORE\n" RESET);
    printf(NEGRITA CYAN "%s\n" RESET, SEPARADOR);

    int n = 10000000;
    int estaciones = 100;

    Estacion *datos = generar_estaciones(n, estaciones);

    if (!datos) {
        printf(ROJO "Error generando datos\n" RESET);
        return;
    }

    // Hash
    // Con el objeto que sacamos de acá, usamos sus propiedades para buscar el mismo objeto.
    printf(NEGRITA AZUL "\n━━━ HASH TABLE ━━━\n" RESET);

    Estacion *res_hash = benchmark_hash(datos, n);

    if (!res_hash) {
        printf(ROJO "Error: Hash no devolvió resultado\n" RESET);
        return;
    }

    double lat = res_hash->latitud;
    double lon = res_hash->longitud;
    printf(NEGRITA MAGENTA "\n━━━ B+ TREE ━━━\n" RESET);
    Estacion *res_bpt = benchmark_bptree(datos, n, lat, lon);
    printf(NEGRITA VERDE "\n━━━ SPATIAL TREE ━━━\n" RESET);
    Estacion *res_spt = benchmark_spatial(datos, n, lat, lon);
    printf(NEGRITA AMARILLO "\n━━━ GRAPH ━━━\n" RESET);
    GraphNode *res_graph = benchmark_graph(datos, n, lat, lon);

    // Validación

    printf(NEGRITA CYAN "\n%s\n" RESET, SEPARADOR);
    printf(NEGRITA CYAN "   VALIDACIÓN GLOBAL\n" RESET);
    printf(NEGRITA CYAN "%s\n" RESET, SEPARADOR);

    if (res_hash && res_bpt &&
        res_hash->id_estacion == res_bpt->id_estacion) {
        printf(VERDE "B+ Tree coincide con Hash\n" RESET);
    } else {
        printf(ROJO "B+ Tree NO coincide\n" RESET);
    }

    if (res_hash && res_spt &&
        res_hash->id_estacion == res_spt->id_estacion) {
        printf(VERDE "Spatial coincide con Hash\n" RESET);
    } else {
        printf(ROJO "Spatial NO coincide\n" RESET);
    }

    if (res_graph && res_hash &&
        res_graph->data == res_hash) {
        printf(VERDE "Graph coincide con Hash\n" RESET);
    } else {
        printf(ROJO "Graph NO coincide\n" RESET);
    }

    // Limpieza

    liberar_estaciones(datos);

    printf(NEGRITA CYAN "\n%s\n" RESET, SEPARADOR);
    printf(NEGRITA CYAN "   FIN BENCHMARK\n" RESET);
    printf(NEGRITA CYAN "%s\n\n" RESET, SEPARADOR);
}