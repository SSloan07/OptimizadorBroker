#include <stdlib.h>
#include "HashTable.h"

// Función hash

static unsigned int hash_func(uint64_t id) {
    return id % HASH_SIZE;
}

// Crear tabla

HashTable* ht_crear() {
    HashTable *ht = malloc(sizeof *ht);
    if (!ht) return NULL;

    ht->tabla = calloc(HASH_SIZE, sizeof(NodoHash*));
    if (!ht->tabla) {
        free(ht);
        return NULL;
    }

    return ht;
}

// Insertar

void ht_insertar(HashTable *ht, Estacion *e) {
    if (!ht || !e) return;

    uint64_t id = e->id_estacion;
    unsigned int idx = hash_func(id);

    NodoHash *nuevo = malloc(sizeof *nuevo);
    if (!nuevo) return;

    nuevo->data = e;
    nuevo->siguiente = ht->tabla[idx];
    ht->tabla[idx] = nuevo;
}

// Buscar

Estacion* ht_buscar(HashTable *ht, uint64_t id_estacion) {
    if (!ht) return NULL;

    unsigned int idx = hash_func(id_estacion);
    NodoHash *actual = ht->tabla[idx];

    while (actual) {
        if (get_id_estacion(actual->data) == id_estacion)
            return actual->data;

        actual = actual->siguiente;
    }

    return NULL;
}

// Wrapper

void ht_insertar_wrapper(void *estructura, Estacion *e) {
    ht_insertar((HashTable*)estructura, e);
}

Estacion* ht_buscar_wrapper(void *estructura, uint64_t id) {
    return ht_buscar((HashTable*)estructura, id);
}

// Destruir

void ht_destruir(HashTable *ht) {
    if (!ht) return;

    for (int i = 0; i < HASH_SIZE; i++) {
        NodoHash *actual = ht->tabla[i];

        while (actual) {
            NodoHash *temp = actual;
            actual = actual->siguiente;
            free(temp);
        }
    }

    free(ht->tabla);
    free(ht);
}

