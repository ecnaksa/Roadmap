/*
 * #17 - ITERACIONES (C++)
 *
 * =========================== TEORÍA ===========================
 * C++ ofrece varios mecanismos para iterar: for clásico, while, do-while,
 * for basado en rango (range-for), iteradores explícitos, algoritmos como
 * std::for_each y, desde C++20, std::ranges.
 *
 * DIFICULTAD EXTRA: el mayor número de mecanismos posible (aquí, varios).
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    std::cout << "=== 3 mecanismos (1..10) ===\n";
    std::cout << "  for:   "; for (int i = 1; i <= 10; ++i) std::cout << i << " "; std::cout << "\n";
    std::cout << "  while: "; { int i = 1; while (i <= 10) std::cout << i++ << " "; } std::cout << "\n";
    std::cout << "  do:    "; { int i = 1; do { std::cout << i << " "; } while (++i <= 10); } std::cout << "\n";

    std::cout << "\n=== Reto extra: mas mecanismos ===\n";
    std::vector<int> v(10);
    std::iota(v.begin(), v.end(), 1);  // rellena 1..10

    std::cout << "  4) range-for: "; for (int x : v) std::cout << x << " "; std::cout << "\n";
    std::cout << "  5) iteradores: ";
    for (auto it = v.begin(); it != v.end(); ++it) std::cout << *it << " ";
    std::cout << "\n";
    std::cout << "  6) reverse-it: ";
    for (auto it = v.rbegin(); it != v.rend(); ++it) std::cout << *it << " ";
    std::cout << "\n";
    std::cout << "  7) for_each:  ";
    std::for_each(v.begin(), v.end(), [](int x) { std::cout << x << " "; });
    std::cout << "\n";
    std::cout << "  8) index[]:   ";
    for (size_t i = 0; i < v.size(); ++i) std::cout << v[i] << " ";
    std::cout << "\n";
    return 0;
}
