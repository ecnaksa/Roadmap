/*
 * #16 - EXPRESIONES REGULARES (C++)
 *
 * =========================== TEORÍA ===========================
 * C++11 incluye <regex>: std::regex define el patrón; std::regex_search y
 * std::sregex_iterator buscan coincidencias; std::regex_match valida la
 * cadena entera. Metacaracteres: \d dígito, \w alfanumérico, + una o más...
 * (en C++ las barras se escapan: "\\d").
 *
 * DIFICULTAD EXTRA: validar email, teléfono y URL.
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <regex>
#include <string>

int main() {
    std::string texto = "El pedido 12 costo 34.50 euros y llego en 7 dias, codigo 007.";
    std::regex numeros(R"(\d+(?:\.\d+)?)");
    std::cout << "=== Extraer numeros ===\n  ";
    for (auto it = std::sregex_iterator(texto.begin(), texto.end(), numeros);
         it != std::sregex_iterator(); ++it)
        std::cout << it->str() << " ";
    std::cout << "\n";

    std::regex email(R"(^[\w.+-]+@[\w-]+\.[\w.-]+$)");
    std::regex telefono(R"(^(\+\d{1,3}\s?)?(\d[\s-]?){8,12}$)");
    std::regex url(R"(^https?://([\w-]+\.)+[\w-]+(/[\w./?%&=-]*)?$)");

    std::cout << "\n=== Reto extra: validaciones ===\n";
    std::cout << std::boolalpha;
    for (auto& e : {"hola@dominio.com", "malo@@x"})
        std::cout << "  email " << e << " -> " << std::regex_match(std::string(e), email) << "\n";
    for (auto& t : {"+34 600123456", "abc"})
        std::cout << "  tel   " << t << " -> " << std::regex_match(std::string(t), telefono) << "\n";
    for (auto& u : {"https://mouredev.com", "sin-protocolo.com"})
        std::cout << "  url   " << u << " -> " << std::regex_match(std::string(u), url) << "\n";
    return 0;
}
