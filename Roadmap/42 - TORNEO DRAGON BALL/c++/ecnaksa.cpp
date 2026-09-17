/*
 * #42 - TORNEO DRAGON BALL (C++)
 *
 * =========================== TEORÍA ===========================
 * Simulación de combates + estructura de torneo por eliminación. Requiere un
 * número de luchadores potencia de 2. En cada ronda se emparejan al azar; el
 * ganador avanza hasta que queda uno.
 *
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>

struct Luchador { std::string nombre; int velocidad, ataque, defensa, salud = 100; };

std::mt19937 rng(42);

int dano(const Luchador& a, const Luchador& d) {
    if (a.ataque > d.defensa) return a.ataque - d.defensa;
    return std::max(1, (int)(a.ataque * 0.10));
}

Luchador combate(Luchador a, Luchador b) {
    a.salud = b.salud = 100;
    Luchador *ata = a.velocidad >= b.velocidad ? &a : &b;
    Luchador *def = ata == &a ? &b : &a;
    std::cout << "    " << a.nombre << " vs " << b.nombre << " (empieza " << ata->nombre << ")\n";
    while (a.salud > 0 && b.salud > 0) {
        if (std::uniform_real_distribution<>(0, 1)(rng) >= 0.20) {  // 20% esquiva
            def->salud -= dano(*ata, *def);
        }
        std::swap(ata, def);
    }
    Luchador ganador = a.salud > 0 ? a : b;
    std::cout << "    -> gana " << ganador.nombre << "\n";
    return ganador;
}

int main() {
    std::vector<Luchador> luchadores = {
        {"Goku", 90, 85, 70}, {"Vegeta", 85, 88, 65}, {"Piccolo", 70, 75, 80},
        {"Freezer", 95, 90, 60}, {"Gohan", 80, 82, 72}, {"Cell", 78, 86, 78},
        {"Krilin", 65, 60, 55}, {"Trunks", 82, 80, 68},
    };
    // Potencia de 2
    if ((luchadores.size() & (luchadores.size() - 1)) != 0) {
        std::cout << "El numero de luchadores debe ser potencia de 2.\n";
        return 1;
    }

    std::cout << "=== Torneo de Artes Marciales ===\n";
    std::shuffle(luchadores.begin(), luchadores.end(), rng);
    int ronda = 1;
    while (luchadores.size() > 1) {
        std::cout << "\n--- Ronda " << ronda++ << " (" << luchadores.size() << " luchadores) ---\n";
        std::vector<Luchador> siguiente;
        for (size_t i = 0; i < luchadores.size(); i += 2)
            siguiente.push_back(combate(luchadores[i], luchadores[i + 1]));
        luchadores = siguiente;
        std::shuffle(luchadores.begin(), luchadores.end(), rng);
    }
    std::cout << "\n" << luchadores[0].nombre << " es el campeon del torneo!\n";
    return 0;
}
