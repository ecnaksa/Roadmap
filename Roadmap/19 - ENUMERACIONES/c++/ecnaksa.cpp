/*
 * #19 - ENUMERACIONES (C++)
 *
 * =========================== TEORÍA ===========================
 * Un enum agrupa constantes con nombre. C++ recomienda 'enum class' (enum con
 * ámbito y tipado fuerte): sus valores no se convierten implícitamente a int
 * y se acceden con Ambito::Valor, evitando colisiones de nombres.
 *
 * DIFICULTAD EXTRA: gestión de estado de pedidos.
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <string>
#include <array>

enum class Dia { Lunes = 1, Martes, Miercoles, Jueves, Viernes, Sabado, Domingo };

std::string nombreDia(int n) {
    static const std::array<std::string, 7> nombres = {
        "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado", "Domingo"};
    if (n < 1 || n > 7) return "Dia no valido";
    return nombres[n - 1];
}

// --- Reto extra ---
enum class Estado { Pendiente, Enviado, Entregado, Cancelado };

class Pedido {
    int id;
    Estado estado = Estado::Pendiente;
public:
    explicit Pedido(int i) : id(i) {}
    void enviar() {
        if (estado == Estado::Pendiente) estado = Estado::Enviado;
        else std::cout << "  [!] No se puede enviar\n";
    }
    void entregar() {
        if (estado == Estado::Enviado) estado = Estado::Entregado;
        else std::cout << "  [!] No se puede entregar si no esta enviado\n";
    }
    void cancelar() {
        if (estado == Estado::Pendiente || estado == Estado::Enviado) estado = Estado::Cancelado;
        else std::cout << "  [!] No se puede cancelar\n";
    }
    std::string describir() const {
        switch (estado) {
            case Estado::Pendiente: return "Pedido #" + std::to_string(id) + " pendiente";
            case Estado::Enviado:   return "Pedido #" + std::to_string(id) + " enviado";
            case Estado::Entregado: return "Pedido #" + std::to_string(id) + " entregado";
            default:                return "Pedido #" + std::to_string(id) + " cancelado";
        }
    }
};

int main() {
    std::cout << "=== Dias de la semana ===\n";
    for (int n : {1, 5, 7, 9}) std::cout << "  " << n << " -> " << nombreDia(n) << "\n";

    std::cout << "\n=== Reto extra: pedidos ===\n";
    Pedido p1(1);
    std::cout << "  " << p1.describir() << "\n";
    p1.enviar();  std::cout << "  " << p1.describir() << "\n";
    p1.entregar(); std::cout << "  " << p1.describir() << "\n";

    Pedido p2(2);
    p2.entregar();  // invalido
    p2.cancelar();
    std::cout << "  " << p2.describir() << "\n";
    return 0;
}
