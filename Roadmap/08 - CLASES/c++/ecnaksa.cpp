/*
 * #08 - CLASES (C++)
 *
 * =========================== TEORÍA ===========================
 * Una CLASE encapsula datos (atributos) y comportamiento (métodos). En C++:
 *  - El constructor inicializa el objeto.
 *  - 'public'/'private' controlan la visibilidad.
 *  - Los métodos pueden acceder a los atributos con 'this'.
 *
 * DIFICULTAD EXTRA: clases Pila y Cola.
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <vector>
#include <string>

class Persona {
    std::string nombre;
    int edad;
public:
    Persona(std::string n, int e) : nombre(std::move(n)), edad(e) {}
    void setEdad(int e) { edad = e; }
    void presentarse() const {
        std::cout << "  Me llamo " << nombre << " y tengo " << edad << " anios.\n";
    }
};

class Pila {
    std::vector<int> items;
public:
    void apilar(int x) { items.push_back(x); }
    int desapilar() { int v = items.back(); items.pop_back(); return v; }
    size_t tamanio() const { return items.size(); }
    void imprimir() const { std::cout << "  Pila: "; for (int x : items) std::cout << x << " "; std::cout << "\n"; }
};

class Cola {
    std::vector<int> items;
public:
    void encolar(int x) { items.push_back(x); }
    int desencolar() { int v = items.front(); items.erase(items.begin()); return v; }
    size_t tamanio() const { return items.size(); }
    void imprimir() const { std::cout << "  Cola: "; for (int x : items) std::cout << x << " "; std::cout << "\n"; }
};

int main() {
    std::cout << "=== Clase Persona ===\n";
    Persona p("ecnaksa", 30);
    p.presentarse();
    p.setEdad(31);
    p.presentarse();

    std::cout << "\n=== Reto extra: Pila ===\n";
    Pila pila;
    for (int x : {1, 2, 3}) pila.apilar(x);
    pila.imprimir();
    std::cout << "  desapilar -> " << pila.desapilar() << " (tam=" << pila.tamanio() << ")\n";

    std::cout << "\n=== Reto extra: Cola ===\n";
    Cola cola;
    for (int x : {1, 2, 3}) cola.encolar(x);
    cola.imprimir();
    std::cout << "  desencolar -> " << cola.desencolar() << " (tam=" << cola.tamanio() << ")\n";
    return 0;
}
