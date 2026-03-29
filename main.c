#include <stdio.h>
#include <time.h>
#include <inttypes.h>
#include "Estacion/Estacion.h"
#include "Algoritmos/HashTable/HashTable.h"
#include "Core/EstructuraOps.h"
#include "Core/GeneradorDatos.h"

int main() {

    int cantidadFrecuencias = 10000000;
    int cantidadEstaciones = 100;

    // Crear estructura

    HashTable *ht = ht_crear();
    if (!ht) {
        printf("Error creando la tabla hash\n");
        return 1;
    }

    // Configurar interfaz

    EstructuraOps ops = {
        .estructura = ht,
        .insertar = ht_insertar_wrapper,
        .buscar = ht_buscar_wrapper
    };

    // Generar datos 

    Estacion *datos = generar_estaciones(cantidadFrecuencias, cantidadEstaciones); 

    if (!datos) {
        printf("Error generando datos\n");
        return 1;
    }

    // Inserción masiva

    clock_t inicio = clock();

    insertar_masivo(&ops, datos, cantidadFrecuencias);

    clock_t fin = clock();

    double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;

    printf("Insertadas %d estaciones en %f segundos\n", cantidadFrecuencias, tiempo);

    // Prueba de búsqueda
    
    uint64_t id_busqueda = 100000;
    inicio = clock();
    Estacion *resultado = buscar(&ops, id_busqueda);
    fin = clock();
    tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    if (resultado) {
        printf("Elemento con ID: %" PRIu64 " encontrado en: %f segundos\n",get_id_estacion(resultado),tiempo);
    } else {
        printf("No se encontró la estación\n");
    }
    
    // Liberar memoria

    liberar_estaciones(datos);  
    ht_destruir(ht);

    return 0;
}