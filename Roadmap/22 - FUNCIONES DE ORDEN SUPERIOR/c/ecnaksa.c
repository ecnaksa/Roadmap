/*
 * #22 - FUNCIONES DE ORDEN SUPERIOR (C)
 *
 * =========================== TEORÍA ===========================
 * C consigue funciones de orden superior mediante PUNTEROS A FUNCIÓN: una
 * función puede recibir otra como argumento (p. ej. qsort recibe el
 * comparador). Podemos escribir nuestros propios map/filter/reduce genéricos
 * que reciban la operación como puntero a función.
 *
 * DIFICULTAD EXTRA: análisis de estudiantes.
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* map genérico: aplica f a cada elemento */
void map(const int *in, int *out, int n, int (*f)(int)) {
    for (int i = 0; i < n; ++i) out[i] = f(in[i]);
}
int doblar(int x) { return x * 2; }

/* reduce genérico */
int reduce(const int *in, int n, int (*f)(int, int), int inicial) {
    int acc = inicial;
    for (int i = 0; i < n; ++i) acc = f(acc, in[i]);
    return acc;
}
int sumar(int a, int b) { return a + b; }

typedef struct { char nombre[16]; int anio; double notas[3]; } Estudiante;

double promedio(const Estudiante *e) {
    return (e->notas[0] + e->notas[1] + e->notas[2]) / 3.0;
}
int cmp_joven(const void *a, const void *b) {
    return ((const Estudiante *)b)->anio - ((const Estudiante *)a)->anio;
}

int main(void) {
    printf("=== HOF basicas (punteros a funcion) ===\n");
    int nums[] = {1, 2, 3, 4, 5, 6}, out[6];
    map(nums, out, 6, doblar);
    printf("  map x2: "); for (int i = 0; i < 6; ++i) printf("%d ", out[i]); printf("\n");
    printf("  reduce suma: %d\n", reduce(nums, 6, sumar, 0));

    printf("\n=== Reto extra: estudiantes ===\n");
    Estudiante est[] = {
        {"Ana", 2001, {8.5, 9.0, 7.5}},
        {"Luis", 1999, {9.2, 9.5, 9.8}},
        {"Marta", 2003, {6.0, 7.0, 8.0}},
        {"Iker", 2000, {9.0, 9.1, 9.3}},
    };
    int n = 4;
    printf("  Promedios: ");
    for (int i = 0; i < n; ++i) printf("%s=%.2f ", est[i].nombre, promedio(&est[i]));
    printf("\n  Mejores (>=9): ");
    for (int i = 0; i < n; ++i) if (promedio(&est[i]) >= 9) printf("%s ", est[i].nombre);

    qsort(est, n, sizeof(Estudiante), cmp_joven);
    printf("\n  Del mas joven: ");
    for (int i = 0; i < n; ++i) printf("%s ", est[i].nombre);

    double maxNota = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < 3; ++j) if (est[i].notas[j] > maxNota) maxNota = est[i].notas[j];
    printf("\n  Mayor calificacion: %.1f\n", maxNota);
    return 0;
}
