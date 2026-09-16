/*
 * #00 - SINTAXIS, VARIABLES, TIPOS DE DATOS Y HOLA MUNDO
 * Web oficial del lenguaje: https://en.cppreference.com/w/c
 *
 * =========================== TEORÍA ===========================
 * C es un lenguaje compilado, de tipado ESTÁTICO y de bajo nivel. Es la base
 * de muchos otros lenguajes. No tiene un tipo booleano nativo hasta C99
 * (<stdbool.h>) ni un tipo string: las cadenas son arrays de char terminados
 * en '\0'.
 *  - Variables: se declaran con su tipo -> int edad = 30;
 *  - Constantes: con la palabra clave 'const' o con #define.
 *  - Tipos primitivos: int, long, float, double, char (y void).
 *
 * ============================ PRÁCTICA ========================
 * Compilar: gcc -std=c11 ecnaksa.c -o ecnaksa && ./ecnaksa
 */

#include <stdio.h>
#include <stdbool.h>  // tipo bool (C99+)

// Comentario de una sola línea
/* Comentario
   de varias líneas */

#define LENGUAJE "C"  // constante con el preprocesador

int main(void) {
    /* Variables (tipado estático) */
    char nombre[] = "ecnaksa";  /* cadena = array de char */
    int edad = 30;               /* entero */
    double altura = 1.80;        /* coma flotante */
    char inicial = 'E';         /* carácter */
    bool programador = true;     /* booleano (stdbool.h) */
    const double PI = 3.14159;   /* constante */

    printf("=== Variables y tipos ===\n");
    printf("nombre (char[]): %s\n", nombre);
    printf("edad (int):      %d\n", edad);
    printf("altura (double): %.2f\n", altura);
    printf("inicial (char):  %c\n", inicial);
    printf("programador (bool): %s\n", programador ? "true" : "false");
    printf("PI (const):      %.5f\n\n", PI);

    printf("¡Hola, %s!\n", LENGUAJE);
    return 0;
}
