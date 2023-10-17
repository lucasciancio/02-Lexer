#include <stdio.h>
#include <string.h>
#include <ctype.h>

///////////////////////////////
typedef enum {
    DESCONOCIDO = -1,
    OPERADOR,
    DIGITO                               // TODO ESTO DEBERÍA IR EN EL ARCHIVO PRINCIPAL CREO
} simbolo;

const char operadores[7] = {'+', '-', '*', '/', '(', ')'};
/////////////////////////////////


//////////////// FUNCIÓN DE TRANSICIÓN

int esOperador(char caracter) {

    int cantidadOperadores = strlen(operadores);
    int i = 0;
    while(i < cantidadOperadores && (caracter != operadores[i])) {
        i++;
    }

    return i != cantidadOperadores;
}


int tipoDeCaracter(char caracter) {
    simbolo tipo;

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
            {-1, -1},        
            {-1,  2}
        };
        
        estadoSiguiente = tablaTransicion[estadoActual][tipoCaracterLeido];
    } else {estadoSiguiente = -1;}
    
    return estadoSiguiente;   
}                           


void mostrarTransicion(int estadoActual, char caracterLeido) {
    int estadoSiguiente = fTransicion(estadoActual, caracterLeido);
    printf("%d -> %c -> %d\n", estadoActual, caracterLeido, estadoSiguiente);
}



int main (void) {
    //                           ESTADO DE LLEGADA ESPERADO
    mostrarTransicion(0, '(');   // 1
    mostrarTransicion(1, '2');   // -1 
    mostrarTransicion(1, ')');   // -1
    
    mostrarTransicion(0, '2');   // 2
    mostrarTransicion(2, ')');   // -1
    mostrarTransicion(0, '2');   // 2


    return 0;
}