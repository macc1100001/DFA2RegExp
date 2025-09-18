#include "linkedlist.h"

lista* crear_lista(void (*free_datos)(void *datos)){
    lista* l = (lista*)malloc(sizeof(lista));
    if(l == NULL)
    	return NULL;
    l->tamano = 0;
    l->cabeza = NULL;
    l->free_datos = free_datos;
    return l;
}

bool estaVacia_lista(lista* l){
    return (l->cabeza == NULL && l->tamano == 0);
}

void agregar_alInicio(lista* l, nodo* n){
	n->sig = l->cabeza;
	n->ant = NULL;
	if(l->cabeza != NULL)
		l->cabeza->ant = n;
	l->cabeza = n;
	(l->tamano)++;
}

void agregar_alFinal(lista* l, nodo* n){
	nodo* tmp = l->cabeza;
	if(tmp == NULL)
		l->cabeza = n;
	while(tmp->sig != NULL)
		tmp = tmp->sig;
	tmp->sig = n;
	n->ant = tmp;
	(l->tamano)++;
}

void insertar_inicio(lista* l, void* dato){
	nodo* n = crear_nodo(dato);
	if(n == NULL) return;
	n->sig = l->cabeza;
	n->ant = NULL;
	if(l->cabeza != NULL)
		l->cabeza->ant = n;
	l->cabeza = n;
	(l->tamano)++;
}

void insertar_final(lista* l, void* dato){
	nodo* n = crear_nodo(dato);
	if(n == NULL) return;
	nodo* tmp = l->cabeza;
	if(tmp == NULL){
		l->cabeza = n;
		(l->tamano)++;
		return;
	}
	while(tmp->sig != NULL)
		tmp = tmp->sig;
	tmp->sig = n;
	n->ant = tmp;
	(l->tamano)++;
}

void remover_primero(lista* l){
	nodo* n = l->cabeza;
	if(l->cabeza != NULL){
		l->cabeza = l->cabeza->sig;
	}
	free_nodo(n, l->free_datos);
	(l->tamano)--;
}

void* buscar_lista(lista* l, void* k, int (*compara_memoria)(void* a, void* b)){
	nodo* n = l->cabeza;
	while(n != NULL && compara_memoria(n->datos, k) != 0)
		n = n->sig;
	return n->datos;		
}

void free_lista(lista* l){
	if(l == NULL)return;
	if(l->free_datos != NULL){
		while(!estaVacia_lista(l))
			remover_primero(l);
	}
	free(l);
	l = NULL;
}

