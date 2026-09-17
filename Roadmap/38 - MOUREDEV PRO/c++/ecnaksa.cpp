/*
 * #38 - MOUREDEV PRO (sorteo desde CSV) (C++)
 *
 * =========================== TEORÍA ===========================
 * Lectura de CSV con <fstream>/<sstream>: se salta la cabecera, se filtran los
 * registros "activo" y se eligen 3 ganadores distintos con <random> (barajado
 * y toma de los 3 primeros).
 *
 * NOTA: el .csv de datos no se sube; se genera al vuelo y se borra.
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <cstdio>

struct Registro { std::string id, email; };

int main() {
    const std::string ruta = "suscriptores.csv";
    // Crear CSV de demo
    {
        std::ofstream f(ruta);
        f << "id,email,status\n";
        for (int i = 1; i <= 10; ++i)
            f << i << ",user" << i << "@test.com," << (i % 3 ? "activo" : "inactivo") << "\n";
    }

    // Leer y filtrar activos
    std::vector<Registro> activos;
    std::ifstream f(ruta);
    std::string linea;
    std::getline(f, linea);  // cabecera
    while (std::getline(f, linea)) {
        std::stringstream ss(linea);
        std::string id, email, status;
        std::getline(ss, id, ','); std::getline(ss, email, ','); std::getline(ss, status, ',');
        if (status == "activo") activos.push_back({id, email});
    }

    std::cout << "=== Sorteo mouredev pro ===\n";
    const char* premios[] = {"Suscripcion", "Descuento", "Libro"};
    if (activos.size() < 3) { std::cout << "  No hay suficientes activos.\n"; }
    else {
        std::mt19937 rng(38);
        std::shuffle(activos.begin(), activos.end(), rng);
        for (int i = 0; i < 3; ++i)
            std::cout << "  " << premios[i] << " -> id " << activos[i].id << "  " << activos[i].email << "\n";
    }
    std::remove(ruta.c_str());
    std::cout << "  Fichero de datos borrado.\n";
    return 0;
}
