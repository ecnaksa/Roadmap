/*
 * #28 - SOLID: LSP (C++)
 *
 * =========================== TEORÍA ===========================
 * LSP: una subclase debe poder sustituir a su clase base sin romper el
 * programa. Aquí, una función que trabaja con Vehiculo& funciona con cualquier
 * subclase (Coche, Bicicleta, Tren) porque todas respetan el contrato de
 * acelerar/frenar.
 *
 * DIFICULTAD EXTRA: jerarquía de vehículos que cumple el LSP.
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

class Vehiculo {
protected:
    std::string nombre;
    int velocidad = 0;
public:
    explicit Vehiculo(std::string n) : nombre(std::move(n)) {}
    virtual ~Vehiculo() = default;
    virtual void acelerar(int inc) { velocidad += inc; }
    virtual void frenar(int dec) { velocidad = std::max(0, velocidad - dec); }
    const std::string& getNombre() const { return nombre; }
    int getVelocidad() const { return velocidad; }
};

class Coche : public Vehiculo { using Vehiculo::Vehiculo; };
class Bicicleta : public Vehiculo {
public:
    using Vehiculo::Vehiculo;
    void acelerar(int inc) override { velocidad += std::min(inc, 5); }  // límite humano
};
class Tren : public Vehiculo {
public:
    using Vehiculo::Vehiculo;
    void acelerar(int inc) override { velocidad += inc * 2; }
};

// Funciona con CUALQUIER Vehiculo -> demuestra LSP
void pruebaLSP(Vehiculo& v) {
    v.acelerar(10);
    v.frenar(3);
    std::cout << "  " << v.getNombre() << " -> velocidad " << v.getVelocidad() << "\n";
}

int main() {
    std::cout << "=== LSP: subclases sustituibles ===\n";
    std::vector<std::unique_ptr<Vehiculo>> vehiculos;
    vehiculos.push_back(std::make_unique<Coche>("Coche"));
    vehiculos.push_back(std::make_unique<Bicicleta>("Bicicleta"));
    vehiculos.push_back(std::make_unique<Tren>("Tren"));
    for (auto& v : vehiculos) pruebaLSP(*v);
    return 0;
}
