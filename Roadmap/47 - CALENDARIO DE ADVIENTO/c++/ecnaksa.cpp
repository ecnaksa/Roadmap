/*
 * #47 - CALENDARIO DE ADVIENTO (C++)
 *
 * =========================== TEORÍA ===========================
 * Dibujo por terminal + estado. El calendario tiene 24 días en 6 columnas;
 * cada día es una celda 4x3 de asteriscos con el número en el centro. Al
 * descubrir un día, su centro se cubre de asteriscos.
 *
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <set>
#include <string>
#include <iomanip>
#include <sstream>

const int COLUMNAS = 6, DIAS = 24;

void render(const std::set<int>& descubiertos) {
    for (int inicio = 1; inicio <= DIAS; inicio += COLUMNAS) {
        for (int fila = 0; fila < 3; ++fila) {
            for (int d = inicio; d < inicio + COLUMNAS && d <= DIAS; ++d) {
                if (fila == 1) {
                    if (descubiertos.count(d)) std::cout << "****";
                    else { std::ostringstream ss; ss << "*" << std::setw(2) << std::setfill('0') << d << "*"; std::cout << ss.str(); }
                } else std::cout << "****";
                std::cout << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
}

std::string seleccionar(std::set<int>& descubiertos, int dia) {
    if (dia < 1 || dia > DIAS) return "[!] el dia debe estar entre 1 y 24";
    if (descubiertos.count(dia)) return "[!] el dia " + std::to_string(dia) + " ya estaba descubierto";
    descubiertos.insert(dia);
    return "Has abierto el dia " + std::to_string(dia) + "!";
}

int main() {
    std::set<int> descubiertos;
    std::cout << "=== Calendario de adviento (inicial) ===\n";
    render(descubiertos);
    for (int d : {1, 5, 24, 5}) std::cout << seleccionar(descubiertos, d) << "\n";
    std::cout << "\n=== Tras descubrir 1, 5 y 24 ===\n";
    render(descubiertos);
    return 0;
}
