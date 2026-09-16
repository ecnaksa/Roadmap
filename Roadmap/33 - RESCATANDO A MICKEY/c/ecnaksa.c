/*
 * #33 - RESCATANDO A MICKEY (C)
 *
 * =========================== TEORÍA ===========================
 * Reto de MATRICES: un laberinto 6x6 como matriz de enteros. La posición de
 * Mickey son dos índices (fila, col); cada movimiento se valida contra los
 * límites y los obstáculos antes de aplicarse.
 * Símbolos: '.' vacío, '#' obstáculo, 'M' Mickey, 'E' salida.
 *
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>
#include <string.h>

int main(void) {
    int plano[6][6] = {
        {0, 0, 0, 1, 0, 0},
        {1, 1, 0, 1, 0, 1},
        {0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 1, 0},
        {1, 1, 0, 1, 0, 0},
    };
    int fila = 0, col = 0, salidaF = 5, salidaC = 5;

    const char *ruta[] = {"derecha", "derecha", "abajo", "abajo", "derecha",
        "derecha", "derecha", "arriba", "abajo", "abajo", "abajo"};
    int nRuta = 11;

    printf("=== Laberinto inicial ('M' Mickey, 'E' salida) ===\n");
    #define DIBUJAR() do { \
        for (int f = 0; f < 6; ++f) { printf("  "); \
            for (int c = 0; c < 6; ++c) { \
                if (f == fila && c == col) putchar('M'); \
                else if (f == salidaF && c == salidaC) putchar('E'); \
                else putchar(plano[f][c] ? '#' : '.'); } \
            putchar('\n'); } } while (0)
    DIBUJAR();

    for (int i = 0; i < nRuta; ++i) {
        int df = 0, dc = 0;
        if (strcmp(ruta[i], "arriba") == 0) df = -1;
        else if (strcmp(ruta[i], "abajo") == 0) df = 1;
        else if (strcmp(ruta[i], "izquierda") == 0) dc = -1;
        else if (strcmp(ruta[i], "derecha") == 0) dc = 1;
        int nf = fila + df, nc = col + dc;
        printf("\n> %s: ", ruta[i]);
        if (nf < 0 || nf >= 6 || nc < 0 || nc >= 6) printf("fuera de limites!\n");
        else if (plano[nf][nc] == 1) printf("hay un obstaculo!\n");
        else { fila = nf; col = nc; printf("ok\n"); }
        DIBUJAR();
        if (fila == salidaF && col == salidaC) { printf("\nMickey ha escapado!\n"); return 0; }
    }
    return 0;
}
