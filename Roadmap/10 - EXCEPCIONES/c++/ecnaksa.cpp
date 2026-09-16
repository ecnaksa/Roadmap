/*
 * #10 - EXCEPCIONES (C++)
 *
 * =========================== TEORÍA ===========================
 * C++ maneja errores con try/throw/catch. Se puede lanzar cualquier tipo,
 * aunque lo idiomático es derivar de std::exception. El bloque catch(...)
 * captura cualquier excepción.
 *
 * DIFICULTAD EXTRA: función que lanza 3 tipos de excepción (una propia).
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// Excepción personalizada
class EdadInvalida : public std::exception {
    std::string msg;
public:
    explicit EdadInvalida(std::string m) : msg(std::move(m)) {}
    const char* what() const noexcept override { return msg.c_str(); }
};

int procesarEdad(const std::string& valor) {
    size_t pos;
    int edad;
    try {
        edad = std::stoi(valor, &pos);       // puede lanzar std::invalid_argument
    } catch (const std::invalid_argument&) {
        throw std::invalid_argument("No es un numero: " + valor);
    }
    if (pos != valor.size()) throw std::invalid_argument("Formato invalido: " + valor);
    if (edad < 0 || edad > 150) throw EdadInvalida("Edad fuera de rango: " + std::to_string(edad));
    return edad;
}

void evaluar(const std::string& valor) {
    std::cout << "Entrada '" << valor << "': ";
    try {
        std::cout << "OK edad = " << procesarEdad(valor);
    } catch (const EdadInvalida& e) {
        std::cout << "[EdadInvalida] " << e.what();
    } catch (const std::invalid_argument& e) {
        std::cout << "[invalid_argument] " << e.what();
    } catch (const std::exception& e) {
        std::cout << "[exception] " << e.what();
    }
    std::cout << " -> finalizado\n";
}

int main() {
    std::cout << "=== Captura basica ===\n";
    try {
        std::vector<int> v = {1, 2, 3};
        std::cout << v.at(10);               // lanza std::out_of_range
    } catch (const std::out_of_range& e) {
        std::cout << "  out_of_range: " << e.what() << "\n";
    }

    std::cout << "\n=== Reto extra ===\n";
    for (const std::string& e : {"25", "abc", "200", "40"}) evaluar(e);
    return 0;
}
