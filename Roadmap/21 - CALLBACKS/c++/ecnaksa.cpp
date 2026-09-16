/*
 * #21 - CALLBACKS (C++)
 *
 * =========================== TEORÍA ===========================
 * Un CALLBACK es una función que se pasa a otra para ser invocada más tarde.
 * En C++ se representan con punteros a función, functores o, de forma más
 * flexible, std::function (que admite lambdas con captura).
 *
 * DIFICULTAD EXTRA: simulador de pedidos de restaurante con callbacks.
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <functional>
#include <vector>
#include <string>

void procesar(const std::vector<int>& datos, const std::function<void(int)>& cb) {
    for (int x : datos) cb(x);
}

void procesarPedido(const std::string& plato,
                    const std::function<void(const std::string&)>& onConfirmado,
                    const std::function<void(const std::string&)>& onListo,
                    const std::function<void(const std::string&)>& onEntregado) {
    onConfirmado(plato);
    onListo(plato);
    onEntregado(plato);
}

int main() {
    std::cout << "=== Callback simple ===\n";
    procesar({1, 2, 3}, [](int n) { std::cout << "  procesando " << n << " -> " << n * n << "\n"; });

    std::cout << "\n=== Reto extra: pedidos de restaurante ===\n";
    procesarPedido(
        "Ramen",
        [](const std::string& p) { std::cout << "  [OK] confirmado: " << p << "\n"; },
        [](const std::string& p) { std::cout << "  '" << p << "' esta listo\n"; },
        [](const std::string& p) { std::cout << "  '" << p << "' entregado. Buen provecho!\n"; });
    return 0;
}
