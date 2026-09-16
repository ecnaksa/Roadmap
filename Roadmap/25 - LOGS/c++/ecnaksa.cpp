/*
 * #25 - LOGS (C++)
 *
 * =========================== TEORÍA ===========================
 * El LOGGING registra eventos con distintos niveles de severidad. La librería
 * estándar de C++ no trae un logger (se usan spdlog, glog...). Aquí montamos
 * uno sencillo con niveles DEBUG < INFO < WARNING < ERROR < CRITICAL, un nivel
 * mínimo configurable y marca de tiempo.
 *
 * DIFICULTAD EXTRA: gestor de tareas con logs y tiempos.
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <string>
#include <map>
#include <chrono>
#include <ctime>

enum class Nivel { DEBUG, INFO, WARNING, ERROR, CRITICAL };

class Logger {
    Nivel minimo;
    static std::string etiqueta(Nivel n) {
        switch (n) {
            case Nivel::DEBUG: return "DEBUG"; case Nivel::INFO: return "INFO";
            case Nivel::WARNING: return "WARNING"; case Nivel::ERROR: return "ERROR";
            default: return "CRITICAL";
        }
    }
public:
    explicit Logger(Nivel m = Nivel::DEBUG) : minimo(m) {}
    void log(Nivel n, const std::string& msg) const {
        if (n < minimo) return;
        std::time_t t = std::time(nullptr);
        char hora[16]; std::strftime(hora, sizeof hora, "%H:%M:%S", std::localtime(&t));
        std::cout << hora << " [" << etiqueta(n) << "] " << msg << "\n";
    }
};

int main() {
    Logger log;
    std::cout << "=== Niveles de severidad ===\n";
    log.log(Nivel::DEBUG, "detalle para desarrolladores");
    log.log(Nivel::INFO, "todo va segun lo esperado");
    log.log(Nivel::WARNING, "algo inusual");
    log.log(Nivel::ERROR, "ha fallado una operacion");
    log.log(Nivel::CRITICAL, "fallo grave");

    std::cout << "\n=== Reto extra: gestor de tareas con logs ===\n";
    std::map<std::string, std::string> tareas;
    auto anadir = [&](const std::string& n, const std::string& d) {
        auto ini = std::chrono::high_resolution_clock::now();
        if (tareas.count(n)) log.log(Nivel::WARNING, "la tarea '" + n + "' ya existe");
        tareas[n] = d;
        std::chrono::duration<double> dt = std::chrono::high_resolution_clock::now() - ini;
        log.log(Nivel::INFO, "tarea anadida: '" + n + "' (" + std::to_string(dt.count()) + "s)");
    };
    auto eliminar = [&](const std::string& n) {
        if (tareas.erase(n)) log.log(Nivel::INFO, "tarea eliminada: '" + n + "'");
        else log.log(Nivel::ERROR, "no existe: '" + n + "'");
    };
    anadir("Estudiar", "Repasar decoradores");
    anadir("Comprar", "Leche y pan");
    eliminar("Inexistente");
    eliminar("Comprar");
    return 0;
}
