#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "reconocedor.h"


#define MAX_LEXEMA 15

void inicializarString (int largo, char* vector);
void cargarLexema (int maxLexema, char* lexema, char input[]);


int main (void) {

    int maxLexema = MAX_LEXEMA;
    char lexema[maxLexema+1];

    cargarLexema(maxLexema, lexema, "(");
    assert(AFD(maxLexema, lexema) == 1);

    cargarLexema(maxLexema, lexema, "-");
    assert(AFD(maxLexema, lexema) == 1);

    cargarLexema(maxLexema, lexema, "*");
    assert(AFD(maxLexema, lexema) == 1);

    cargarLexema(maxLexema, lexema, "()+");
    assert(AFD(maxLexema, lexema) == 3);

    cargarLexema(maxLexema, lexema, "(156");
    assert(AFD(maxLexema, lexema) == 3);

    cargarLexema(maxLexema, lexema, "0123");
    assert(AFD(maxLexema, lexema) == 2);

    cargarLexema(maxLexema, lexema, "110/");
    assert(AFD(maxLexema, lexema) == 3);

    cargarLexema(maxLexema, lexema, "hola");
    assert(AFD(maxLexema, lexema) == 3);

    cargarLexema(maxLexema, lexema, "12a");
    assert(AFD(maxLexema, lexema) == 3);

    printf("Todos los tests pasaron.\n");

    return 0;
}



void inicializarString (int largo, char vector[]) {
    for(int i = 0; i < largo; i++) {
        vector[i] = ' ';
    }
}

void cargarLexema (int maxLexema, char* lexema, char input[]) {
    int largo = strlen(input);
    inicializarString(maxLexema, lexema);
    strncpy(lexema, input, largo);
}