/*
 * #00 - SINTAXIS, VARIABLES, TIPOS DE DATOS Y HOLA MUNDO
 * Web oficial del lenguaje: https://isocpp.org
 *
 * =========================== TEORÍA ===========================
 * C++ es un lenguaje compilado, de tipado ESTÁTICO y fuerte: el tipo de cada
 * variable se conoce en tiempo de compilación. Añade a C la programación
 * orientada a objetos, plantillas (templates) y una amplia librería estándar
 * (STL).
 *  - Variables: se declaran con su tipo -> int edad = 30;
 *  - Constantes: con la palabra clave 'const' (o 'constexpr').
 *  - Tipos primitivos: int, long, float, double, char, bool y void.
 *  - std::string (de la STL) representa cadenas de texto.
 *
 * ============================ PRÁCTICA ========================
 * Compilar: g++ -std=c++17 ecnaksa.cpp -o ecnaksa && ./ecnaksa
 */

#include <iostream>  // entrada/salida
#include <string>

// Comentario de una sola línea
/* Comentario
   de varias líneas */

int main() {
    // Variables (tipado estático)
    std::string nombre = "ecnaksa";  // cadena
    int edad = 30;                    // entero
    double altura = 1.80;             // coma flotante (doble precisión)
    char inicial = 'E';              // carácter
    bool programador = true;          // booleano

    // Constante
    const double PI = 3.14159;

    std::cout << "=== Variables y tipos ===\n";
    std::cout << "nombre (string): " << nombre << "\n";
    std::cout << "edad (int):      " << edad << "\n";
    std::cout << "altura (double): " << altura << "\n";
    std::cout << "inicial (char):  " << inicial << "\n";
    std::cout << "programador (bool): " << std::boolalpha << programador << "\n";
    std::cout << "PI (const):      " << PI << "\n\n";

    std::cout << "¡Hola, C++!" << std::endl;
    return 0;
}
