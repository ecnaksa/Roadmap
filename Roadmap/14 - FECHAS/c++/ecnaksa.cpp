/*
 * #14 - FECHAS (C++)
 *
 * =========================== TEORÍA ===========================
 * C++ hereda de C <ctime> (struct tm, time(), strftime()) y desde C++11 añade
 * <chrono> para medir tiempos con precisión. Para formatear una fecha a texto
 * se usa std::strftime con códigos: %d día, %m mes, %Y año, %H:%M:%S hora...
 *
 * DIFICULTAD EXTRA: mostrar la fecha de nacimiento en 10 formatos.
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <ctime>
#include <string>

static std::string formatear(const std::tm& t, const char* patron) {
    char buffer[128];
    std::strftime(buffer, sizeof buffer, patron, &t);
    return buffer;
}

int main() {
    std::time_t ahora_t = std::time(nullptr);
    std::tm ahora = *std::localtime(&ahora_t);

    std::tm nacimiento{};
    nacimiento.tm_year = 1994 - 1900;  // años desde 1900
    nacimiento.tm_mon = 5 - 1;          // meses 0-11
    nacimiento.tm_mday = 12;
    nacimiento.tm_hour = 8; nacimiento.tm_min = 30;
    std::mktime(&nacimiento);           // normaliza (calcula día de semana, etc.)

    int anios = (ahora.tm_year - nacimiento.tm_year);
    if (ahora.tm_mon < nacimiento.tm_mon ||
        (ahora.tm_mon == nacimiento.tm_mon && ahora.tm_mday < nacimiento.tm_mday))
        --anios;

    std::cout << "=== Fechas ===\n";
    std::cout << "  Ahora:      " << formatear(ahora, "%Y-%m-%d %H:%M:%S") << "\n";
    std::cout << "  Nacimiento: " << formatear(nacimiento, "%Y-%m-%d %H:%M:%S") << "\n";
    std::cout << "  Anios transcurridos: " << anios << "\n";

    std::cout << "\n=== Reto extra: 10 formatos ===\n";
    const char* patrones[][2] = {
        {"Dia/Mes/Anio", "%d/%m/%Y"}, {"ISO", "%Y-%m-%d"},
        {"Hora:Min:Seg", "%H:%M:%S"}, {"Dia del anio", "%j"},
        {"Dia de la semana", "%A"}, {"Nombre del mes", "%B"},
        {"Semana del anio", "%U"}, {"Fecha completa", "%c"},
        {"12h AM/PM", "%I:%M %p"}, {"Largo", "%A %d %B %Y %H:%M"},
    };
    for (auto& p : patrones)
        std::cout << "  " << p[0] << ": " << formatear(nacimiento, p[1]) << "\n";
    return 0;
}
