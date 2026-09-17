/*
 * #36 - EL SOMBRERO SELECCIONADOR (C++)
 *
 * =========================== TEORÍA ===========================
 * Sistema de puntuación: 10 preguntas con 4 respuestas; cada respuesta suma un
 * punto a una de las 4 casas (Frontend, Backend, Mobile, Data). Al final se
 * elige el máximo, resolviendo empates al azar.
 *
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

int main() {
    std::array<std::string, 4> casas = {"Frontend", "Backend", "Mobile", "Data"};
    std::mt19937 rng(1);

    // Respuestas simuladas (índice de casa 0-3 por cada una de las 10 preguntas)
    std::vector<int> respuestas;
    for (int i = 0; i < 10; ++i) respuestas.push_back(rng() % 4);

    std::array<int, 4> puntos = {0, 0, 0, 0};
    for (int r : respuestas) puntos[r]++;

    int maximo = *std::max_element(puntos.begin(), puntos.end());
    std::vector<int> empatadas;
    for (int i = 0; i < 4; ++i) if (puntos[i] == maximo) empatadas.push_back(i);
    int elegida = empatadas[rng() % empatadas.size()];

    std::cout << "=== El Sombrero Seleccionador (demo) ===\n";
    std::cout << "Respuestas: ";
    for (int r : respuestas) std::cout << r << " ";
    std::cout << "\n\nEl sombrero medita... " << (empatadas.size() > 1 ? "Dificil decision!" : "") << "\n";
    std::cout << "  ecnaksa, tu casa es: " << casas[elegida] << "\n  Puntuaciones: ";
    for (int i = 0; i < 4; ++i) std::cout << casas[i] << "=" << puntos[i] << " ";
    std::cout << std::endl;
    return 0;
}
