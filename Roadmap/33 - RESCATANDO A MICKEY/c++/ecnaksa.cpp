/*
 * #33 - RESCATANDO A MICKEY (C++)
 *
 * =========================== TEORÍA ===========================
 * Reto de MATRICES: un laberinto 6x6 representado como matriz. Se controla la
 * posición de Mickey con coordenadas (fila, col) y se validan los movimientos
 * (límites y obstáculos) antes de aplicarlos.
 * Símbolos: '.' vacío, '#' obstáculo, 'M' Mickey, 'E' salida.
 *
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <vector>
#include <string>
#include <map>

int main() {
    int plano[6][6] = {
        {0, 0, 0, 1, 0, 0},
        {1, 1, 0, 1, 0, 1},
        {0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 1, 0},
        {1, 1, 0, 1, 0, 0},
    };
    int fila = 0, col = 0;
    const int salidaF = 5, salidaC = 5;

    std::map<std::string, std::pair<int, int>> mov = {
        {"arriba", {-1, 0}}, {"abajo", {1, 0}}, {"izquierda", {0, -1}}, {"derecha", {0, 1}}};

    auto dibujar = [&]() {
        for (int f = 0; f < 6; ++f) {
            std::cout << "  ";
            for (int c = 0; c < 6; ++c) {
                if (f == fila && c == col) std::cout << 'M';
                else if (f == salidaF && c == salidaC) std::cout << 'E';
                else std::cout << (plano[f][c] ? '#' : '.');
            }
            std::cout << "\n";
        }
    };

    std::vector<std::string> ruta = {"derecha", "derecha", "abajo", "abajo", "derecha",
        "derecha", "derecha", "arriba", "abajo", "abajo", "abajo"};

    std::cout << "=== Laberinto inicial ('M' Mickey, 'E' salida) ===\n";
    dibujar();
    for (auto& d : ruta) {
        auto [df, dc] = mov[d];
        int nf = fila + df, nc = col + dc;
        std::cout << "\n> " << d << ": ";
        if (nf < 0 || nf >= 6 || nc < 0 || nc >= 6) std::cout << "fuera de limites!\n";
        else if (plano[nf][nc] == 1) std::cout << "hay un obstaculo!\n";
        else { fila = nf; col = nc; std::cout << "ok\n"; }
        dibujar();
        if (fila == salidaF && col == salidaC) { std::cout << "\nMickey ha escapado!\n"; return 0; }
    }
    return 0;
}
