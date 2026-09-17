/*
 * #46 - X VS BLUESKY (simulador de red social) (C++)
 *
 * =========================== TEORÍA ===========================
 * Modelado de dominio: usuarios (con a quién siguen) y posts (texto de máx 200
 * caracteres, fecha e id únicos). Feeds ordenados por fecha. Se controlan
 * duplicados y acciones no permitidas.
 *
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

const int MAX_TEXTO = 200;

struct Post { int id; std::string autor, texto; int orden; std::set<std::string> likes; };
struct Usuario { std::string id, nombre; std::set<std::string> siguiendo; };

class Red {
    std::map<std::string, Usuario> usuarios;
    std::vector<Post> posts;
    int nextId = 1, reloj = 0;
public:
    std::string registrar(const std::string& id, const std::string& nombre) {
        if (usuarios.count(id)) return "[!] '" + id + "' ya existe";
        usuarios[id] = {id, nombre, {}};
        return "Registrado " + nombre + " (@" + id + ")";
    }
    std::string seguir(const std::string& a, const std::string& b) {
        if (!usuarios.count(a) || !usuarios.count(b)) return "[!] usuario inexistente";
        if (a == b) return "[!] no puedes seguirte a ti mismo";
        if (!usuarios[a].siguiendo.insert(b).second) return "[!] ya lo sigues";
        return "@" + a + " ahora sigue a @" + b;
    }
    std::string publicar(const std::string& autor, const std::string& texto) {
        if (!usuarios.count(autor)) return "[!] usuario inexistente";
        if ((int)texto.size() > MAX_TEXTO) return "[!] el texto supera los 200 caracteres";
        posts.push_back({nextId, autor, texto, ++reloj, {}});
        return "Post #" + std::to_string(nextId++) + " publicado por @" + autor;
    }
    std::string like(int id, const std::string& usuario) {
        for (auto& p : posts) if (p.id == id) {
            if (!p.likes.insert(usuario).second) return "[!] ya habias dado like";
            return "@" + usuario + " dio like al post #" + std::to_string(id);
        }
        return "[!] post inexistente";
    }
    void feed(const std::string& id, bool deSeguidos) {
        std::vector<Post> sel;
        for (auto& p : posts) {
            bool ok = deSeguidos ? usuarios[id].siguiendo.count(p.autor) : (p.autor == id);
            if (ok) sel.push_back(p);
        }
        std::sort(sel.begin(), sel.end(), [](auto& a, auto& b) { return a.orden > b.orden; });
        int n = 0;
        for (auto& p : sel) {
            if (n++ >= 10) break;
            std::cout << "    [@" << p.autor << "] " << usuarios[p.autor].nombre << ": \""
                      << p.texto << "\" - " << p.likes.size() << " likes\n";
        }
    }
};

int main() {
    Red red;
    std::cout << "=== Simulador de red social ===\n";
    std::cout << "  " << red.registrar("ecnaksa", "ecnaksa") << "\n";
    std::cout << "  " << red.registrar("mouredev", "Brais Moure") << "\n";
    std::cout << "  " << red.registrar("mouredev", "Duplicado") << "\n";
    std::cout << "  " << red.seguir("ecnaksa", "mouredev") << "\n";
    std::cout << "  " << red.seguir("ecnaksa", "mouredev") << "\n";
    std::cout << "  " << red.publicar("mouredev", "Nuevo reto del roadmap!") << "\n";
    std::cout << "  " << red.publicar("mouredev", "mouredev pro ya esta aqui") << "\n";
    std::cout << "  " << red.publicar("ecnaksa", "Resolviendo el reto #46") << "\n";
    std::cout << "  " << red.publicar("ecnaksa", std::string(201, 'x')) << "\n";
    std::cout << "  " << red.like(1, "ecnaksa") << "\n";
    std::cout << "  " << red.like(1, "ecnaksa") << "\n";

    std::cout << "\n  Feed de @ecnaksa (sus posts):\n";
    red.feed("ecnaksa", false);
    std::cout << "  Feed de @ecnaksa (de quienes sigue):\n";
    red.feed("ecnaksa", true);
    return 0;
}
