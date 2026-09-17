/*
 * #41 - CAMISETA.RAR (compresión de archivos) (C++)
 *
 * =========================== TEORÍA ===========================
 * La compresión reduce el tamaño de los datos. Usamos la librería zlib (la
 * misma de gzip): gzopen/gzwrite crean un fichero .gz comprimido. Es la forma
 * estándar de comprimir en C/C++ sin reinventar el algoritmo.
 *
 * NOTA: ni el original ni el comprimido se suben; se generan y se borran.
 * Compilar: g++ ecnaksa.cpp -o ecnaksa -lz
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include <zlib.h>

int main() {
    const std::string origen = "camiseta.txt";
    const std::string destino = "camiseta.txt.gz";

    // Crear un fichero con contenido repetitivo (comprime muy bien)
    {
        std::ofstream f(origen);
        for (int i = 0; i < 500; ++i) f << "MoureDev roadmap de retos de programacion\n";
    }

    // Leer el original
    std::ifstream in(origen, std::ios::binary);
    std::vector<char> datos((std::istreambuf_iterator<char>(in)), {});
    long tamOriginal = datos.size();

    // Comprimir con zlib (gzip)
    gzFile gz = gzopen(destino.c_str(), "wb9");   // nivel 9 = máxima compresión
    gzwrite(gz, datos.data(), datos.size());
    gzclose(gz);

    std::ifstream cmp(destino, std::ios::binary | std::ios::ate);
    long tamComprimido = cmp.tellg();

    std::cout << "=== camiseta.rar (con gzip/zlib) ===\n";
    std::cout << "  Original:   " << tamOriginal << " bytes\n";
    std::cout << "  Comprimido: " << tamComprimido << " bytes\n";
    std::cout << "  Ratio:      " << (100.0 * tamComprimido / tamOriginal) << "% del original\n";

    std::remove(origen.c_str());
    std::remove(destino.c_str());
    std::cout << "  Ficheros temporales borrados.\n";
    return 0;
}
