/*
 * #05 - VALOR Y REFERENCIA (C++)
 *
 * =========================== TEORÍA ===========================
 * C++ distingue tres formas de pasar argumentos:
 *  - POR VALOR: se copia el argumento; los cambios no afectan al original.
 *  - POR REFERENCIA (tipo&): se trabaja sobre el original; los cambios sí
 *    afectan.
 *  - POR PUNTERO (tipo*): se pasa la dirección; se modifica con *.
 *
 * DIFICULTAD EXTRA: intercambio por valor (retornando) y por referencia.
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <utility>

void modificaPorValor(int x) { x += 100; std::cout << "  dentro (valor): " << x << "\n"; }
void modificaPorReferencia(int& x) { x += 100; }

// Intercambio por valor: retorna el par intercambiado
std::pair<int, int> intercambioPorValor(int a, int b) { return {b, a}; }
// Intercambio por referencia: modifica los originales
void intercambioPorReferencia(int& a, int& b) { std::swap(a, b); }

int main() {
    std::cout << "=== Por valor (no cambia el original) ===\n";
    int n = 5;
    modificaPorValor(n);
    std::cout << "  fuera: " << n << "\n";

    std::cout << "\n=== Por referencia (cambia el original) ===\n";
    modificaPorReferencia(n);
    std::cout << "  fuera: " << n << "\n";

    std::cout << "\n=== Reto extra: intercambio por valor ===\n";
    int x = 10, y = 20;
    auto [nx, ny] = intercambioPorValor(x, y);
    std::cout << "  originales x=" << x << " y=" << y << " (conservados)\n";
    std::cout << "  nuevas    x=" << nx << " y=" << ny << " (invertidas)\n";

    std::cout << "\n=== Reto extra: intercambio por referencia ===\n";
    int a = 1, b = 2;
    std::cout << "  antes  a=" << a << " b=" << b << "\n";
    intercambioPorReferencia(a, b);
    std::cout << "  despues a=" << a << " b=" << b << "\n";
    return 0;
}
