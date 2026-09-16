/*
 * #07 - PILAS Y COLAS (C++)
 *
 * =========================== TEORÍA ===========================
 * PILA (stack) -> LIFO. COLA (queue) -> FIFO. La STL ofrece std::stack y
 * std::queue como adaptadores de contenedor listos para usar.
 *
 * DIFICULTAD EXTRA: navegador (adelante/atrás con dos pilas) e impresora
 * (cola de documentos).
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <vector>

void navegador(const std::vector<std::string>& comandos) {
    std::cout << "\n=== Reto extra: navegador (pilas) ===\n";
    std::stack<std::string> atras, adelante;
    std::string actual;
    for (const auto& c : comandos) {
        if (c == "atras") {
            if (!atras.empty()) { adelante.push(actual); actual = atras.top(); atras.pop();
                std::cout << "  <- atras -> " << actual << "\n"; }
            else std::cout << "  <- no hay anteriores\n";
        } else if (c == "adelante") {
            if (!adelante.empty()) { atras.push(actual); actual = adelante.top(); adelante.pop();
                std::cout << "  -> adelante -> " << actual << "\n"; }
            else std::cout << "  -> no hay siguientes\n";
        } else {
            if (!actual.empty()) atras.push(actual);
            actual = c; while (!adelante.empty()) adelante.pop();
            std::cout << "  visitar '" << c << "'\n";
        }
    }
}

void impresora(const std::vector<std::string>& comandos) {
    std::cout << "\n=== Reto extra: impresora (cola) ===\n";
    std::queue<std::string> cola;
    for (const auto& c : comandos) {
        if (c == "imprimir") {
            if (!cola.empty()) { std::cout << "  imprimiendo '" << cola.front() << "'\n"; cola.pop(); }
            else std::cout << "  no hay documentos\n";
        } else { cola.push(c); std::cout << "  + en cola '" << c << "'\n"; }
    }
}

int main() {
    std::cout << "=== PILA (LIFO) ===\n  ";
    std::stack<int> p;
    for (int x : {1, 2, 3}) p.push(x);
    while (!p.empty()) { std::cout << p.top() << " "; p.pop(); }

    std::cout << "\n\n=== COLA (FIFO) ===\n  ";
    std::queue<int> q;
    for (int x : {1, 2, 3}) q.push(x);
    while (!q.empty()) { std::cout << q.front() << " "; q.pop(); }
    std::cout << "\n";

    navegador({"mouredev.com", "python.org", "atras", "atras", "github.com", "adelante"});
    impresora({"informe.pdf", "foto.png", "imprimir", "nomina.docx", "imprimir", "imprimir", "imprimir"});
    return 0;
}
