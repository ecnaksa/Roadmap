/*
 * #01 - OPERADORES Y ESTRUCTURAS DE CONTROL (C++)
 *
 * =========================== TEORÍA ===========================
 * OPERADORES en C++: aritméticos (+ - * / %), comparación (== != < > <= >=),
 * lógicos (&& || !), asignación (= += -= ...), bits (& | ^ ~ << >>) e
 * incremento/decremento (++ --). No hay operador de potencia: se usa std::pow.
 * ESTRUCTURAS DE CONTROL: condicionales (if/else, switch), bucles (for, while,
 * do-while) y manejo de excepciones (try/catch).
 *
 * DIFICULTAD EXTRA: números 10..55 pares, que no sean 16 ni múltiplos de 3.
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <cmath>
#include <stdexcept>

int main() {
    std::cout << "=== Aritméticos ===\n";
    std::cout << "7+2=" << 7 + 2 << "  7/2=" << 7 / 2 << "  7%2=" << 7 % 2
              << "  pow(7,2)=" << std::pow(7, 2) << "\n";

    std::cout << "\n=== Comparación y lógicos ===\n";
    std::cout << std::boolalpha << "(7>2 && 2>1) = " << (7 > 2 && 2 > 1) << "\n";

    std::cout << "\n=== Bits ===\n";
    std::cout << "5&3=" << (5 & 3) << "  5|3=" << (5 | 3) << "  5<<1=" << (5 << 1) << "\n";

    std::cout << "\n=== Condicional (if/else) ===\n";
    int nota = 7;
    if (nota >= 9) std::cout << "Sobresaliente\n";
    else if (nota >= 5) std::cout << "Aprobado\n";
    else std::cout << "Suspenso\n";

    std::cout << "\n=== Bucles ===\n";
    for (int i = 0; i < 3; ++i) std::cout << "for " << i << "  ";
    std::cout << "\n";
    int n = 3;
    while (n-- > 0) std::cout << "while " << n << "  ";
    std::cout << "\n";

    std::cout << "\n=== Excepciones ===\n";
    try {
        throw std::runtime_error("error de ejemplo");
    } catch (const std::exception& e) {
        std::cout << "Capturado: " << e.what() << "\n";
    }

    std::cout << "\n=== Reto extra: 10..55 pares, sin 16 ni múltiplos de 3 ===\n";
    for (int i = 10; i <= 55; ++i)
        if (i % 2 == 0 && i != 16 && i % 3 != 0)
            std::cout << i << " ";
    std::cout << std::endl;
    return 0;
}
