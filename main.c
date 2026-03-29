#include <stdio.h>
#include <inttypes.h>

#include "Estacion/Estacion.h"
#include "Algoritmos/HashTable/HashTable.h"
#include "Algoritmos/B+Tree/B+Tree.h"
#include "Core/EstructuraOps.h"
#include "Core/GeneradorDatos.h"
#include "Core/MotorConsultas.h"


void imprimir_estacion(const char *label, Estacion *e) {
    if (!e) {
        printf("%s: NULL\n", label);
        return;
    }

    printf("\n=== %s ===\n", label);
    printf("ID: %" PRIu64 "\n", get_id_estacion(e));
    printf("Latitud: %.10f\n", get_latitud(e));
    printf("Longitud: %.10f\n", get_longitud(e));
    printf("Temperatura: %.2f\n", get_temperatura(e));
    printf("Fecha: %ld\n", get_fecha(e));
}

int main() {

    int cantidadFrecuencias = 10000000;
    int cantidadEstaciones = 100;

    // Generar datos

    Estacion *datos = generar_estaciones(cantidadFrecuencias, cantidadEstaciones); 
    if (!datos) {
        printf("Error generando datos\n");
        return 1;
    }

    // HASH TABLE

    printf("\n=== HASH TABLE ===\n");

    HashTable *ht = ht_crear();

    EstructuraOps ops_hash = {
        .estructura = ht,
        .insertar = ht_insertar_wrapper,
        .buscar_id = ht_buscar_wrapper,
        .buscar_coord = NULL
    };

    double tiempo_hash_insert =
        ejecutar_insercion(&ops_hash, datos, cantidadFrecuencias);

    printf("Inserción Hash: %f segundos\n", tiempo_hash_insert);

    // BÚSQUEDA HASH (ID)

    uint64_t id_busqueda = 1000;
    Estacion *resultado_hash = NULL;

    double tiempo_hash_busqueda =
        ejecutar_busqueda_id(&ops_hash, id_busqueda, &resultado_hash);

    if (!resultado_hash) {
        printf("Hash no encontró la estación\n");
        return 1;
    }

    printf("Hash encontró ID: %" PRIu64 " en %f segundos\n",
           get_id_estacion(resultado_hash),
           tiempo_hash_busqueda);

    // EXTRAER COORDENADAS

    double lat = resultado_hash->latitud;
    double lon = resultado_hash->longitud;

    // B+ TREE

    printf("\n=== B+ TREE ===\n");

    BPlusTree *bpt = bpt_crear();

    EstructuraOps ops_bpt = {
        .estructura = bpt,
        .insertar = bpt_insertar_wrapper,
        .buscar_id = NULL,
        .buscar_coord = bpt_buscar_exacto_wrapper
    };

    double tiempo_bpt_insert =
        ejecutar_insercion(&ops_bpt, datos, cantidadFrecuencias);

    printf("Inserción B+ Tree: %f segundos\n", tiempo_bpt_insert);

    // BÚSQUEDA EXACTA (lat, lon)

    Estacion *resultado_bpt = NULL;

    double tiempo_bpt_busqueda =
        ejecutar_busqueda_coord(&ops_bpt, lat, lon, &resultado_bpt);

    printf("Tiempo búsqueda B+ Tree: %f segundos\n", tiempo_bpt_busqueda);

    // VALIDACIÓN

    imprimir_estacion("Resultado HASH", resultado_hash);
    imprimir_estacion("Resultado B+ TREE", resultado_bpt);

    if (resultado_bpt && resultado_hash) {

        if (get_id_estacion(resultado_bpt) == get_id_estacion(resultado_hash)) {
            printf("\n SON EL MISMO OBJETO\n");
        } else {
            printf("\n NO son el mismo objeto\n");
        }

        if (resultado_bpt == resultado_hash) {
            printf("\n MISMO PUNTERO EN MEMORIA\n");
        }

    } else {
        printf("\n No se pudo validar\n");
    }

    // BÚSQUEDA POR RANGO

    double lat_min = lat - 0.2;
    double lat_max = lat + 0.2;

    clock_t inicio = clock();

    bpt_buscar_rango(bpt, lat_min, lat_max);

    clock_t fin = clock();

    double tiempo_rango =
        (double)(fin - inicio) / CLOCKS_PER_SEC;

    printf("B+ Tree rango ejecutado en: %f segundos\n", tiempo_rango);

    // Liberar memoria

    liberar_estaciones(datos);
    ht_destruir(ht);
    bpt_destruir(bpt);

    return 0;
}