/*
 * #24 - DECORADORES (C)
 *
 * =========================== TEORÍA ===========================
 * C no tiene decoradores ni closures. El patrón se emula con PUNTEROS A
 * FUNCIÓN: una función "envoltura" recibe el puntero de la función original,
 * añade comportamiento (medir tiempo, contar llamadas) y la invoca. El estado
 * (p. ej. el contador) se guarda en una variable static.
 *
 * DIFICULTAD EXTRA: contar cuántas veces se llama a una función.
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>
#include <time.h>

typedef long (*FuncInt)(int);

/* Decorador cronómetro: envuelve una llamada midiendo el tiempo */
long cronometro(FuncInt f, int arg, const char *nombre) {
    clock_t ini = clock();
    long r = f(arg);
    double s = (double)(clock() - ini) / CLOCKS_PER_SEC;
    printf("  '%s' tardo %.6fs\n", nombre, s);
    return r;
}

long suma_lenta(int n) {
    long s = 0;
    for (int i = 0; i < n; ++i) s += i;
    return s;
}

/* Decorador contador: mantiene el estado en una variable static */
const char *saludar_contado(const char *nombre) {
    static int llamadas = 0;
    static char buffer[64];
    ++llamadas;
    printf("  llamada #%d\n", llamadas);
    snprintf(buffer, sizeof buffer, "Hola %s", nombre);
    return buffer;
}

int main(void) {
    printf("=== Decorador cronometro ===\n");
    printf("  resultado = %ld\n", cronometro(suma_lenta, 1000000, "suma_lenta"));

    printf("\n=== Reto extra: contador de llamadas ===\n");
    saludar_contado("Ana");
    saludar_contado("Luis");
    saludar_contado("Marta");
    return 0;
}
