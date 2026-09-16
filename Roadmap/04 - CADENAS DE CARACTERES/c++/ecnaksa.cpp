/*
 * #04 - CADENAS DE CARACTERES (C++)
 *
 * =========================== TEORÍA ===========================
 * std::string (STL) representa cadenas y ofrece métodos: length/size, acceso
 * por índice, substr, +, find, replace, comparación... Es mutable, a
 * diferencia de las cadenas de Python.
 *
 * DIFICULTAD EXTRA: comprobar si dos palabras son palíndromos, anagramas e
 * isogramas.
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <set>

static std::string normalizar(const std::string& s) {
    std::string r;
    for (char c : s) if (std::isalnum((unsigned char)c)) r += std::tolower((unsigned char)c);
    return r;
}

static bool esPalindromo(const std::string& s) {
    std::string n = normalizar(s), rev(n.rbegin(), n.rend());
    return n == rev;
}

static bool sonAnagramas(const std::string& a, const std::string& b) {
    std::string x = normalizar(a), y = normalizar(b);
    std::sort(x.begin(), x.end());
    std::sort(y.begin(), y.end());
    return x == y;
}

static bool esIsograma(const std::string& s) {
    std::string n = normalizar(s);
    std::set<char> unicos(n.begin(), n.end());
    return unicos.size() == n.size();
}

int main() {
    std::string s = "Hola, C++";
    std::cout << "=== Operaciones ===\n";
    std::cout << "longitud: " << s.size() << "\n";
    std::cout << "s[0]: " << s[0] << "\n";
    std::cout << "substr(6): " << s.substr(6) << "\n";
    std::cout << "concat: " << s + "!" << "\n";
    std::string mayus = s; std::transform(mayus.begin(), mayus.end(), mayus.begin(), ::toupper);
    std::cout << "mayusculas: " << mayus << "\n";
    std::cout << "find('C'): " << s.find('C') << "\n";

    std::cout << "\n=== Reto extra ===\n";
    auto analizar = [](const std::string& a, const std::string& b) {
        std::cout << "  '" << a << "' palindromo? " << std::boolalpha << esPalindromo(a) << "\n";
        std::cout << "  '" << a << "' y '" << b << "' anagramas? " << sonAnagramas(a, b) << "\n";
        std::cout << "  '" << a << "' isograma? " << esIsograma(a) << "\n";
    };
    analizar("Roma", "Amor");
    analizar("Anita lava la tina", "casa");
    return 0;
}
