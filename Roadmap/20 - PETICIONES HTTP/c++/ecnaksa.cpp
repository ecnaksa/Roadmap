/*
 * #20 - PETICIONES HTTP (C++)
 *
 * =========================== TEORÍA ===========================
 * La librería estándar de C++ no incluye cliente HTTP (se suelen usar libcurl
 * o cpp-httplib). Aquí, sin dependencias, invocamos el binario 'curl' con
 * popen() y capturamos su salida. La respuesta JSON se parsea manualmente.
 *
 * DIFICULTAD EXTRA: cliente de la PokéAPI.
 * Requiere el comando 'curl' y conexión a internet.
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <string>
#include <cstdio>
#include <array>

static std::string httpGet(const std::string& url) {
    std::string cmd = "curl -s --max-time 15 '" + url + "'";
    std::string salida;
    std::array<char, 4096> buffer{};
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) return "";
    size_t n;
    while ((n = fread(buffer.data(), 1, buffer.size(), pipe)) > 0)
        salida.append(buffer.data(), n);
    pclose(pipe);
    return salida;
}

// Extrae el valor de "clave":"valor" (cadena) o "clave":numero
static std::string campo(const std::string& json, const std::string& clave) {
    auto pos = json.find("\"" + clave + "\"");
    if (pos == std::string::npos) return "";
    pos = json.find(':', pos) + 1;
    while (pos < json.size() && (json[pos] == ' ' || json[pos] == '"')) ++pos;
    auto fin = pos;
    while (fin < json.size() && json[fin] != '"' && json[fin] != ',' && json[fin] != '}') ++fin;
    return json.substr(pos, fin - pos);
}

int main() {
    std::cout << "=== Peticion HTTP basica ===\n";
    std::string web = httpGet("https://example.com");
    if (web.empty()) std::cout << "  (sin conexion o curl no disponible)\n";
    else std::cout << "  Recibidos " << web.size() << " bytes. Inicio: "
                   << web.substr(0, 60) << "...\n";

    std::cout << "\n=== Reto extra: PokeAPI ===\n";
    std::string json = httpGet("https://pokeapi.co/api/v2/pokemon/pikachu");
    if (json.empty() || json.find("\"name\"") == std::string::npos) {
        std::cout << "  No se pudo obtener el Pokemon (sin conexion o no encontrado).\n";
        return 0;
    }
    std::cout << "  Nombre: " << campo(json, "name") << "\n";
    std::cout << "  Id:     " << campo(json, "id") << "\n";
    std::cout << "  Peso:   " << campo(json, "weight") << " (hectogramos)\n";
    std::cout << "  Altura: " << campo(json, "height") << " (decimetros)\n";

    std::cout << "  Tipos:  ";
    size_t pos = 0;
    const std::string marca = "\"type\":{\"name\":\"";
    while ((pos = json.find(marca, pos)) != std::string::npos) {
        pos += marca.size();
        std::cout << json.substr(pos, json.find('"', pos) - pos) << " ";
    }
    std::cout << std::endl;
    return 0;
}
