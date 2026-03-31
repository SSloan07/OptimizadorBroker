#include <stdio.h>
#include <inttypes.h>

#include "BenchmarkHash.h"
#include "HashTable.h"
#include "EstructuraOps.h"
#include "MotorConsultas.h"

Estacion* benchmark_hash(Estacion *datos, int n) {


    HashTable *ht = ht_crear();

    EstructuraOps ops = {
        .estructura = ht,
        .insertar = ht_insertar_wrapper,
        .buscar_id = ht_buscar_wrapper,
        .buscar_coord = NULL
    };

    double t_insert = ejecutar_insercion(&ops, datos, n);
    printf("Inserción Hash: %f segundos\n", t_insert);

    uint64_t id = 1000;
    Estacion *resultado = NULL;

    double t_search = ejecutar_busqueda_id(&ops, id, &resultado);

    printf("Hash encontró ID: %" PRIu64 " en %f segundos\n",
           get_id_estacion(resultado), t_search);

    ht_destruir(ht);

    return resultado; 
}