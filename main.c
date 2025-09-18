#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"automata.h"

#define MAXCHAR 1024

int main(int argc, char** argv){

	char buffer[MAXCHAR] = {0};
	FILE *fp = fopen(argv[1], "r");
	if(!fp){
		perror("fopen");
		printf("Error al leer el archivo\n");
		return EXIT_FAILURE;
	}
	fread(buffer, sizeof(char), MAXCHAR, fp);
	fclose(fp);

	automata* a = crear_automata(buffer);
	char* regexp = convert_to_regexp(a);
	printf("regexp: %s\n", regexp);
	mostrar_automata(a);
	preprocess_automata(a);
	mostrar_automata(a);
	free_automata(a);

	return EXIT_SUCCESS;
}
