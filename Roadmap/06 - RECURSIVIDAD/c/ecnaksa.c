/*
 * #06 - RECURSIVIDAD (C)
 *
 * =========================== TEORÍA ===========================
 * La RECURSIVIDAD es una función que se llama a sí misma. Necesita un CASO
 * BASE que detenga las llamadas y un CASO RECURSIVO. En C conviene vigilar la
 * profundidad para no desbordar la pila.
 *
 * DIFICULTAD EXTRA: factorial y Fibonacci recursivos.
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>

void cuenta_atras(int n) {
    if (n < 0) return;          /* caso base */
    printf("%d ", n);
    cuenta_atras(n - 1);        /* caso recursivo */
}

long long factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

long long fibonacci(int pos) {
    return (pos < 2) ? pos : fibonacci(pos - 1) + fibonacci(pos - 2);
}

int main(void) {
    printf("=== Cuenta atras 100 -> 0 ===\n");
    cuenta_atras(100);
    printf("\n\n=== Reto extra: factorial ===\n");
    int nums[] = {0, 1, 5, 10};
    for (int i = 0; i < 4; ++i) printf("  %d! = %lld\n", nums[i], factorial(nums[i]));

    printf("\n=== Reto extra: Fibonacci ===\n  ");
    for (int i = 0; i < 15; ++i) printf("%lld ", fibonacci(i));
    printf("\n  fibonacci(10) = %lld\n", fibonacci(10));
    return 0;
}
