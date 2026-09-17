/*
 * #40 - FORTNITE RUBIUS CUP (API de Twitch) (C++)
 *
 * =========================== TEORÍA ===========================
 * Consumo de la API de Twitch con OAuth (Client Credentials). Con 'curl' vía
 * popen: se pide un app access token y luego se consultan /helix/users y
 * /helix/channels/followers. Credenciales por variables de entorno (no se
 * suben): TWITCH_CLIENT_ID / TWITCH_CLIENT_SECRET.
 *
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <array>

static std::string ejecutar(const std::string& cmd) {
    std::string out; std::array<char, 4096> buf{};
    FILE* p = popen(cmd.c_str(), "r");
    if (!p) return "";
    size_t n; while ((n = fread(buf.data(), 1, buf.size(), p)) > 0) out.append(buf.data(), n);
    pclose(p);
    return out;
}

static std::string campo(const std::string& j, const std::string& clave) {
    auto pos = j.find("\"" + clave + "\"");
    if (pos == std::string::npos) return "";
    pos = j.find(':', pos) + 1;
    while (pos < j.size() && (j[pos] == ' ' || j[pos] == '"')) ++pos;
    auto fin = pos;
    while (fin < j.size() && j[fin] != '"' && j[fin] != ',' && j[fin] != '}') ++fin;
    return j.substr(pos, fin - pos);
}

int main() {
    const char* id = std::getenv("TWITCH_CLIENT_ID");
    const char* secret = std::getenv("TWITCH_CLIENT_SECRET");
    std::cout << "=== Fortnite Rubius Cup (Twitch) ===\n";
    if (!id || !secret) {
        std::cout << "Faltan credenciales. Configura TWITCH_CLIENT_ID y TWITCH_CLIENT_SECRET\n"
                     "(registro en https://dev.twitch.tv/console).\n";
        return 0;
    }
    std::string tok = ejecutar("curl -s -X POST 'https://id.twitch.tv/oauth2/token' "
        "-d 'client_id=" + std::string(id) + "&client_secret=" + secret +
        "&grant_type=client_credentials'");
    std::string token = campo(tok, "access_token");
    if (token.empty()) { std::cout << "No se pudo obtener token.\n"; return 0; }

    std::vector<std::string> participantes = {"rubius", "auronplay", "ibai", "usuario_inexistente_xyz"};
    std::cout << "Seguidores por canal:\n";
    for (auto& login : participantes) {
        std::string u = ejecutar("curl -s 'https://api.twitch.tv/helix/users?login=" + login +
            "' -H 'Client-Id: " + id + "' -H 'Authorization: Bearer " + token + "'");
        std::string uid = campo(u, "id");
        if (uid.empty()) { std::cout << "  " << login << ": (sin cuenta en Twitch)\n"; continue; }
        std::string fol = ejecutar("curl -s 'https://api.twitch.tv/helix/channels/followers?broadcaster_id=" +
            uid + "' -H 'Client-Id: " + id + "' -H 'Authorization: Bearer " + token + "'");
        std::cout << "  " << login << ": " << campo(fol, "total") << " seguidores, creada "
                  << campo(u, "created_at").substr(0, 10) << "\n";
    }
    return 0;
}
