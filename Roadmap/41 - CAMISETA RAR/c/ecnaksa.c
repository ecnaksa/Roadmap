/*
 * #41 - CAMISETA.RAR (compresión de archivos) (C)
 *
 * =========================== TEORÍA ===========================
 * La compresión reduce el tamaño de los datos. Usamos zlib (la librería de
 * gzip): gzopen/gzwrite crean un fichero .gz comprimido. Es la forma estándar
 * de comprimir en C sin implementar el algoritmo a mano.
 *
 * NOTA: ni el original ni el comprimido se suben; se generan y se borran.
 * Compilar: gcc ecnaksa.c -o ecnaksa -lz
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>
#include <string.h>
#include <zlib.h>

static long tam_fichero(const char *ruta) {
    FILE *f = fopen(ruta, "rb");
    if (!f) return -1;
    fseek(f, 0, SEEK_END);
    long t = ftell(f);
    fclose(f);
    return t;
}

int main(void) {
    const char *origen = "camiseta.txt";
    const char *destino = "camiseta.txt.gz";

    /* Crear fichero con contenido repetitivo */
    FILE *f = fopen(origen, "w");
    for (int i = 0; i < 500; ++i) fprintf(f, "MoureDev roadmap de retos de programacion\n");
    fclose(f);

    long tamOriginal = tam_fichero(origen);

    /* Comprimir con zlib (gzip) */
    f = fopen(origen, "rb");
    gzFile gz = gzopen(destino, "wb9");   /* nivel 9 = máxima compresión */
    char buffer[8192];
    size_t leidos;
    while ((leidos = fread(buffer, 1, sizeof buffer, f)) > 0)
        gzwrite(gz, buffer, (unsigned)leidos);
    gzclose(gz);
    fclose(f);

    long tamComprimido = tam_fichero(destino);

    printf("=== camiseta.rar (con gzip/zlib) ===\n");
    printf("  Original:   %ld bytes\n", tamOriginal);
    printf("  Comprimido: %ld bytes\n", tamComprimido);
    printf("  Ratio:      %.1f%% del original\n", 100.0 * tamComprimido / tamOriginal);

    remove(origen);
    remove(destino);
    printf("  Ficheros temporales borrados.\n");
    return 0;
}
