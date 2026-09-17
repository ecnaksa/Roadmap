/*
 * #50 - PLANIFICADOR DE OBJETIVOS DE AÑO NUEVO (C++)
 *
 * =========================== TEORÍA ===========================
 * Lógica + generación de informe + escritura de ficheros. Cada objetivo
 * reparte su cantidad total entre los meses de su plazo; se genera una vista
 * mes a mes y se exporta a .txt (que no se sube).
 *
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdio>
#include <algorithm>

const char* MESES[] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
    "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};

struct Objetivo { std::string meta, unidades; int cantidad, plazo; };

std::string fmt(double v) {
    if (v == (long)v) return std::to_string((long)v);
    std::ostringstream ss; ss.precision(2); ss << std::fixed << v; return ss.str();
}

std::string calcularPlan(const std::vector<Objetivo>& objetivos) {
    if (objetivos.empty()) return "(sin objetivos)";
    int meses = 0;
    for (auto& o : objetivos) meses = std::max(meses, o.plazo);
    std::ostringstream out;
    out << "=== PLAN DE OBJETIVOS DE ANIO NUEVO ===\n";
    for (int m = 0; m < meses; ++m) {
        out << "\n" << MESES[m] << ":\n";
        int n = 1;
        for (auto& o : objetivos)
            if (m < o.plazo)
                out << "[ ] " << n++ << ". " << o.meta << " (" << fmt((double)o.cantidad / o.plazo)
                    << " " << o.unidades << "/mes). Total: " << o.cantidad << ".\n";
    }
    return out.str();
}

int main() {
    std::vector<Objetivo> objetivos = {
        {"Leer libros", "libros", 12, 12},
        {"Estudiar Git", "curso", 1, 1},
        {"Correr", "km", 300, 6},
    };
    std::cout << "=== Planificador de objetivos (demo) ===\n";
    std::string plan = calcularPlan(objetivos);
    std::cout << plan;

    std::ofstream f("propositos.txt"); f << plan; f.close();
    std::cout << "\nPlan exportado a 'propositos.txt'\n";
    std::remove("propositos.txt");
    std::cout << "(fichero borrado tras la demo)\n";
    return 0;
}
