#include "estacion_status.h"

// Esta es la funcion que me pasa esos numeros de error a texto (string)
const char* estacion_status_str(EstacionStatus status) {
    switch (status) {
        case ESTACION_OK:
            return "OK";

        case ESTACION_ERROR_NULL:
            return "Puntero nulo";

        case ESTACION_ERROR_RANGO_LATITUD:
            return "Latitud fuera de rango [-90, 90]";

        case ESTACION_ERROR_RANGO_LONGITUD:
            return "Longitud fuera de rango [-180, 180]";

        case ESTACION_ERROR_RANGO_TEMPERATURA:
            return "Temperatura fuera de rango [-100, 100] °C";

        case ESTACION_ERROR_FECHA_INVALIDA:
            return "Fecha inválida";

        case ESTACION_ERROR_ID_INVALIDO:
            return "ID de estación inválido";

        default:
            return "Error desconocido";
    }
}