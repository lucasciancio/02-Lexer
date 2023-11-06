#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "reconocedor.h"

#define MAX_LEXEMA 15


struct posicion {
    int linea;
    int columna;
};

struct posicion posicionActual = {0,0};

// PROTOTIPOS

void inicializarVector (int largo, char vector[]);
int ignorarEntrada(char entrada);
void agregarAlLexema(char entrada, int maxLexema, char lexema[]);
void obtenerToken(int estado, char token[]);
void imprimirEncabezado();
void imprimirToken(char token[], char lexema[]);
void actualizarPosicion(struct posicion* posicionActual, char entrada);
void retrocederPosicion(struct posicion* posicionActual, char entrada);


// MAIN

int main (void) {

    int maxLexema = MAX_LEXEMA;
    char lexema[maxLexema+1];

    // vector = {'0', '1', '2', '3', '4', '\0'}

    inicializarVector(maxLexema, lexema);

    int entrada, estado;
    char token[11+1];

    imprimirEncabezado();

    while((entrada = getc(stdin)) != EOF) {

        if(!ignorarEntrada(entrada)) {

            inicializarVector(maxLexema, lexema);

            agregarAlLexema(entrada, maxLexema, lexema);

            estado = AFD(maxLexema, lexema);

            inicializarVector(11, token);
            obtenerToken(estado, token);
            imprimirToken(token, lexema);
        
        } else { actualizarPosicion(&posicionActual, entrada); }

    }

    return 0;
}


// FUNCIONES


int ignorarEntrada(char entrada) {
    return entrada == '\n' || entrada == '\r' || entrada == ' ';
}

// (1+1) *2\n3/4\n2\n3


void agregarAlLexema(char entrada, int maxLexema, char lexema[]) {

    int i = 0;

    if(isdigit(entrada)) {
        
        do {
            actualizarPosicion(&posicionActual, entrada);
            lexema[i] = entrada;
            i++;
        } while ((entrada = getc(stdin) != EOF) && (isdigit(entrada)) && (i < maxLexema));

        ungetc(entrada, stdin);
        retrocederPosicion(&posicionActual, entrada);

    } else {
        if(!ignorarEntrada(entrada)) { lexema[i] = entrada; }
    }

}

void obtenerToken(int estado, char token[]) {

    switch(estado) {
        case 1: 
            strcpy(token, "operador");
            break;
        case 2:
            strcpy(token, "numero");
            break;
        default: strcpy(token, "desconocido");
    }
}


void imprimirEncabezado() {
    printf("%-15s | %-30s\n", "PALABRA", "TOKEN");
}


void imprimirToken(char token[], char lexema[]) {
    char posicion[15+1];
    int linea;
    int columna;

    if(strcmp(token, "desconocido")) {
        inicializarVector(15, posicion);
        sprintf(posicion, " [Ln %d Col %d ]", posicionActual.linea, posicionActual.columna);
        strcat(token, posicion);
    }
    printf("%-15s | %-30s\n", lexema, token);
}


void inicializarVector (int largo, char vector[]) {
    for(int i = 0; i < largo; i++) {
        vector[i] = ' ';
    }
}


void actualizarPosicion(struct posicion* posicionActual, char entrada) {
    if (entrada == '\n') {
        (*posicionActual).linea++;
        (*posicionActual).columna = 0;
    } else { (*posicionActual).columna ++; }
}

void retrocederPosicion(struct posicion* posicionActual, char entrada) {
    (*posicionActual).columna--;
}