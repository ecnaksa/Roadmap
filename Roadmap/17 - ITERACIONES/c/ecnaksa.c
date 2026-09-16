/*
 * #17 - ITERACIONES (C)
 *
 * =========================== TEORÍA ===========================
 * C ofrece tres bucles: for, while y do-while, además de la posibilidad de
 * simular bucles con goto (desaconsejado) o recursión. Sobre arrays se itera
 * por índice o con un puntero que avanza.
 *
 * DIFICULTAD EXTRA: el mayor número de mecanismos posible.
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>

int main(void) {
    printf("=== 3 mecanismos (1..10) ===\n");
    printf("  for:   "); for (int i = 1; i <= 10; ++i) printf("%d ", i); printf("\n");
    printf("  while: "); { int i = 1; while (i <= 10) printf("%d ", i++); } printf("\n");
    printf("  do:    "); { int i = 1; do { printf("%d ", i); } while (++i <= 10); } printf("\n");

    printf("\n=== Reto extra: mas mecanismos ===\n");
    int v[10]; for (int i = 0; i < 10; ++i) v[i] = i + 1;

    printf("  4) indice:   "); for (int i = 0; i < 10; ++i) printf("%d ", v[i]); printf("\n");
    printf("  5) puntero:  "); for (int *p = v; p < v + 10; ++p) printf("%d ", *p); printf("\n");
    printf("  6) reverso:  "); for (int i = 9; i >= 0; --i) printf("%d ", v[i]); printf("\n");
    printf("  7) for-2en2: "); for (int i = 1; i <= 10; i += 2) printf("%d ", i); printf("\n");

    printf("  8) goto:     ");
    int i = 1;
inicio:
    if (i <= 10) { printf("%d ", i); ++i; goto inicio; }
    printf("\n");
    return 0;
}
