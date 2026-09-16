/*
 * #32 - BATALLA DEADPOOL Y WOLVERINE (C++)
 *
 * =========================== TEORÍA ===========================
 * Simulación por turnos con <random>. Cada luchador tiene vida, rango de daño,
 * probabilidad de evasión y estado de regeneración (si recibe el golpe máximo,
 * pierde el siguiente turno).
 *
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <string>
#include <random>

struct Luchador {
    std::string nombre;
    int vida, danoMin, danoMax;
    double probEvasion;
    bool debeRegenerar = false;
    bool vivo() const { return vida > 0; }
};

int main() {
    std::mt19937 rng(7);
    Luchador deadpool{"Deadpool", 300, 10, 100, 0.25};
    Luchador wolverine{"Wolverine", 300, 10, 120, 0.20};

    std::cout << "=== Deadpool vs Wolverine! ===\n";
    Luchador *ata = &deadpool, *def = &wolverine;
    int turno = 0;
    while (deadpool.vivo() && wolverine.vivo()) {
        std::cout << "\n--- Turno " << ++turno << " ---\n";
        if (ata->debeRegenerar) {
            std::cout << "  " << ata->nombre << " se regenera y pierde el turno.\n";
            ata->debeRegenerar = false;
        } else {
            int dano = std::uniform_int_distribution<>(ata->danoMin, ata->danoMax)(rng);
            bool maximo = (dano == ata->danoMax);
            if (std::uniform_real_distribution<>(0, 1)(rng) < def->probEvasion) {
                std::cout << "  " << ata->nombre << " ataca por " << dano << ", pero "
                          << def->nombre << " lo esquiva!\n";
            } else {
                def->vida -= dano;
                std::cout << "  " << ata->nombre << " inflige " << dano << " de danio"
                          << (maximo ? " (golpe maximo!)" : "") << ".\n";
                if (maximo) def->debeRegenerar = true;
            }
        }
        std::cout << "  Vida -> " << deadpool.nombre << ": " << std::max(0, deadpool.vida)
                  << " | " << wolverine.nombre << ": " << std::max(0, wolverine.vida) << "\n";
        std::swap(ata, def);
    }
    std::cout << "\n" << (deadpool.vivo() ? deadpool.nombre : wolverine.nombre) << " gana la batalla!\n";
    return 0;
}
