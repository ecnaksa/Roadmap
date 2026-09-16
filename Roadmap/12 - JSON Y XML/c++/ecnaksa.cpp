/*
 * #12 - JSON Y XML (C++)
 *
 * =========================== TEORÍA ===========================
 * La librería estándar de C++ no incluye parseadores de JSON/XML (en proyectos
 * reales se usan librerías como nlohmann/json o pugixml). Aquí lo hacemos "a
 * mano" con <fstream> y <sstream>: se escribe el formato con la sintaxis
 * correcta y se lee de vuelta a una struct común.
 *
 * DIFICULTAD EXTRA: leer el JSON y el XML a una misma struct.
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>

struct Persona {
    std::string nombre, fecha;
    int edad;
    std::vector<std::string> lenguajes;
};

static void escribirJSON(const std::string& r, const Persona& p) {
    std::ofstream f(r);
    f << "{\n  \"nombre\": \"" << p.nombre << "\",\n  \"edad\": " << p.edad
      << ",\n  \"fecha_nacimiento\": \"" << p.fecha << "\",\n  \"lenguajes\": [";
    for (size_t i = 0; i < p.lenguajes.size(); ++i)
        f << "\"" << p.lenguajes[i] << "\"" << (i + 1 < p.lenguajes.size() ? ", " : "");
    f << "]\n}\n";
}

static void escribirXML(const std::string& r, const Persona& p) {
    std::ofstream f(r);
    f << "<persona>\n  <nombre>" << p.nombre << "</nombre>\n  <edad>" << p.edad
      << "</edad>\n  <fecha_nacimiento>" << p.fecha << "</fecha_nacimiento>\n  <lenguajes>\n";
    for (auto& l : p.lenguajes) f << "    <lenguaje>" << l << "</lenguaje>\n";
    f << "  </lenguajes>\n</persona>\n";
}

// Extrae el texto entre 'abre' y 'cierra' dentro de 'contenido'
static std::string entre(const std::string& c, const std::string& abre, const std::string& cierra) {
    auto a = c.find(abre);
    if (a == std::string::npos) return "";
    a += abre.size();
    auto b = c.find(cierra, a);
    return c.substr(a, b - a);
}

int main() {
    Persona original{"ecnaksa", "1994-05-12", 30, {"C++", "Python", "Rust"}};
    escribirJSON("datos.json", original);
    escribirXML("datos.xml", original);

    std::cout << "=== Contenido JSON ===\n";
    { std::ifstream f("datos.json"); std::cout << f.rdbuf(); }
    std::cout << "\n=== Contenido XML ===\n";
    { std::ifstream f("datos.xml"); std::cout << f.rdbuf(); }

    std::cout << "\n=== Reto extra: leer XML a struct ===\n";
    std::stringstream ss;
    { std::ifstream f("datos.xml"); ss << f.rdbuf(); }
    std::string xml = ss.str();
    Persona leido;
    leido.nombre = entre(xml, "<nombre>", "</nombre>");
    leido.edad = std::stoi(entre(xml, "<edad>", "</edad>"));
    leido.fecha = entre(xml, "<fecha_nacimiento>", "</fecha_nacimiento>");
    std::cout << "  nombre=" << leido.nombre << " edad=" << leido.edad
              << " fecha=" << leido.fecha << "\n";

    std::remove("datos.json");
    std::remove("datos.xml");
    std::cout << "  Ficheros borrados.\n";
    return 0;
}
