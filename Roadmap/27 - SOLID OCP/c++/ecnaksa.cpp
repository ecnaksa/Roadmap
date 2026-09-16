/*
 * #27 - SOLID: OCP (C++)
 *
 * =========================== TEORÍA ===========================
 * OCP: "abierto a la extensión, cerrado a la modificación". Con una clase base
 * abstracta Operacion y un registro en la Calculadora, añadir una nueva
 * operación (potencia) es CREAR una clase nueva, sin tocar el código existente.
 *
 * DIFICULTAD EXTRA: calculadora extensible con una quinta operación.
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <cmath>

struct Operacion {
    virtual ~Operacion() = default;
    virtual double calcular(double a, double b) const = 0;
};

struct Suma : Operacion { double calcular(double a, double b) const override { return a + b; } };
struct Resta : Operacion { double calcular(double a, double b) const override { return a - b; } };
struct Mult : Operacion { double calcular(double a, double b) const override { return a * b; } };
struct Div : Operacion { double calcular(double a, double b) const override { return b ? a / b : 0; } };
// Extensión SIN modificar Calculadora:
struct Potencia : Operacion { double calcular(double a, double b) const override { return std::pow(a, b); } };

class Calculadora {
    std::map<std::string, std::unique_ptr<Operacion>> ops;
public:
    void registrar(const std::string& n, std::unique_ptr<Operacion> op) { ops[n] = std::move(op); }
    double operar(const std::string& n, double a, double b) const {
        auto it = ops.find(n);
        return it == ops.end() ? 0 : it->second->calcular(a, b);
    }
};

int main() {
    std::cout << "=== OCP: calculadora extensible ===\n";
    Calculadora calc;
    calc.registrar("suma", std::make_unique<Suma>());
    calc.registrar("resta", std::make_unique<Resta>());
    calc.registrar("mult", std::make_unique<Mult>());
    calc.registrar("div", std::make_unique<Div>());
    std::cout << "  suma(4,2)=" << calc.operar("suma", 4, 2) << "\n";
    std::cout << "  div(4,2)=" << calc.operar("div", 4, 2) << "\n";

    calc.registrar("pot", std::make_unique<Potencia>());   // añadida sin tocar nada
    std::cout << "  pot(4,2)=" << calc.operar("pot", 4, 2) << "  <- extension OCP\n";
    return 0;
}
