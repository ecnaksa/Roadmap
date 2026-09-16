/*
 * #05 - VALOR Y REFERENCIA (C)
 *
 * =========================== TEORÍA ===========================
 * C SIEMPRE pasa los argumentos POR VALOR (se copian). Para simular el "paso
 * por referencia" se pasan PUNTEROS: la dirección se copia, pero a través de
 * ella se puede modificar el valor original con el operador de
 * desreferencia (*).
 *
 * DIFICULTAD EXTRA: intercambio por valor (retorno vía struct) y por
 * "referencia" (punteros).
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>

void modificaPorValor(int x) { x += 100; printf("  dentro (valor): %d\n", x); }
void modificaPorPuntero(int *x) { *x += 100; }

typedef struct { int a, b; } Par;
Par intercambioPorValor(int a, int b) { Par p = {b, a}; return p; }
void intercambioPorPuntero(int *a, int *b) { int t = *a; *a = *b; *b = t; }

int main(void) {
    printf("=== Por valor (no cambia el original) ===\n");
    int n = 5;
    modificaPorValor(n);
    printf("  fuera: %d\n", n);

    printf("\n=== Por puntero (cambia el original) ===\n");
    modificaPorPuntero(&n);
    printf("  fuera: %d\n", n);

    printf("\n=== Reto extra: intercambio por valor ===\n");
    int x = 10, y = 20;
    Par r = intercambioPorValor(x, y);
    printf("  originales x=%d y=%d (conservados)\n", x, y);
    printf("  nuevas    x=%d y=%d (invertidas)\n", r.a, r.b);

    printf("\n=== Reto extra: intercambio por puntero ===\n");
    int a = 1, b = 2;
    printf("  antes  a=%d b=%d\n", a, b);
    intercambioPorPuntero(&a, &b);
    printf("  despues a=%d b=%d\n", a, b);
    return 0;
}
