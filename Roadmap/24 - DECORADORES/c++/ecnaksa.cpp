/*
 * #24 - DECORADORES (C++)
 *
 * =========================== TEORÍA ===========================
 * C++ no tiene la sintaxis @decorador de Python, pero logra lo mismo con
 * funciones de orden superior: una función que recibe otra (o un std::function
 * / lambda) y devuelve una nueva que la "envuelve" añadiendo comportamiento
 * (medir tiempo, contar llamadas, cachear...).
 *
 * DIFICULTAD EXTRA: decorador que cuenta cuántas veces se llama a una función.
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <functional>
#include <chrono>
#include <string>
#include <memory>

// Decorador cronómetro: envuelve una función y mide su duración
template <typename Func>
auto cronometro(Func f, const std::string& nombre) {
    return [f, nombre](auto&&... args) {
        auto ini = std::chrono::high_resolution_clock::now();
        auto r = f(std::forward<decltype(args)>(args)...);
        auto fin = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> d = fin - ini;
        std::cout << "  '" << nombre << "' tardo " << d.count() << "s\n";
        return r;
    };
}

// Decorador contador de llamadas
template <typename Func>
auto contador(Func f, std::shared_ptr<int> cuenta) {
    return [f, cuenta](auto&&... args) {
        ++(*cuenta);
        std::cout << "  llamada #" << *cuenta << "\n";
        return f(std::forward<decltype(args)>(args)...);
    };
}

long sumaLenta(int n) {
    long s = 0;
    for (int i = 0; i < n; ++i) s += i;
    return s;
}

int main() {
    std::cout << "=== Decorador cronometro ===\n";
    auto suma = cronometro(sumaLenta, "sumaLenta");
    std::cout << "  resultado = " << suma(1000000) << "\n";

    std::cout << "\n=== Reto extra: contador de llamadas ===\n";
    auto cuenta = std::make_shared<int>(0);
    auto saludar = contador([](const std::string& n) { return "Hola " + n; }, cuenta);
    saludar("Ana");
    saludar("Luis");
    saludar("Marta");
    std::cout << "  Total de llamadas: " << *cuenta << std::endl;
    return 0;
}
