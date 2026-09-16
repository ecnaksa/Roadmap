/*
 * #18 - CONJUNTOS (C++)
 *
 * =========================== TEORÍA ===========================
 * El ejercicio principal pide operaciones posicionales -> std::vector.
 * El reto extra usa operaciones matemáticas de conjuntos: <algorithm> ofrece
 * set_union, set_intersection, set_difference y set_symmetric_difference
 * (requieren rangos ordenados). std::set también evita duplicados.
 *
 * DIFICULTAD EXTRA: unión, intersección, diferencia y diferencia simétrica.
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

static void imprimir(const std::string& etq, const std::vector<int>& v) {
    std::cout << "  " << etq;
    for (int x : v) std::cout << x << " ";
    std::cout << "\n";
}

int main() {
    std::cout << "=== Operaciones posicionales (vector) ===\n";
    std::vector<int> d = {1, 2, 3};
    d.push_back(4);                     // final
    d.insert(d.begin(), 0);            // principio
    d.insert(d.end(), {5, 6});         // varios al final
    d.insert(d.begin() + 2, {10, 11}); // varios en posición
    d.erase(d.begin() + 2);            // borrar posición
    d[0] = 99;                          // actualizar
    imprimir("estado: ", d);
    std::cout << "  contiene 99? " << (std::find(d.begin(), d.end(), 99) != d.end()) << "\n";
    d.clear();
    std::cout << "  tras clear, tam=" << d.size() << "\n";

    std::cout << "\n=== Reto extra: operaciones de conjuntos ===\n";
    std::set<int> a = {1, 2, 3, 4}, b = {3, 4, 5, 6};
    std::vector<int> res;
    std::set_union(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(res));
    imprimir("union:        ", res); res.clear();
    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(res));
    imprimir("interseccion: ", res); res.clear();
    std::set_difference(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(res));
    imprimir("diferencia:   ", res); res.clear();
    std::set_symmetric_difference(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(res));
    imprimir("dif. simetrica: ", res);
    return 0;
}
