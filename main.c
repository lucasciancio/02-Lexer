#include <stdio.h>
#include <string.h>
#include <ctype.h>
//#include "reconocedor.h"

#define MAX_LEXEMA 15



// PROTOTIPOS

void inicializarVector (int largo, char vector[]);



// MAIN

int main (void) {

    int maxLexema = MAX_LEXEMA;
    char lexema[maxLexema+1];

    inicializarVector(maxLexema, lexema);

    int entrada;

    while(entrada = getc(stdin)) {

    }

    return 0;
}


// FUNCIONES

void inicializarVector (int largo, char vector[]) {
    for(int i = 0; i < largo; i++) {
        vector[i] = ' ';
    }
}