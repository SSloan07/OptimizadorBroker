#include <stdlib.h>
#include "B+Tree.h"
#include "B+TreeNode.h"
#include <math.h>
#include <stdio.h>

#define EPS 0.00001

// Buscar hoja

static BPTNode* buscar_hoja(BPTNode *nodo, double clave) {
    while (!nodo->es_hoja) {
        int i = 0;

        while (i < nodo->num_claves && clave >= nodo->claves[i])
            i++;

        nodo = nodo->hijos[i];
    }

    return nodo;
}

// Crear árbol

BPlusTree* bpt_crear() {
    BPlusTree *tree = malloc(sizeof(BPlusTree));
    if (!tree) return NULL;

    tree->raiz = bptn_crear(true);
    return tree;
}

// Forward declarations

static void insertar_en_padre(BPlusTree *tree, BPTNode *izq, double clave, BPTNode *der);
static void dividir_interno(BPlusTree *tree, BPTNode *nodo);

// Dividir hoja

static void dividir_hoja(BPlusTree *tree, BPTNode *hoja) {

    BPTNode *nueva = bptn_crear(true);
    nueva->padre = hoja->padre;

    int split = (BPT_ORDER) / 2;

    nueva->num_claves = hoja->num_claves - split;

    for (int i = 0; i < nueva->num_claves; i++) {
        nueva->claves[i] = hoja->claves[split + i];
        nueva->datos[i] = hoja->datos[split + i];
    }

    hoja->num_claves = split;

    nueva->siguiente = hoja->siguiente;
    hoja->siguiente = nueva;

    double clave_promovida = nueva->claves[0];

    insertar_en_padre(tree, hoja, clave_promovida, nueva);
}

// Insertar en padre

static void insertar_en_padre(BPlusTree *tree, BPTNode *izq, double clave, BPTNode *der) {

    // caso raíz
    if (izq->padre == NULL) {
        BPTNode *nueva_raiz = bptn_crear(false);

        nueva_raiz->claves[0] = clave;
        nueva_raiz->hijos[0] = izq;
        nueva_raiz->hijos[1] = der;
        nueva_raiz->num_claves = 1;

        izq->padre = nueva_raiz;
        der->padre = nueva_raiz;

        tree->raiz = nueva_raiz;
        return;
    }

    BPTNode *padre = izq->padre;

    int i = padre->num_claves - 1;

    while (i >= 0 && padre->claves[i] > clave) {
        padre->claves[i + 1] = padre->claves[i];
        padre->hijos[i + 2] = padre->hijos[i + 1];
        i--;
    }

    padre->claves[i + 1] = clave;
    padre->hijos[i + 2] = der;
    padre->num_claves++;

    der->padre = padre;

    if (padre->num_claves >= BPT_ORDER - 1) {
        dividir_interno(tree, padre);
    }
}

// Dividir nodo interno

static void dividir_interno(BPlusTree *tree, BPTNode *nodo) {

    BPTNode *nuevo = bptn_crear(false);
    nuevo->padre = nodo->padre;

    int split = BPT_ORDER / 2;

    double clave_promovida = nodo->claves[split];

    int j = 0;

    for (int i = split + 1; i < nodo->num_claves; i++, j++) {
        nuevo->claves[j] = nodo->claves[i];
        nuevo->hijos[j] = nodo->hijos[i];
        if (nuevo->hijos[j])
            nuevo->hijos[j]->padre = nuevo;
    }

    nuevo->hijos[j] = nodo->hijos[nodo->num_claves];
    if (nuevo->hijos[j])
        nuevo->hijos[j]->padre = nuevo;

    nuevo->num_claves = nodo->num_claves - split - 1;
    nodo->num_claves = split;

    insertar_en_padre(tree, nodo, clave_promovida, nuevo);
}

// Insertar

void bpt_insertar(BPlusTree *tree, Estacion *e) {
    if (!tree || !e) return;

    BPTNode *hoja = buscar_hoja(tree->raiz, e->latitud);

    bptn_insertar_en_hoja(hoja, e);

    if (hoja->num_claves >= BPT_ORDER - 1) {
        dividir_hoja(tree, hoja);
    }
}


// Wrapper

void bpt_insertar_wrapper(void *estructura, Estacion *e) {
    bpt_insertar((BPlusTree*)estructura, e);
}

Estacion* bpt_buscar_exacto_wrapper(void *estructura, double lat, double lon) {
    return bpt_buscar_exacto((BPlusTree*)estructura, lat, lon);
}


// Búsqueda por rango 

void bpt_buscar_rango(BPlusTree *tree, double lat_min, double lat_max) {
    if (!tree) return;

    BPTNode *hoja = buscar_hoja(tree->raiz, lat_min);

    while (hoja) {
        for (int i = 0; i < hoja->num_claves; i++) {
            double lat = hoja->claves[i];

            if (lat > lat_max)
                return;

            if (lat >= lat_min) {
                Estacion *e = hoja->datos[i];
                volatile double temp = e->temperatura;
                (void)temp;
            }
        }

        hoja = hoja->siguiente;
    }
}

Estacion* bpt_buscar_exacto(BPlusTree *tree, double lat, double lon) {
    if (!tree) return NULL;

    BPTNode *hoja = buscar_hoja(tree->raiz, lat);

    while (hoja) {
        for (int i = 0; i < hoja->num_claves; i++) {

            double lat_actual = hoja->claves[i];
            Estacion *e = hoja->datos[i];

            // Si ya nos pasamos no existe
            if (lat_actual > lat + EPS)
                break;

            // Coincidencia por latitud
            if (fabs(lat_actual - lat) < EPS) {

                // Coincidencia por longitud
                if (fabs(e->longitud - lon) < EPS) {
                    printf("MATCH ENCONTRADO\n");
                    return e;
                }
            }
        }

        hoja = hoja->siguiente;
    }

    return NULL;
}

// Destructor

static void destruir_nodo(BPTNode *nodo) {
    if (!nodo) return;

    if (!nodo->es_hoja) {
        for (int i = 0; i <= nodo->num_claves; i++)
            destruir_nodo(nodo->hijos[i]);
    }

    free(nodo);
}

void bpt_destruir(BPlusTree *tree) {
    if (!tree) return;

    destruir_nodo(tree->raiz);
    free(tree);
}