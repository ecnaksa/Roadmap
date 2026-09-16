/*
 * #15 - ASINCRONÍA (C++)
 *
 * =========================== TEORÍA ===========================
 * C++ ofrece concurrencia real con hilos: <thread> (std::thread), <future>
 * (std::async, std::future) y <chrono> para dormir. std::async lanza una
 * tarea que puede ejecutarse en otro hilo; con varios futures se logra
 * paralelismo, y .get() espera su finalización.
 *
 * DIFICULTAD EXTRA: C, B, A en paralelo; D cuando terminan las tres.
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <string>
#include <mutex>

std::mutex io;
auto inicio = std::chrono::steady_clock::now();

std::string tarea(const std::string& nombre, int segundos) {
    {
        std::lock_guard<std::mutex> lock(io);
        std::cout << "  > '" << nombre << "' empieza (durara " << segundos << "s)\n";
    }
    std::this_thread::sleep_for(std::chrono::seconds(segundos));
    {
        std::lock_guard<std::mutex> lock(io);
        std::cout << "  # '" << nombre << "' finaliza\n";
    }
    return nombre;
}

int main() {
    std::cout << "=== Tarea asincrona simple ===\n";
    auto simple = std::async(std::launch::async, tarea, "Sencilla", 1);
    simple.get();

    std::cout << "\n=== Reto extra: C, B, A en paralelo; luego D ===\n";
    auto c = std::async(std::launch::async, tarea, "C", 3);
    auto b = std::async(std::launch::async, tarea, "B", 2);
    auto a = std::async(std::launch::async, tarea, "A", 1);
    c.get(); b.get(); a.get();          // esperar a las tres
    auto d = std::async(std::launch::async, tarea, "D", 1);
    d.get();
    return 0;
}
