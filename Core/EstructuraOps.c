#include <time.h>
#include "EstructuraOps.h"

void insertar_masivo(EstructuraOps *ops, Estacion *datos, int cantidad) {
    if (ops == NULL || ops->estructura == NULL || ops->insertar == NULL || datos == NULL)
        return;

    for (int i = 0; i < cantidad; i++) {
        ops->insertar(ops->estructura, &datos[i]);
    }
}

Estacion* buscar(EstructuraOps *ops, uint64_t id) {
    if (!ops || !ops->buscar) return NULL;
    return ops->buscar(ops->estructura, id);
}