/*
 * #34 - ÁRBOL GENEALÓGICO (LA CASA DEL DRAGÓN) (C++)
 *
 * =========================== TEORÍA ===========================
 * Modelado de relaciones (árbol/grafo). Cada persona se referencia por su id.
 * Reglas: una sola pareja (simétrica) y un hijo con máximo dos progenitores.
 * Se recorre el árbol de forma recursiva para imprimirlo.
 *
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <set>

struct Persona {
    std::string id, nombre, pareja;
    std::vector<std::string> hijos;
};

class Arbol {
    std::map<std::string, Persona> personas;
    std::map<std::string, int> progenitores;
public:
    void anadir(const std::string& id, const std::string& nombre) { personas[id] = {id, nombre, "", {}}; }

    std::string emparejar(const std::string& a, const std::string& b) {
        if (!personas.count(a) || !personas.count(b)) return "[!] persona inexistente";
        if (!personas[a].pareja.empty() || !personas[b].pareja.empty()) return "[!] ya tienen pareja";
        personas[a].pareja = b; personas[b].pareja = a;
        return personas[a].nombre + " y " + personas[b].nombre + " son pareja";
    }

    std::string anadirHijo(const std::string& padre, const std::string& hijo) {
        if (!personas.count(padre) || !personas.count(hijo)) return "[!] inexistente";
        if (progenitores[hijo] >= 2) return "[!] " + personas[hijo].nombre + " ya tiene 2 progenitores";
        personas[padre].hijos.push_back(hijo);
        progenitores[hijo]++;
        return personas[hijo].nombre + " es hijo/a de " + personas[padre].nombre;
    }

    void imprimir(const std::string& id, int nivel = 0, std::set<std::string> vis = {}) {
        if (vis.count(id) || !personas.count(id)) return;
        vis.insert(id);
        const auto& p = personas[id];
        std::cout << std::string(nivel * 4, ' ') << "* " << p.nombre;
        if (!p.pareja.empty()) std::cout << " & " << personas[p.pareja].nombre;
        std::cout << "\n";
        for (auto& h : p.hijos) imprimir(h, nivel + 1, vis);
    }
};

int main() {
    Arbol arbol;
    const char* datos[][2] = {{"1", "Viserys I"}, {"2", "Alicent"}, {"3", "Rhaenyra"},
        {"4", "Daemon"}, {"5", "Aegon II"}, {"6", "Jacaerys"}};
    for (auto& d : datos) arbol.anadir(d[0], d[1]);

    std::cout << "  " << arbol.emparejar("1", "2") << "\n";
    std::cout << "  " << arbol.anadirHijo("1", "3") << "\n";
    std::cout << "  " << arbol.anadirHijo("2", "5") << "\n";
    std::cout << "  " << arbol.anadirHijo("3", "6") << "\n";
    std::cout << "  " << arbol.emparejar("3", "1") << "\n";  // invalido

    std::cout << "\n=== Arbol genealogico ===\n";
    arbol.imprimir("1");
    return 0;
}
