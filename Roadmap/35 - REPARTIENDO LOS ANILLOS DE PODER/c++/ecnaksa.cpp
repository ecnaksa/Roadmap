/*
 * #35 - REPARTIENDO LOS ANILLOS DE PODER (C++)
 *
 * =========================== TEORÍA ===========================
 * Búsqueda combinatoria con restricciones: reservamos 1 anillo para Sauron y
 * buscamos elfos (impar), enanos (primo) y hombres (par) que sumen el resto.
 *
 * ============================ PRÁCTICA ========================
 */

#include <iostream>

bool esPrimo(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; ++i) if (n % i == 0) return false;
    return true;
}

void repartir(int total) {
    std::cout << "\n=== Repartir " << total << " anillos ===\n";
    int restante = total - 1;  // Sauron
    for (int elfos = 1; elfos <= restante; elfos += 2)          // impar
        for (int enanos = 2; enanos <= restante - elfos; ++enanos) {
            if (!esPrimo(enanos)) continue;
            int hombres = restante - elfos - enanos;
            if (hombres >= 0 && hombres % 2 == 0) {              // par
                std::cout << "  Elfos:   " << elfos << "\n  Enanos:  " << enanos
                          << "\n  Hombres: " << hombres << "\n  Sauron:  1\n";
                return;
            }
        }
    std::cout << "  No existe un reparto valido.\n";
}

int main() {
    for (int t : {20, 15, 3, 1}) repartir(t);
    return 0;
}
