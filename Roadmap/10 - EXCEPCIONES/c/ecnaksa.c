/*
 * #10 - EXCEPCIONES (C)
 *
 * =========================== TEORÍA ===========================
 * C NO tiene excepciones. Los errores se gestionan con:
 *  1. Códigos de retorno / errno (lo más habitual).
 *  2. setjmp/longjmp (<setjmp.h>): permite un salto no local que EMULA el
 *     comportamiento de throw/catch. longjmp "salta" de vuelta al punto
 *     marcado con setjmp, transportando un código de error.
 * Aquí usamos setjmp/longjmp para simular 3 tipos de excepción.
 *
 * DIFICULTAD EXTRA: función que "lanza" 3 tipos de error (uno personalizado).
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <setjmp.h>

/* "Tipos de excepción" */
enum { EX_OK = 0, EX_TIPO = 1, EX_VALOR = 2, EX_EDAD_INVALIDA = 3 };

static jmp_buf entorno;

static int procesar_edad(const char *valor) {
    /* comprobar que todos son dígitos (si no -> "ValueError") */
    if (valor[0] == '\0') longjmp(entorno, EX_VALOR);
    for (int i = 0; valor[i]; ++i)
        if (!isdigit((unsigned char)valor[i])) longjmp(entorno, EX_VALOR);
    int edad = atoi(valor);
    if (edad < 0 || edad > 150) longjmp(entorno, EX_EDAD_INVALIDA); /* excepcion propia */
    return edad;
}

static void evaluar(const char *valor) {
    printf("Entrada '%s': ", valor);
    int codigo = setjmp(entorno);   /* punto de retorno (como 'try') */
    if (codigo == EX_OK) {
        int edad = procesar_edad(valor);
        printf("OK edad = %d", edad);
    } else if (codigo == EX_VALOR) {
        printf("[ValueError] no es un numero valido");
    } else if (codigo == EX_EDAD_INVALIDA) {
        printf("[EdadInvalida] edad fuera de rango");
    } else {
        printf("[Error] tipo desconocido");
    }
    printf(" -> finalizado\n");
}

int main(void) {
    printf("=== Captura basica (division / indice) ===\n");
    int arr[3] = {1, 2, 3};
    int idx = 10;
    if (idx < 0 || idx >= 3) printf("  Indice fuera de rango evitado (%d)\n", idx);
    else printf("%d\n", arr[idx]);

    printf("\n=== Reto extra (setjmp/longjmp) ===\n");
    const char *entradas[] = {"25", "abc", "200", "40"};
    for (int i = 0; i < 4; ++i) evaluar(entradas[i]);
    return 0;
}
