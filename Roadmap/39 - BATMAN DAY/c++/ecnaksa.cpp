/*
 * #39 - BATMAN DAY (reto doble) (C++)
 *
 * =========================== TEORÍA ===========================
 * RETO 1: cálculo de fechas (tercer sábado de septiembre) con <ctime>.
 * RETO 2: recorrido de matriz 20x20 con ventana deslizante 3x3 para hallar la
 * zona de mayor amenaza, y distancia Manhattan a la Batcueva (0,0).
 *
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <ctime>
#include <vector>
#include <tuple>

static int diaSemana(int anio, int mes, int dia) {  // 0=domingo..6=sabado
    std::tm t = {};
    t.tm_year = anio - 1900; t.tm_mon = mes - 1; t.tm_mday = dia;
    std::mktime(&t);
    return t.tm_wday;
}

int main() {
    std::cout << "=== RETO 1: Batman Day hasta el 100 aniversario ===\n";
    const int PRIMER = 1939;
    for (int aniv = 85; aniv <= 100; ++aniv) {
        int anio = PRIMER + aniv;
        int sabados = 0, dia = 0;
        for (int d = 1; d <= 30; ++d)
            if (diaSemana(anio, 9, d) == 6 && ++sabados == 3) { dia = d; break; }
        std::cout << "  " << aniv << "o aniversario (" << anio << "): sabado "
                  << (dia < 10 ? "0" : "") << dia << "/09/" << anio << "\n";
    }

    std::cout << "\n=== RETO 2: seguridad de la Batcueva ===\n";
    int grid[20][20] = {};
    std::vector<std::tuple<int, int, int>> sensores = {
        {5, 5, 8}, {6, 5, 7}, {5, 6, 9}, {6, 6, 6}, {1, 1, 2}, {18, 18, 10}, {10, 10, 3}, {4, 5, 4}};
    for (auto& [x, y, a] : sensores) grid[y][x] = a;

    int mejorSuma = -1, cx = 0, cy = 0;
    for (int y = 1; y < 19; ++y)
        for (int x = 1; x < 19; ++x) {
            int suma = 0;
            for (int dy = -1; dy <= 1; ++dy)
                for (int dx = -1; dx <= 1; ++dx) suma += grid[y + dy][x + dx];
            if (suma > mejorSuma) { mejorSuma = suma; cx = x; cy = y; }
        }
    std::cout << "  Centro mas amenazado: (" << cx << ", " << cy << ")\n";
    std::cout << "  Suma de amenazas 3x3: " << mejorSuma << "\n";
    std::cout << "  Distancia a la Batcueva: " << (cx + cy) << "\n";
    std::cout << "  Activar protocolo (>20)? " << (mejorSuma > 20 ? "SI" : "no") << "\n";
    return 0;
}
