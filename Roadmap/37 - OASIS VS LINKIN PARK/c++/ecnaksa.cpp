/*
 * #37 - OASIS VS LINKIN PARK (API de Spotify) (C++)
 *
 * =========================== TEORÍA ===========================
 * Consumo de la Web API de Spotify con OAuth 2.0 (Client Credentials). Sin
 * librerías externas, usamos 'curl' vía popen: primero pedimos un token con
 * las credenciales y luego consultamos el endpoint de búsqueda de artistas.
 * Las credenciales se leen de variables de entorno (no se suben al repo):
 *   SPOTIFY_CLIENT_ID / SPOTIFY_CLIENT_SECRET
 *
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <array>

static std::string ejecutar(const std::string& cmd) {
    std::string out;
    std::array<char, 4096> buf{};
    FILE* p = popen(cmd.c_str(), "r");
    if (!p) return "";
    size_t n; while ((n = fread(buf.data(), 1, buf.size(), p)) > 0) out.append(buf.data(), n);
    pclose(p);
    return out;
}

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
    const char* id = std::getenv("SPOTIFY_CLIENT_ID");
    const char* secret = std::getenv("SPOTIFY_CLIENT_SECRET");
    std::cout << "=== Oasis vs Linkin Park (Spotify) ===\n";
    if (!id || !secret) {
        std::cout << "Faltan credenciales. Configura SPOTIFY_CLIENT_ID y SPOTIFY_CLIENT_SECRET\n"
                     "(registro en https://developer.spotify.com).\n";
        return 0;
    }
    std::string tokenJson = ejecutar(
        "curl -s -X POST 'https://accounts.spotify.com/api/token' "
        "-d grant_type=client_credentials -u '" + std::string(id) + ":" + secret + "'");
    std::string token = campo(tokenJson, "access_token");
    if (token.empty()) { std::cout << "No se pudo obtener token.\n"; return 0; }

    for (const std::string& banda : {"Oasis", "Linkin Park"}) {
        std::string url = "https://api.spotify.com/v1/search?q=" + banda + "&type=artist&limit=1";
        // sustituir espacios por %20
        for (auto& c : url) if (c == ' ') c = '+';
        std::string json = ejecutar("curl -s '" + url + "' -H 'Authorization: Bearer " + token + "'");
        std::cout << "  " << banda << ": seguidores=" << campo(json, "total")
                  << " popularidad=" << campo(json, "popularity") << "\n";
    }
    return 0;
}
