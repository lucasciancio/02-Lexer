#include <stdio.h>
#include <string.h>
#include <ctype.h>
//#include "reconocedor.h"

typedef enum {
    DESCONOCIDO = -1,
    OPERADOR,
    DIGITO                             
} tipoCaracter;

const char operadores[7] = {'+', '-', '*', '/', '(', ')'};


// PROTOTIPOS

int AFD(int maxLexema, char lexema[]);
int esOperador(char caracter);
int tipoDeCaracter(char caracter);
int fTransicion(int estadoActual, char caracterLeido);

void inicializarVector (int largo, char vector[]);
void mostrarTransicion(int estadoActual, char caracterLeido);
void cargarLexema (int max_lexema, char lexema[], char* input);

// MAIN PRUEBAS

int main(void) {

    // PRUEBAS AFD

    int max_lexema = 15;
    char lexema[max_lexema+1];

    printf("ENTRADA | SALIDA\n"); 
    
    cargarLexema(max_lexema, lexema, "(");
    printf("%-7s | %-6d\n", "(", AFD(max_lexema, lexema));
    
    cargarLexema(max_lexema, lexema, "012");
    printf("%-7s | %-6d\n", "012", AFD(max_lexema, lexema));

    cargarLexema(max_lexema, lexema, "hola");
    printf("%-7s | %-6d\n", "hola", AFD(max_lexema, lexema));

    cargarLexema(max_lexema, lexema, "1+1");
    printf("%-7s | %-6d\n", "1+1", AFD(max_lexema, lexema));


    // PRUEBAS FUNCIÓN DE TRANSICIÓN

    // mostrarTransicion(0, '(');   // 1
    // mostrarTransicion(1, '2');   // 3 
    // mostrarTransicion(1, ')');   // 3
    
    // mostrarTransicion(0, '2');   // 2
    // mostrarTransicion(2, ')');   // 3
    // mostrarTransicion(2, '2');   // 2




    return 0;
}



// AUTOMATA

int AFD(int maxLexema, char lexema[]) {

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
            { 3,  3},              // probar de definir la tabla como global
            { 3,  2}
        };
        
        estadoSiguiente = tablaTransicion[estadoActual][tipoCaracterLeido];
    } else {estadoSiguiente = 3;}
    
    return estadoSiguiente;   
}                           

// PARA PROBAR

void mostrarTransicion(int estadoActual, char caracterLeido) {
    int estadoSiguiente = fTransicion(estadoActual, caracterLeido);
    printf("%d -> %c -> %d\n", estadoActual, caracterLeido, estadoSiguiente);
}

void inicializarVector (int largo, char vector[]) {
    for(int i = 0; i < largo; i++) {
        vector[i] = ' ';
    }
}

void cargarLexema (int max_lexema, char lexema[], char* input) {
    int largo = strlen(input);
    inicializarVector(max_lexema, lexema);
    strncpy(lexema, input, largo);
}