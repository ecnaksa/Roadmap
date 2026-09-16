/*
 * #29 - SOLID: ISP (C++)
 *
 * =========================== TEORÍA ===========================
 * ISP: "ningún cliente debe depender de métodos que no usa". Mejor varias
 * interfaces pequeñas que una "gorda". Aquí separamos Impresora, Escaner y Fax;
 * una impresora sencilla implementa solo Impresora, y la multifunción combina
 * las tres por herencia múltiple.
 *
 * DIFICULTAD EXTRA: gestor de impresoras con interfaces segregadas.
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <string>

struct IImpresora { virtual ~IImpresora() = default; virtual std::string imprimir(const std::string&) = 0; };
struct IEscaner   { virtual ~IEscaner() = default;   virtual std::string escanear(const std::string&) = 0; };
struct IFax       { virtual ~IFax() = default;       virtual std::string enviarFax(const std::string&) = 0; };

class ImpresoraBN : public IImpresora {
public:
    std::string imprimir(const std::string& d) override { return "(B/N) imprimiendo '" + d + "'"; }
};

class Multifuncion : public IImpresora, public IEscaner, public IFax {
public:
    std::string imprimir(const std::string& d) override { return "imprimiendo '" + d + "'"; }
    std::string escanear(const std::string& d) override { return "escaneando '" + d + "'"; }
    std::string enviarFax(const std::string& d) override { return "enviando fax '" + d + "'"; }
};

int main() {
    std::cout << "=== ISP: interfaces segregadas ===\n";
    ImpresoraBN bn;
    Multifuncion multi;
    std::cout << "  " << bn.imprimir("carta.txt") << "\n";
    std::cout << "  " << multi.imprimir("informe.pdf") << "\n";
    std::cout << "  " << multi.escanear("dni.jpg") << "\n";
    std::cout << "  " << multi.enviarFax("contrato.pdf") << "\n";

    std::cout << "\n=== Comprobacion ===\n";
    std::cout << "  ImpresoraBN es IEscaner? " << std::boolalpha
              << (dynamic_cast<IEscaner*>(&bn) != nullptr) << " (no arrastra metodos que no usa)\n";
    std::cout << "  Multifuncion es IEscaner? " << (dynamic_cast<IEscaner*>(&multi) != nullptr) << "\n";
    return 0;
}
