/*
 * #26 - SOLID: SRP (C++)
 *
 * =========================== TEORÍA ===========================
 * SRP: "una clase debe tener una única razón para cambiar". Cada clase asume
 * una sola responsabilidad. Separar libros, usuarios y préstamos en clases
 * distintas reduce el acoplamiento.
 *
 * DIFICULTAD EXTRA: sistema de biblioteca refactorizado según SRP.
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <string>
#include <map>
#include <vector>

struct Libro { std::string titulo, autor; int copias; };
struct Usuario { std::string nombre, id, email; };

// Responsabilidad 1: almacenar libros
class RepositorioLibros {
    std::map<std::string, Libro> libros;
public:
    void agregar(const Libro& l) { libros[l.titulo] = l; }
    Libro* obtener(const std::string& t) { auto it = libros.find(t); return it == libros.end() ? nullptr : &it->second; }
};

// Responsabilidad 2: almacenar usuarios
class RepositorioUsuarios {
    std::map<std::string, Usuario> usuarios;
public:
    void agregar(const Usuario& u) { usuarios[u.id] = u; }
    Usuario* obtener(const std::string& id) { auto it = usuarios.find(id); return it == usuarios.end() ? nullptr : &it->second; }
};

// Responsabilidad 3: gestionar préstamos
class GestorPrestamos {
    RepositorioLibros& libros;
    RepositorioUsuarios& usuarios;
public:
    GestorPrestamos(RepositorioLibros& l, RepositorioUsuarios& u) : libros(l), usuarios(u) {}
    std::string prestar(const std::string& titulo, const std::string& id) {
        Libro* l = libros.obtener(titulo);
        Usuario* u = usuarios.obtener(id);
        if (!l || !u) return "Libro o usuario no encontrado";
        if (l->copias <= 0) return "No quedan copias";
        l->copias--;
        return "'" + titulo + "' prestado a " + u->nombre;
    }
};

int main() {
    std::cout << "=== SRP: responsabilidades separadas ===\n";
    RepositorioLibros libros;
    RepositorioUsuarios usuarios;
    libros.agregar({"Clean Code", "R. Martin", 2});
    usuarios.agregar({"Ana", "U1", "ana@mail.com"});

    GestorPrestamos gestor(libros, usuarios);
    std::cout << "  " << gestor.prestar("Clean Code", "U1") << "\n";
    std::cout << "  " << gestor.prestar("Clean Code", "U1") << "\n";
    std::cout << "  " << gestor.prestar("Clean Code", "U1") << " (sin copias)\n";
    return 0;
}
