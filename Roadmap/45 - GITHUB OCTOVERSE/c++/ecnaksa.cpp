/*
 * #45 - GITHUB OCTOVERSE (informe de usuario) (C++)
 *
 * =========================== TEORÍA ===========================
 * Consumo de la API pública de GitHub con 'curl' vía popen. Con /users/{login}
 * y /users/{login}/repos se calculan métricas: repos, seguidores, stars, forks
 * y lenguaje más usado. Con la variable GITHUB_TOKEN sube el límite de
 * peticiones (opcional).
 *
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <string>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <array>

static std::string run(const std::string& cmd) {
    std::string out; std::array<char, 8192> buf{};
    FILE* p = popen(cmd.c_str(), "r");
    if (!p) return "";
    size_t n; while ((n = fread(buf.data(), 1, buf.size(), p)) > 0) out.append(buf.data(), n);
    pclose(p);
    return out;
}

static std::string autoriza() {
    const char* t = std::getenv("GITHUB_TOKEN");
    return t ? " -H 'Authorization: Bearer " + std::string(t) + "'" : "";
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
    std::string login = "mouredev";
    std::string base = "curl -s -H 'User-Agent: roadmap-ecnaksa'" + autoriza();
    std::string usuario = run(base + " https://api.github.com/users/" + login);
    if (usuario.find("\"login\"") == std::string::npos) {
        std::cout << "No se pudo obtener el usuario (limite de la API o sin conexion).\n";
        return 0;
    }
    std::string repos = run(base + " 'https://api.github.com/users/" + login + "/repos?per_page=100'");

    // Contar stars, forks y lenguajes
    long stars = 0, forks = 0;
    std::map<std::string, int> lenguajes;
    size_t pos = 0;
    const std::string ms = "\"stargazers_count\":";
    while ((pos = repos.find(ms, pos)) != std::string::npos) { pos += ms.size(); stars += std::atol(repos.c_str() + pos); }
    pos = 0; const std::string mf = "\"forks_count\":";
    while ((pos = repos.find(mf, pos)) != std::string::npos) { pos += mf.size(); forks += std::atol(repos.c_str() + pos); }
    pos = 0; const std::string ml = "\"language\":\"";
    while ((pos = repos.find(ml, pos)) != std::string::npos) {
        pos += ml.size();
        lenguajes[repos.substr(pos, repos.find('"', pos) - pos)]++;
    }
    std::string top = "-"; int maxN = 0;
    for (auto& [l, n] : lenguajes) if (n > maxN) { maxN = n; top = l; }

    std::cout << "===== INFORME OCTOVERSE: @" << login << " =====\n";
    std::cout << "  1. Lenguaje mas usado:    " << top << "\n";
    std::cout << "  2. Repositorios publicos: " << campo(usuario, "public_repos") << "\n";
    std::cout << "  3. Seguidores/Seguidos:   " << campo(usuario, "followers") << " / " << campo(usuario, "following") << "\n";
    std::cout << "  4. Stars totales:         " << stars << "\n";
    std::cout << "  5. Forks totales:         " << forks << "\n";
    return 0;
}
