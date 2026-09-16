/*
 * #13 - PRUEBAS UNITARIAS (C++)
 *
 * =========================== TEORÍA ===========================
 * Las PRUEBAS UNITARIAS verifican automáticamente el comportamiento del
 * código. En proyectos reales se usan frameworks como GoogleTest o Catch2.
 * Aquí, sin dependencias, montamos un mini-framework con una macro CHECK que
 * cuenta aciertos y fallos (misma idea que assertEqual de otros lenguajes).
 *
 * DIFICULTAD EXTRA: tests sobre un "perfil" (campos presentes y correctos).
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <string>
#include <map>
#include <vector>

int fallos = 0, total = 0;
#define CHECK(cond) do { \
    ++total; \
    if (cond) std::cout << "  [OK] " #cond "\n"; \
    else { std::cout << "  [FALLO] " #cond "\n"; ++fallos; } \
} while (0)

int sumar(int a, int b) { return a + b; }

int main() {
    std::cout << "=== Tests de sumar ===\n";
    CHECK(sumar(2, 3) == 5);
    CHECK(sumar(-2, -3) == -5);
    CHECK(sumar(0, 0) == 0);

    std::cout << "\n=== Reto extra: perfil ===\n";
    std::map<std::string, std::string> perfil = {
        {"name", "ecnaksa"}, {"age", "30"}, {"birth_date", "1994-05-12"}};
    std::vector<std::string> lenguajes = {"C++", "Python"};

    // Test 1: existen todos los campos
    CHECK(perfil.count("name") && perfil.count("age") && perfil.count("birth_date"));
    CHECK(!lenguajes.empty());
    // Test 2: los datos son correctos
    CHECK(!perfil["name"].empty());
    CHECK(std::stoi(perfil["age"]) > 0);
    CHECK(perfil["birth_date"].size() == 10);

    std::cout << "\n=== Resultado: " << (total - fallos) << "/" << total << " tests OK ===\n";
    return fallos == 0 ? 0 : 1;
}
