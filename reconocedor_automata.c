#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "reconocedor.h"

typedef enum {
    DESCONOCIDO = -1,
    OPERADOR,
    DIGITO                             
} tipoCaracter;

const char operadores[7] = {'+', '-', '*', '/', '(', ')'};


// PROTOTIPOS

int AFD(int maxLexema, char* lexema);
int esOperador(char caracter);
int tipoDeCaracter(char caracter);
int fTransicion(int estadoActual, char caracterLeido);


// AUTOMATA

int AFD(int maxLexema, char* lexema) {

    int estadoActual = 0;      //  {'(',' ', ' ', ' ', ..., ' '}
    int i = 0;
    char caracter;

    while((i < maxLexema) && (estadoActual != 3)) {
        caracter = lexema[i];
        if(caracter != ' ') {
            estadoActual = fTransicion(estadoActual, caracter);
        } else { break; }
        
        i++;
    }

    return estadoActual;
}


///// FUNCIÓN DE TRANSICIÓN /////


int esOperador(char caracter) {

    int cantidadOperadores = strlen(operadores);
    int i = 0;
    while(i < cantidadOperadores && (caracter != operadores[i])) {
        i++;
    }

    return i != cantidadOperadores;
}


int tipoDeCaracter(char caracter) {
    tipoCaracter tipo;

    if (isdigit(caracter)) {
        tipo = DIGITO;
    } else if (esOperador(caracter)) {
        tipo = OPERADOR;
    } else {tipo = DESCONOCIDO;}

    return tipo;
}



int fTransicion(int estadoActual, char caracterLeido) {
    
    int estadoSiguiente;

    int tipoCaracterLeido = tipoDeCaracter(caracterLeido);

    if (tipoCaracterLeido >= 0) {    
        static int tablaTransicion[3][2] = {          
            { 1,  2},           
            { 3,  3},
            { 3,  2}
        };
        
        estadoSiguiente = tablaTransicion[estadoActual][tipoCaracterLeido];
    } else {estadoSiguiente = 3;}
    
    return estadoSiguiente;   
}                           
