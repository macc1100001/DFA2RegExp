#ifndef MY_LINKED_LIST_H
#define MY_LINKED_LIST_H

#include <stdbool.h>
#include "nodo.h"

typedef struct lista lista;

struct lista{
    size_t tamano;
    nodo* cabeza;
    void (*free_datos)(void*);
};

lista* crear_lista(void (*free_datos)(void*));
bool estaVacia_lista(lista*);
void* buscar_lista(lista*, void*, int (*compara_memoria)(void*, void*));
void free_lista(lista*);
void insertar_final(lista*, void*);
void insertar_inicio(lista*, void*);
void remover_final(lista*);
void remover_primero(lista*);
void remover_nodo(lista*, nodo*);

#endif

