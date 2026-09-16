/*
 * #03 - ESTRUCTURAS DE DATOS (C++)
 *
 * =========================== TEORÍA ===========================
 * La STL de C++ ofrece contenedores:
 *  - std::vector : array dinámico (inserción/borrado, acceso por índice).
 *  - std::map    : pares clave-valor ordenados por clave.
 *  - std::set    : conjunto ordenado sin duplicados.
 *  - std::tuple / std::pair : agrupaciones heterogéneas.
 * Ofrecen operaciones de inserción, borrado, actualización y ordenación
 * (std::sort).
 *
 * DIFICULTAD EXTRA: agenda de contactos (demo con validación de teléfono).
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <string>

static bool telefonoValido(const std::string& t) {
    if (t.empty() || t.size() > 11) return false;
    return std::all_of(t.begin(), t.end(), ::isdigit);
}

int main() {
    std::cout << "=== vector ===\n";
    std::vector<int> v = {3, 1, 2};
    v.push_back(4);                 // inserción al final
    v.insert(v.begin(), 0);         // inserción al principio
    v[1] = 10;                       // actualización
    v.erase(v.begin() + 2);          // borrado por posición
    std::sort(v.begin(), v.end());   // ordenación
    std::cout << "  ";
    for (int x : v) std::cout << x << " ";
    std::cout << "\n";

    std::cout << "\n=== map ===\n";
    std::map<std::string, int> agenda = {{"Ana", 111}, {"Luis", 222}};
    agenda["Marta"] = 333;           // inserción
    agenda["Ana"] = 999;             // actualización
    agenda.erase("Luis");            // borrado
    for (auto& [k, val] : agenda) std::cout << "  " << k << " -> " << val << "\n";

    std::cout << "\n=== set ===\n";
    std::set<int> s = {1, 2, 2, 3};
    s.insert(4);
    s.erase(1);
    std::cout << "  ";
    for (int x : s) std::cout << x << " ";
    std::cout << "\n";

    std::cout << "\n=== Reto extra: agenda (demo) ===\n";
    std::map<std::string, std::string> contactos;
    std::vector<std::pair<std::string, std::string>> entradas = {
        {"Ana", "600111222"}, {"Luis", "abc"}, {"Marta", "999"}};
    for (auto& [nombre, tel] : entradas) {
        if (telefonoValido(tel)) { contactos[nombre] = tel; std::cout << "  insertado " << nombre << ": " << tel << "\n"; }
        else std::cout << "  rechazado " << nombre << " ('" << tel << "' no valido)\n";
    }
    contactos["Ana"] = "600999888";  // actualizar
    contactos.erase("Marta");        // eliminar
    std::cout << "  final: ";
    for (auto& [k, val] : contactos) std::cout << k << "=" << val << " ";
    std::cout << std::endl;
    return 0;
}
