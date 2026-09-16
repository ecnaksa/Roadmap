/*
 * #23 - SINGLETON (C++)
 *
 * =========================== TEORÍA ===========================
 * El SINGLETON garantiza una única instancia con acceso global. En C++ la
 * forma idiomática y segura frente a hilos (desde C++11) es el "Meyers
 * Singleton": una variable static local dentro de un método getInstance(),
 * cuyo constructor se ejecuta una sola vez. Se borran copia y asignación.
 *
 * DIFICULTAD EXTRA: sesión de usuario única.
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <string>
#include <optional>

class Sesion {
    struct Usuario { int id; std::string username, nombre, email; };
    std::optional<Usuario> usuario;
    Sesion() = default;
public:
    Sesion(const Sesion&) = delete;
    Sesion& operator=(const Sesion&) = delete;

    static Sesion& instancia() {
        static Sesion s;   // se crea una sola vez
        return s;
    }
    void iniciar(int id, std::string username, std::string nombre, std::string email) {
        usuario = Usuario{id, std::move(username), std::move(nombre), std::move(email)};
    }
    void mostrar() const {
        if (usuario) std::cout << "  Usuario: [" << usuario->id << "] " << usuario->username
                               << " (" << usuario->email << ")\n";
        else std::cout << "  (sin sesion)\n";
    }
    void cerrar() { usuario.reset(); }
};

int main() {
    std::cout << "=== Singleton: sesion de usuario ===\n";
    Sesion& s1 = Sesion::instancia();
    s1.iniciar(1, "ecnaksa", "ecnaksa dev", "hola@ecnaksa.dev");

    Sesion& s2 = Sesion::instancia();   // misma instancia
    std::cout << "  s1 y s2 son el mismo objeto? " << std::boolalpha << (&s1 == &s2) << "\n";
    s2.mostrar();

    s2.cerrar();
    std::cout << "  Tras cerrar en s2, s1 ve:\n";
    s1.mostrar();
    return 0;
}
