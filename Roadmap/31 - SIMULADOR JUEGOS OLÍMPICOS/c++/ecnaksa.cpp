/*
 * #31 - SIMULADOR DE JUEGOS OLÍMPICOS (C++)
 *
 * =========================== TEORÍA ===========================
 * Integra POO, contenedores de la STL y aleatoriedad (<random>). Modelamos
 * Participante, Evento y los Juegos como orquestador. La simulación baraja los
 * participantes y reparte medallas al podio.
 *
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <algorithm>

struct Participante { std::string nombre, pais; };

struct Evento {
    std::string nombre;
    std::vector<Participante> participantes;
    std::vector<Participante> podio;
};

int main() {
    std::mt19937 rng(2024);  // semilla fija -> reproducible

    std::vector<Evento> eventos = {
        {"100m lisos", {{"Bolt", "Jamaica"}, {"Gatlin", "EE.UU."}, {"Blake", "Jamaica"}, {"Coleman", "EE.UU."}}, {}},
        {"Natacion 200m", {{"Phelps", "EE.UU."}, {"Popov", "Rusia"}, {"Thorpe", "Australia"}}, {}},
        {"Maraton", {{"Kipchoge", "Kenia"}, {"Bekele", "Etiopia"}, {"Farah", "Reino Unido"}, {"Rupp", "EE.UU."}}, {}},
    };

    std::map<std::string, int> medallero;
    const char* medallas[] = {"Oro", "Plata", "Bronce"};

    std::cout << "===== INFORME JJOO Paris 2024 =====\n";
    for (auto& ev : eventos) {
        std::shuffle(ev.participantes.begin(), ev.participantes.end(), rng);
        std::cout << "\n" << ev.nombre << ":\n";
        for (int i = 0; i < 3 && i < (int)ev.participantes.size(); ++i) {
            auto& g = ev.participantes[i];
            std::cout << "  " << medallas[i] << ": " << g.nombre << " (" << g.pais << ")\n";
            medallero[g.pais]++;
        }
    }

    std::cout << "\n----- RANKING DE PAISES -----\n";
    std::vector<std::pair<std::string, int>> ranking(medallero.begin(), medallero.end());
    std::sort(ranking.begin(), ranking.end(), [](auto& a, auto& b) { return a.second > b.second; });
    int pos = 1;
    for (auto& [pais, total] : ranking)
        std::cout << "  " << pos++ << ". " << pais << ": " << total << " medalla(s)\n";
    return 0;
}
