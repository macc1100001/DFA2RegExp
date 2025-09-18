#include "nodo.h"

nodo* crear_nodo(void* datos){
    nodo* n = (nodo*)malloc(sizeof(nodo));
    if(n != NULL){
        n->ant = n->sig = NULL;
        n->datos = datos;
    }
    return n;
}

void free_nodo(nodo* n, void (*free_datos)(void*)){
    if(n == NULL) return;
    if(free_datos != NULL)
        (*free_datos)(n->datos);
    free(n);
	n = NULL;
}

