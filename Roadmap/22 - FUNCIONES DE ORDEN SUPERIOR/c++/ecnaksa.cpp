/*
 * #22 - FUNCIONES DE ORDEN SUPERIOR (C++)
 *
 * =========================== TEORÍA ===========================
 * Una FUNCIÓN DE ORDEN SUPERIOR recibe y/o devuelve funciones. C++ las soporta
 * con std::function y lambdas, y con algoritmos de <algorithm> y <numeric>:
 * std::transform (map), std::copy_if (filter), std::accumulate (reduce),
 * std::sort con comparador...
 *
 * DIFICULTAD EXTRA: análisis de estudiantes.
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <functional>

struct Estudiante { std::string nombre; int anio; std::vector<double> notas; };

int main() {
    std::cout << "=== HOF basicas ===\n";
    std::vector<int> nums = {1, 2, 3, 4, 5, 6};
    std::vector<int> doblados;
    std::transform(nums.begin(), nums.end(), std::back_inserter(doblados), [](int x) { return x * 2; });
    std::cout << "  transform x2: "; for (int x : doblados) std::cout << x << " "; std::cout << "\n";
    int suma = std::accumulate(nums.begin(), nums.end(), 0);
    std::cout << "  accumulate: " << suma << "\n";
    auto multiplicador = [](int f) { return [f](int x) { return x * f; }; };  // devuelve función
    std::cout << "  funcion que devuelve funcion: triple(10)=" << multiplicador(3)(10) << "\n";

    std::cout << "\n=== Reto extra: estudiantes ===\n";
    std::vector<Estudiante> est = {
        {"Ana", 2001, {8.5, 9.0, 7.5}},
        {"Luis", 1999, {9.2, 9.5, 9.8}},
        {"Marta", 2003, {6.0, 7.0, 8.0}},
        {"Iker", 2000, {9.0, 9.1, 9.3}},
    };

    auto promedio = [](const Estudiante& e) {
        return std::accumulate(e.notas.begin(), e.notas.end(), 0.0) / e.notas.size();
    };

    std::cout << "  Promedios: ";
    for (auto& e : est) std::cout << e.nombre << "=" << promedio(e) << " ";
    std::cout << "\n  Mejores (>=9): ";
    for (auto& e : est) if (promedio(e) >= 9) std::cout << e.nombre << " ";

    std::vector<Estudiante> jovenes = est;
    std::sort(jovenes.begin(), jovenes.end(), [](auto& a, auto& b) { return a.anio > b.anio; });
    std::cout << "\n  Del mas joven: ";
    for (auto& e : jovenes) std::cout << e.nombre << " ";

    double maxNota = 0;
    for (auto& e : est) maxNota = std::max(maxNota, *std::max_element(e.notas.begin(), e.notas.end()));
    std::cout << "\n  Mayor calificacion: " << maxNota << std::endl;
    return 0;
}
