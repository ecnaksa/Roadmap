/*
 * #02 - FUNCIONES Y ALCANCE (C)
 *
 * =========================== TEORÍA ===========================
 * Una FUNCIÓN en C se declara con su tipo de retorno, nombre y parámetros.
 * C NO admite sobrecarga ni parámetros por defecto (a diferencia de C++).
 * Las funciones deben declararse (prototipo) antes de usarse.
 * ALCANCE: variables LOCALES (dentro de una función) y GLOBALES (fuera de
 * toda función). 'static' a nivel de función limita la visibilidad al fichero.
 *
 * DIFICULTAD EXTRA: FizzBuzz 1..100; devuelve cuántas veces se imprimió el
 * número.
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>

int contadorGlobal = 0;  /* variable GLOBAL */

void sinRetorno(void) { printf("  funcion sin retorno\n"); }

int suma(int a, int b) { return a + b; }

int potencia(int base, int exp) {
    int r = 1;
    for (int i = 0; i < exp; ++i) r *= base;
    return r;
}

int fizzbuzz(const char *t3, const char *t5) {
    int vecesNumero = 0;
    for (int n = 1; n <= 100; ++n) {
        if (n % 15 == 0) printf("%s%s\n", t3, t5);
        else if (n % 3 == 0) printf("%s\n", t3);
        else if (n % 5 == 0) printf("%s\n", t5);
        else { printf("%d\n", n); ++vecesNumero; }
    }
    return vecesNumero;
}

int main(void) {
    printf("=== Funciones ===\n");
    sinRetorno();
    printf("  suma(3,4)=%d\n", suma(3, 4));
    printf("  potencia(3,2)=%d  potencia(3,3)=%d\n", potencia(3, 2), potencia(3, 3));

    printf("\n=== Alcance ===\n");
    contadorGlobal += 1;
    int local = 10;
    printf("  global=%d  local=%d\n", contadorGlobal, local);

    printf("\n=== Reto extra (FizzBuzz) ===\n");
    int veces = fizzbuzz("fizz", "buzz");
    printf("El numero se imprimio %d veces.\n", veces);
    return 0;
}
