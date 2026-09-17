/*
 * #48 - ÁRBOL DE NAVIDAD (C++)
 *
 * =========================== TEORÍA ===========================
 * Dibujo por terminal + estado con conjuntos de posiciones. El follaje es un
 * triángulo (fila i -> 2i+1 estrellas). Bolas ('o') y luces ('+' encendida /
 * '*' apagada) ocupan posiciones disjuntas; la estrella ('@') va en la copa.
 *
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <set>
#include <vector>
#include <random>
#include <string>
#include <algorithm>

using Pos = std::pair<int, int>;

class Arbol {
    int altura;
    bool estrella = false, encendidas = true;
    std::set<Pos> bolas, luces;
    std::mt19937 rng{48};
public:
    explicit Arbol(int h) : altura(h) {}

    std::vector<Pos> libres() {
        std::vector<Pos> res;
        for (int i = 0; i < altura; ++i)
            for (int c = 0; c < 2 * i + 1; ++c) {
                Pos p{i, c};
                if (p == Pos{0, 0}) continue;  // reservado para la estrella
                if (!bolas.count(p) && !luces.count(p)) res.push_back(p);
            }
        return res;
    }
    std::string ponerEstrella() { estrella = !estrella; return estrella ? "Estrella anadida" : "Estrella retirada"; }
    std::string anadir(std::set<Pos>& destino, int cuantas, const std::string& que) {
        auto libs = libres();
        if ((int)libs.size() < cuantas) return "[!] no hay sitio para " + que;
        std::shuffle(libs.begin(), libs.end(), rng);
        for (int i = 0; i < cuantas; ++i) destino.insert(libs[i]);
        return que + " anadidas";
    }
    std::string anadirBolas() { return anadir(bolas, 2, "2 bolas"); }
    std::string anadirLuces() { return anadir(luces, 3, "3 luces"); }
    std::string interruptor() { encendidas = !encendidas; return encendidas ? "Luces encendidas" : "Luces apagadas"; }

    char simbolo(int i, int c) {
        if (i == 0 && c == 0 && estrella) return '@';
        if (bolas.count({i, c})) return 'o';
        if (luces.count({i, c})) return encendidas ? '+' : '*';
        return '*';
    }
    void dibujar() {
        for (int i = 0; i < altura; ++i) {
            std::cout << std::string(altura - 1 - i, ' ');
            for (int c = 0; c < 2 * i + 1; ++c) std::cout << simbolo(i, c);
            std::cout << "\n";
        }
        std::string tronco = std::string(std::max(0, altura - 2), ' ') + "|||";
        std::cout << tronco << "\n" << tronco << "\n";
    }
};

int main() {
    Arbol arbol(7);
    std::cout << "=== Arbol base (altura 7) ===\n";
    arbol.dibujar();
    std::cout << "\n> " << arbol.ponerEstrella() << "\n> " << arbol.anadirBolas()
              << "\n> " << arbol.anadirLuces() << "\n> " << arbol.anadirLuces() << "\n";
    std::cout << "\n=== Arbol decorado ===\n";
    arbol.dibujar();
    std::cout << "\n> " << arbol.interruptor() << "\n=== Con las luces apagadas ===\n";
    arbol.dibujar();
    return 0;
}
