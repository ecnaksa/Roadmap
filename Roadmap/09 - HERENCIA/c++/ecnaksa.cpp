/*
 * #09 - HERENCIA (C++)
 *
 * =========================== TEORÍA ===========================
 * La HERENCIA permite que una clase derive de otra reutilizando su código.
 * Con métodos VIRTUALES se logra POLIMORFISMO: la llamada se resuelve según el
 * tipo real del objeto en tiempo de ejecución.
 *
 * DIFICULTAD EXTRA: jerarquía de empresa (Empleado -> Programador, etc.).
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Animal {
protected:
    std::string nombre;
public:
    Animal(std::string n) : nombre(std::move(n)) {}
    virtual ~Animal() = default;
    virtual std::string hacerSonido() const { return "..."; }
    void describir() const { std::cout << "  " << nombre << " dice: " << hacerSonido() << "\n"; }
};

class Perro : public Animal {
public:
    using Animal::Animal;
    std::string hacerSonido() const override { return "Guau!"; }
};

class Gato : public Animal {
public:
    using Animal::Animal;
    std::string hacerSonido() const override { return "Miau!"; }
};

// --- Reto extra: jerarquía de empresa ---
class Empleado {
protected:
    int id; std::string nombre;
public:
    Empleado(int i, std::string n) : id(i), nombre(std::move(n)) {}
    virtual ~Empleado() = default;
    virtual std::string rol() const { return "Empleado"; }
    void info() const { std::cout << "  [" << id << "] " << nombre << " - " << rol() << "\n"; }
};

class Programador : public Empleado {
    std::string lenguaje;
public:
    Programador(int i, std::string n, std::string l) : Empleado(i, std::move(n)), lenguaje(std::move(l)) {}
    std::string rol() const override { return "Programador (" + lenguaje + ")"; }
};

class GerenteProyectos : public Empleado {
public:
    using Empleado::Empleado;
    std::string rol() const override { return "Gerente de Proyectos"; }
};

int main() {
    std::cout << "=== Herencia: Animal ===\n";
    std::vector<std::unique_ptr<Animal>> animales;
    animales.push_back(std::make_unique<Perro>("Toby"));
    animales.push_back(std::make_unique<Gato>("Michi"));
    for (auto& a : animales) a->describir();

    std::cout << "\n=== Reto extra: empresa ===\n";
    std::vector<std::unique_ptr<Empleado>> emp;
    emp.push_back(std::make_unique<Programador>(3, "Ana", "C++"));
    emp.push_back(std::make_unique<GerenteProyectos>(2, "Marta"));
    for (auto& e : emp) e->info();
    return 0;
}
