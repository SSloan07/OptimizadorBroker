#include <time.h>
#include "EstructuraOps.h"
#include "../Estacion/Estacion.h"

void insertar_masivo(EstructuraOps *ops, Estacion *datos, int cantidad) {
    if (ops == NULL || ops->estructura == NULL || ops->insertar == NULL || datos == NULL)
        return;

    for (int i = 0; i < cantidad; i++) {
        ops->insertar(ops->estructura, &datos[i]);
    }
}

Estacion* buscar_id(EstructuraOps *ops, uint64_t id) {
    if (!ops || !ops->buscar_id) return NULL;   
    return ops->buscar_id(ops->estructura, id);
}

Estacion* buscar_coord(EstructuraOps *ops, double lat, double lon) {
    if (!ops || !ops->buscar_coord) return NULL;
    return ops->buscar_coord(ops->estructura, lat, lon);
}