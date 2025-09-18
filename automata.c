/*
 * formato del archivo de automatas.
 *
 * primera linea: una lista de todos los estados del automata, separado por comas.
 * segunda linea: el estado de aceptacion, debe ser parte de la lista de estados de la primera linea.
 * tercera linea: una lista de los estados de aceptacion, deben ser parte de la lista de estados de la primera linea.
 *
 * las lineas siguientes son las transiciones de cada estado en el siguiente formato: q0, t, q1.
 * que representa la transicion "t" para llegar del estado "q0" hacia el estado "q1" (q0 -> t -> q1).
 * */

#include<stdio.h>

#include"automata.h"

int compara_estados(void* a, void* b){
	estado* a_e = (estado*)a;
	char* b_e = (char*)b;
	return strcmp(a_e->nombre, b_e);
}

lista* parse_format(char* fmt, int* n_estados){
	char* tmp = fmt;
	int line_num = 1;
	*n_estados = 0;
	lista* estados = crear_lista(free_estado);
	if(estados == NULL)
		return NULL;
	estado* e;
	int count = 1;
	estado* e_trans1;
	estado* e_trans2;
	char* trans_str;
	while(tmp != NULL){
		char* token_line = strsep(&tmp, "\n");
		if(token_line == NULL || strcmp(token_line, "") == 0)
			break;
		while(token_line != NULL){
			char* token_space = strsep(&token_line, " ");
			if(token_space == NULL)
				break;
			switch(line_num){
				case 1:
					insertar_final(estados, crear_estado(token_space, NULL, false, false));	
					(*n_estados)++;
					break;
				case 2:
					e = buscar_lista(estados, token_space, compara_estados);
					e->esInicio = true;
					break;
				case 3: 
					e = buscar_lista(estados, token_space, compara_estados);
					e->esAceptacion = true;
					break;
				default:
					switch(count){
						case 1:
							e_trans1 = buscar_lista(estados, token_space, compara_estados);
							++count;
							break;
						case 2:
							trans_str = token_space;
							++count;
							break;
						case 3:
							e_trans2 = buscar_lista(estados, token_space, compara_estados);
							insertar_final(e_trans1->transiciones, crear_transicion(trans_str, e_trans2));
							++count;
						default:
							count = 1;
					}
			}
		}
		++line_num;
	}
	return estados;
}

void preprocess_automata(automata* a){
	// Paso uno: crear un nuevo estado inicial que conecte
	// con el anterior utilizando la palabra vacia como
	// transicion.
	// Paso dos: crear un nuevo unico estado final que reciba conexiones
	// de todos los estados de aceptacion anteriores 
	estado* e_inicio = crear_estado("qstart", NULL, true, false);
	estado* e_aceptacion = crear_estado("qaccept", NULL, false, true);
	nodo* tmp = a->estados->cabeza;
	while(tmp != NULL){
		estado* e_tmp = tmp->datos;
		if(e_tmp->esInicio){
			//printf("El estado de inicio es: %s\n",e_tmp->nombre);
			e_tmp->esInicio = false;
			insertar_inicio(e_inicio->transiciones, crear_transicion("", e_tmp));
			break;
		}
		if(e_tmp->esAceptacion){
			//printf("%s, ", e_tmp->nombre);
			e_tmp->esAceptacion = false;
			insertar_final(e_tmp->transiciones, crear_transicion("", e_aceptacion));
		}
		tmp = tmp->sig;
	}
	insertar_inicio(a->estados, e_inicio);
	insertar_final(a->estados, e_aceptacion);
	a->n_estados += 2; 

}

char* convert_to_regexp(automata* a){
	if(a->n_estados == 2){
		estado* e = ((estado*)a->estados->cabeza->datos);
		transicion* t = ((transicion*)e->transiciones->cabeza->datos);
		return t->transicion;
	}
	
	return NULL;
}

void mostrar_automata(automata* a){
	nodo* inicio = a->estados->cabeza;
	printf("automata:\n");
	for(int i = 0; i < a->n_estados; ++i){
		estado* e = (estado*)inicio->datos;
		if(e == NULL) break;
		printf("estado %d: %s, ", i+1, e->nombre);
		printf("inicio: %s, ", (e->esInicio) ? "true" : "false");
		printf("aceptacion: %s\n", (e->esAceptacion) ? "true" : "false");
		printf("transiciones: ");
		nodo* ini_trans = e->transiciones->cabeza;
		for(int i = 0; i < e->transiciones->tamano; ++i){
			transicion* t = (transicion*)ini_trans->datos;
			if(t == NULL) break;
			printf("%s->%s, ", t->transicion, t->estado->nombre);
			ini_trans = ini_trans->sig;
		}
		printf("\n");
		inicio = inicio->sig;
	}
}

automata* crear_automata(char* fmt){
	automata* a = (automata*)malloc(sizeof(automata));
	if(a == NULL)return NULL;
	a->n_estados = 0;
	a->estados = parse_format(fmt, &a->n_estados);
	return a;
}

estado* crear_estado(char* nombre, lista* transiciones, bool esInicio, bool esAceptacion){
	estado* e = (estado*)malloc(sizeof(estado));
	if(e == NULL) return NULL;
	e->nombre = strdup(nombre);
	if(transiciones != NULL)
		e->transiciones = transiciones;
	else
		e->transiciones = crear_lista(free_transicion);
	e->esInicio = esInicio;
	e->esAceptacion = esAceptacion;
	return e;
}

transicion* crear_transicion(char* str_transicion, estado* e){
	transicion* t = malloc(sizeof(transicion));
	if(t == NULL) return NULL;
	t->transicion = strdup(str_transicion);
	t->estado = e;
	return t;
}

void free_estado(void* e){
	estado* tmp = (estado*)e;
	if(tmp == NULL) return;
	if(tmp->nombre != NULL){
		free(tmp->nombre);
		tmp->nombre = NULL;
	}
	if(tmp->transiciones != NULL)
		free_lista(tmp->transiciones);
	free(tmp);
	tmp = NULL;
}

void free_transicion(void* t){
	transicion* tmp = (transicion*)t;
	if(tmp == NULL) return;
	free(tmp->transicion);
	free(tmp);
	tmp = NULL;
}

void free_automata(automata* a){
	if(a == NULL)return;
	//TODO: free estados y transiciones.
	free_lista(a->estados);
	free(a);
	a = NULL;
}

//void agregar_estado(automata*, estado*);
//void eliminar_estado(automata*, estado*);

