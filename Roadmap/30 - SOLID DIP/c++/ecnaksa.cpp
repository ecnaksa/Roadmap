/*
 * #30 - SOLID: DIP (C++)
 *
 * =========================== TEORÍA ===========================
 * DIP: los módulos de alto nivel no dependen de los de bajo nivel; ambos
 * dependen de ABSTRACCIONES. El ServicioNotificaciones no conoce Email, SMS ni
 * Push: solo la interfaz CanalNotificacion, que se le INYECTA. Así se pueden
 * cambiar/añadir canales sin tocarlo.
 *
 * DIFICULTAD EXTRA: sistema de notificaciones (Email, SMS, Push).
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>

struct Canal {
    virtual ~Canal() = default;
    virtual void enviar(const std::string& msg) = 0;
};

struct Email : Canal { void enviar(const std::string& m) override { std::cout << "  EMAIL: " << m << "\n"; } };
struct SMS   : Canal { void enviar(const std::string& m) override { std::cout << "  SMS:   " << m << "\n"; } };
struct Push  : Canal { void enviar(const std::string& m) override { std::cout << "  PUSH:  " << m << "\n"; } };

class ServicioNotificaciones {
    std::vector<std::unique_ptr<Canal>> canales;  // depende de la abstracción
public:
    void agregar(std::unique_ptr<Canal> c) { canales.push_back(std::move(c)); }
    void enviar(const std::string& msg) { for (auto& c : canales) c->enviar(msg); }
};

int main() {
    std::cout << "=== DIP: inyeccion de dependencias ===\n";
    ServicioNotificaciones servicio;
    servicio.agregar(std::make_unique<Email>());
    servicio.agregar(std::make_unique<SMS>());
    servicio.agregar(std::make_unique<Push>());
    servicio.enviar("Nuevo reto disponible!");

    std::cout << "\n  Se cambian/anaden canales sin modificar el servicio -> cumple DIP\n";
    return 0;
}
