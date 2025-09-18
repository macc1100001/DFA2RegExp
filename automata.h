#ifndef AUTOMATA_HH
#define AUTOMATA_HH

#include "linkedlist.h"

typedef struct automata automata;
typedef struct estado estado;
typedef struct transicion transicion;

struct estado{
	char *nombre;
	bool esInicio, esAceptacion;
	lista* transiciones;
};

struct transicion{
	char* transicion;
	estado* estado;
};

struct automata{
	lista* estados;
	int n_estados;
};

automata* crear_automata(char*);
char* convert_to_regexp(automata*);
void agregar_estado(automata*, estado*, char*);
void eliminar_estado(automata*, estado*);
estado* crear_estado(char*, lista*, bool , bool);
transicion* crear_transicion(char*, estado*);
void free_transicion(void*);
void free_estado(void*);
void free_automata(automata*);
void mostrar_automata(automata*);
void preprocess_automata(automata*);

#endif
