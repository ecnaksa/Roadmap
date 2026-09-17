/*
 * #49 - EL ALMACÉN DE PAPÁ NOEL (C++)
 *
 * =========================== TEORÍA ===========================
 * Juego tipo Mastermind. Código de 4 caracteres (letras A-C y números 1-3, sin
 * repetidos). Para cada intento se compara carácter a carácter: Correcto (bien
 * colocado), Presente (existe en otra posición) o Incorrecto.
 *
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>

const int LONGITUD = 4;

std::string generarCodigo(std::mt19937& rng) {
    std::string chars = "ABC123";
    std::shuffle(chars.begin(), chars.end(), rng);
    return chars.substr(0, LONGITUD);
}

std::string validar(const std::string& intento) {
    if ((int)intento.size() != LONGITUD) return "el codigo debe tener 4 caracteres";
    for (char c : intento)
        if (std::string("ABC123").find(c) == std::string::npos) return std::string("caracter no soportado: ") + c;
    return "";
}

void evaluar(const std::string& secreto, const std::string& intento) {
    std::cout << "  ";
    for (int i = 0; i < LONGITUD; ++i) {
        std::string estado = (intento[i] == secreto[i]) ? "Correcto"
            : (secreto.find(intento[i]) != std::string::npos) ? "Presente" : "Incorrecto";
        std::cout << intento[i] << ":" << estado << "  ";
    }
    std::cout << "\n";
}

int main() {
    std::mt19937 rng(49);
    std::string secreto = generarCodigo(rng);
    std::cout << "=== El almacen de Papa Noel (demo) ===\n";
    std::cout << "(codigo secreto para la demo: " << secreto << ")\n";

    std::vector<std::string> intentos = {"AB12", "XY99", secreto};
    int n = 1;
    for (auto& intento : intentos) {
        std::string err = validar(intento);
        if (!err.empty()) { std::cout << "  Intento " << n++ << " '" << intento << "': [!] " << err << "\n"; continue; }
        std::cout << "  Intento " << n++ << " '" << intento << "':\n";
        evaluar(secreto, intento);
        if (intento == secreto) { std::cout << "  Codigo descifrado!\n"; break; }
    }
    return 0;
}
