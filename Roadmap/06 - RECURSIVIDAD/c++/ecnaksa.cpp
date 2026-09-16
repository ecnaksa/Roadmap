/*
 * #06 - RECURSIVIDAD (C++)
 *
 * =========================== TEORÍA ===========================
 * La RECURSIVIDAD es una función que se llama a sí misma. Necesita un CASO
 * BASE que detenga las llamadas y un CASO RECURSIVO que se acerque a él. Cada
 * llamada usa espacio en la pila de llamadas.
 *
 * DIFICULTAD EXTRA: factorial y Fibonacci recursivos.
 * ============================ PRÁCTICA ========================
 */

#include <iostream>

void cuentaAtras(int n) {
    if (n < 0) return;          // caso base
    std::cout << n << " ";
    cuentaAtras(n - 1);         // caso recursivo
}

long long factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

long long fibonacci(int pos) {
    return (pos < 2) ? pos : fibonacci(pos - 1) + fibonacci(pos - 2);
}

int main() {
    std::cout << "=== Cuenta atras 100 -> 0 ===\n";
    cuentaAtras(100);
    std::cout << "\n\n=== Reto extra: factorial ===\n";
    for (int n : {0, 1, 5, 10}) std::cout << "  " << n << "! = " << factorial(n) << "\n";

    std::cout << "\n=== Reto extra: Fibonacci ===\n  ";
    for (int i = 0; i < 15; ++i) std::cout << fibonacci(i) << " ";
    std::cout << "\n  fibonacci(10) = " << fibonacci(10) << std::endl;
    return 0;
}
