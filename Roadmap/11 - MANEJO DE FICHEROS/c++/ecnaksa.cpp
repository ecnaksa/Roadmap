/*
 * #11 - MANEJO DE FICHEROS (C++)
 *
 * =========================== TEORÍA ===========================
 * C++ maneja ficheros con <fstream>: std::ofstream (escritura),
 * std::ifstream (lectura) y std::fstream (ambos). Se cierran solos al destruir
 * el objeto (RAII). <filesystem> permite borrar y consultar ficheros.
 *
 * DIFICULTAD EXTRA: gestión de ventas en un .txt (nombre,cantidad,precio).
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdio>

struct Producto { std::string nombre; int cantidad; double precio; };

static std::vector<Producto> leer(const std::string& ruta) {
    std::vector<Producto> productos;
    std::ifstream f(ruta);
    std::string linea;
    while (std::getline(f, linea)) {
        if (linea.empty()) continue;
        std::stringstream ss(linea);
        std::string nombre, cant, prec;
        std::getline(ss, nombre, ',');
        std::getline(ss, cant, ',');
        std::getline(ss, prec, ',');
        productos.push_back({nombre, std::stoi(cant), std::stod(prec)});
    }
    return productos;
}

int main() {
    const std::string usuario = "ecnaksa.txt";
    std::cout << "=== Fichero basico ===\n";
    {
        std::ofstream f(usuario);
        f << "Nombre: ecnaksa\nEdad: 30\nLenguaje favorito: C++\n";
    }
    { std::ifstream f(usuario); std::cout << f.rdbuf(); }
    std::remove(usuario.c_str());
    std::cout << "Fichero borrado.\n";

    std::cout << "\n=== Reto extra: ventas (demo) ===\n";
    const std::string ventas = "ventas.txt";
    {
        std::ofstream f(ventas);
        f << "Teclado,3,25.0\nRaton,5,12.5\nTeclado,2,25.0\n";
    }
    auto productos = leer(ventas);
    double total = 0, totalTeclado = 0;
    for (auto& p : productos) {
        total += p.cantidad * p.precio;
        if (p.nombre == "Teclado") totalTeclado += p.cantidad * p.precio;
    }
    std::cout << "  Productos leidos: " << productos.size() << "\n";
    std::cout << "  Total 'Teclado': " << totalTeclado << " EUR\n";
    std::cout << "  Total ventas:    " << total << " EUR\n";
    std::remove(ventas.c_str());   // la opcion salir borra el fichero
    std::cout << "  Fichero borrado.\n";
    return 0;
}
