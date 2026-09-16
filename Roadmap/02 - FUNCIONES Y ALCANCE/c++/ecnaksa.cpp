/*
 * #02 - FUNCIONES Y ALCANCE (C++)
 *
 * =========================== TEORÍA ===========================
 * Una FUNCIÓN agrupa código reutilizable. En C++ se declara con su tipo de
 * retorno, nombre y parámetros. Admite: valores por defecto, sobrecarga
 * (mismo nombre, distintos parámetros) y lambdas (funciones anónimas).
 * ALCANCE: variables LOCALES (dentro de un bloque) y GLOBALES (fuera de toda
 * función). Las lambdas pueden "capturar" variables del ámbito que las rodea.
 *
 * DIFICULTAD EXTRA: FizzBuzz 1..100 con dos textos; devuelve cuántas veces se
 * imprimió el número.
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <string>

int contadorGlobal = 0;  // variable GLOBAL

void sinRetorno() { std::cout << "  funcion sin retorno\n"; }

int suma(int a, int b) { return a + b; }

int potencia(int base, int exp = 2) {  // parámetro por defecto
    int r = 1;
    for (int i = 0; i < exp; ++i) r *= base;
    return r;
}

int fizzbuzz(const std::string& t3, const std::string& t5) {
    int vecesNumero = 0;
    for (int n = 1; n <= 100; ++n) {
        if (n % 15 == 0) std::cout << t3 << t5 << "\n";
        else if (n % 3 == 0) std::cout << t3 << "\n";
        else if (n % 5 == 0) std::cout << t5 << "\n";
        else { std::cout << n << "\n"; ++vecesNumero; }
    }
    return vecesNumero;
}

int main() {
    std::cout << "=== Funciones ===\n";
    sinRetorno();
    std::cout << "  suma(3,4)=" << suma(3, 4) << "\n";
    std::cout << "  potencia(3)=" << potencia(3) << "  potencia(3,3)=" << potencia(3, 3) << "\n";

    std::cout << "\n=== Alcance y lambda ===\n";
    contadorGlobal += 1;
    int local = 10;
    auto duplicar = [local](int x) { return x * 2 + 0 * local; };  // captura por valor
    std::cout << "  global=" << contadorGlobal << "  lambda(5)=" << duplicar(5) << "\n";

    std::cout << "\n=== Reto extra (FizzBuzz) ===\n";
    int veces = fizzbuzz("fizz", "buzz");
    std::cout << "El numero se imprimio " << veces << " veces.\n";
    return 0;
}
