/*
 * #44 - CUENTA ATRÁS MOUREDEV PRO (C++)
 *
 * =========================== TEORÍA ===========================
 * Combina fechas (<ctime>/<chrono>), conversión a UTC (gmtime) y concurrencia
 * (<thread>). La cuenta atrás corre en un hilo aparte, se actualiza cada
 * segundo y limpia la terminal en cada iteración.
 *
 * ============================ PRÁCTICA ========================
 * La demo usa 3 segundos y NO limpia la pantalla, para ver la salida.
 */

#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
#include <cstdlib>

void cuentaAtras(std::time_t objetivo, bool limpiar) {
    while (true) {
        long restante = (long)(objetivo - std::time(nullptr));
        if (limpiar) std::system("clear");
        if (restante <= 0) {
            std::cout << "Es la hora! mouredev pro ya esta disponible: https://mouredev.pro\n";
            break;
        }
        long dias = restante / 86400, horas = (restante % 86400) / 3600;
        long min = (restante % 3600) / 60, seg = restante % 60;
        std::cout << "Cuenta atras: " << dias << "d " << horas << "h " << min << "m " << seg << "s\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    std::cout << "=== Cuenta atras (demo 3s, sin limpiar) ===\n";
    std::time_t objetivo = std::time(nullptr) + 3;
    // Se convierte a UTC internamente al comparar con time(): time() ya es UTC.
    std::thread hilo(cuentaAtras, objetivo, false);
    hilo.join();
    return 0;
}
