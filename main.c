#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "reconocedor.h"

#define MAX_LEXEMA 15
#define MAX_TOKEN 40


struct posicion {
    int linea;
    int columna;
};

struct posicion posicionActual = {1,0};

// PROTOTIPOS

void inicializarVector (int largo, char* vector);
int ignorarEntrada(char entrada);
void agregarAlLexema(char entrada, int maxLexema, char* lexema);
char* obtenerToken(int estado, char* token);
void imprimirEncabezado();
void imprimirToken(char* token, char* lexema);
void actualizarPosicion(struct posicion* posicionActual, char entrada);
void retrocederPosicion(struct posicion* posicionActual);

// MAIN

int main (void) {

    int maxLexema = MAX_LEXEMA;
    char lexema[maxLexema+1];

    int maxToken = MAX_TOKEN;
    char token[maxToken+1];
    
    int entrada, estado;
    
    entrada = getc(stdin);

    imprimirEncabezado();

    while(entrada != EOF) {
        
        if(!ignorarEntrada(entrada)) {

            inicializarVector(maxLexema, lexema);

            agregarAlLexema(entrada, maxLexema, lexema);

            estado = AFD(maxLexema, lexema);

            inicializarVector(maxToken, token);
            
            imprimirToken(obtenerToken(estado, token), lexema);
        
        } else { actualizarPosicion(&posicionActual, entrada); }

        entrada = getc(stdin);

    }

    return 0;
}


// FUNCIONES


int ignorarEntrada(char entrada) {
    return entrada == '\n' || entrada == '\r' || entrada == ' ';
}


void agregarAlLexema(char entrada, int maxLexema, char* lexema) {

    int i = 0;

    if(isdigit(entrada)) {
        
        do {
            actualizarPosicion(&posicionActual, entrada);
            lexema[i] = entrada;
            i++;
        } while (((entrada = getc(stdin)) != EOF) && (isdigit(entrada)) && (i < maxLexema));

        ungetc(entrada, stdin);
        retrocederPosicion(&posicionActual);

    } else {
        actualizarPosicion(&posicionActual, entrada);
        if(!ignorarEntrada(entrada)) { lexema[i] = entrada; }
    }

}

char* obtenerToken(int estado, char* token) {

    switch(estado) {
        case 1: 
            strcpy(token, "operador");
            break;
        case 2:
            strcpy(token, "numero");
            break;
        default:
            int linea = posicionActual.linea;
            int col = posicionActual.columna;
            sprintf(token, "desconocido [Ln %d, Col %d]", linea, col);
    }

    return token;
}


void imprimirEncabezado() {
    printf("\n\n%-15s | %-40s\n", "PALABRA", "TOKEN");
}


void imprimirToken(char* token, char* lexema) {
    printf("%-15s | %-40s\n", lexema, token);
}


void inicializarVector (int largo, char* vector) {
    for(int i = 0; i < largo; i++) {
        vector[i] = ' ';
    }
}


void actualizarPosicion(struct posicion* posicionActual, char entrada) {
    if (entrada == '\n') {
        (*posicionActual).linea ++;
        (*posicionActual).columna = 0;
    } else { (*posicionActual).columna ++; }
}

void retrocederPosicion(struct posicion* posicionActual) {
    (*posicionActual).columna --;
}