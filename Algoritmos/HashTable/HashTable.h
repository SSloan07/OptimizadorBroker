#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdint.h>
#include "../../Estacion/Estacion.h"

#define HASH_SIZE 10000019  

typedef struct NodoHash {
    Estacion *data;
    struct NodoHash *siguiente;
} NodoHash;

typedef struct {
    NodoHash **tabla;
} HashTable;

// Funciones principales

HashTable* ht_crear();
void ht_insertar(HashTable *ht, Estacion *e);
Estacion* ht_buscar(HashTable *ht, uint64_t id_estacion);
void ht_destruir(HashTable *ht);

// Wrapper (para interfaz genérica)

void ht_insertar_wrapper(void *estructura, Estacion *e);
Estacion* ht_buscar_wrapper(void *estructura, uint64_t id); 

#endif