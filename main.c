#include <stdio.h>
#include <time.h>
#include "Estacion/Estacion.h"

int main() {
    Estacion *e = crear_estacion(1, 10.5, -75.3, 25.0, time(NULL));

    if (e == NULL) {
        printf("Error creando estación\n");
        return 1;
    }

    printf("ID: %lu\n", get_id_estacion(e));

    destruir_estacion(e);
    return 0;
}
