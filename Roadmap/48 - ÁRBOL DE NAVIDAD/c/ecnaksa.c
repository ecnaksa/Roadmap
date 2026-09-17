/*
 * #48 - ÁRBOL DE NAVIDAD (C)
 *
 * =========================== TEORÍA ===========================
 * Dibujo por terminal + estado en una matriz. El follaje es un triángulo
 * (fila i -> 2i+1 estrellas). Una matriz 'decor' guarda qué hay en cada celda:
 * 'o' bola, 'L' luz o vacío. La estrella ('@') va en la copa. Las luces se
 * dibujan '+' encendidas o '*' apagadas.
 *
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXH 30

static int altura;
static int estrella = 0, encendidas = 1;
static char decor[MAXH][2 * MAXH];  /* 0, 'o' o 'L' */

/* Rellena filas[],cols[] con las posiciones libres; devuelve cuántas hay. */
static int libres(int *filas, int *cols) {
    int n = 0;
    for (int i = 0; i < altura; ++i)
        for (int c = 0; c < 2 * i + 1; ++c) {
            if (i == 0 && c == 0) continue;         /* copa reservada */
            if (decor[i][c] == 0) { filas[n] = i; cols[n] = c; n++; }
        }
    return n;
}

static int anadir(char tipo, int cuantas) {
    int filas[MAXH * MAXH], cols[MAXH * MAXH];
    int n = libres(filas, cols);
    if (n < cuantas) return 0;
    /* barajar índices */
    for (int i = n - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        int tf = filas[i]; filas[i] = filas[j]; filas[j] = tf;
        int tc = cols[i]; cols[i] = cols[j]; cols[j] = tc;
    }
    for (int i = 0; i < cuantas; ++i) decor[filas[i]][cols[i]] = tipo;
    return 1;
}

static char simbolo(int i, int c) {
    if (i == 0 && c == 0 && estrella) return '@';
    if (decor[i][c] == 'o') return 'o';
    if (decor[i][c] == 'L') return encendidas ? '+' : '*';
    return '*';
}

static void dibujar(void) {
    for (int i = 0; i < altura; ++i) {
        for (int s = 0; s < altura - 1 - i; ++s) putchar(' ');
        for (int c = 0; c < 2 * i + 1; ++c) putchar(simbolo(i, c));
        putchar('\n');
    }
    int sangria = altura - 2 > 0 ? altura - 2 : 0;
    for (int t = 0; t < 2; ++t) {
        for (int s = 0; s < sangria; ++s) putchar(' ');
        printf("|||\n");
    }
}

int main(void) {
    srand(48);
    altura = 7;
    printf("=== Arbol base (altura 7) ===\n");
    dibujar();

    estrella = 1;  printf("\n> Estrella anadida\n");
    printf("> %s\n", anadir('o', 2) ? "2 bolas anadidas" : "[!] sin sitio");
    printf("> %s\n", anadir('L', 3) ? "3 luces anadidas" : "[!] sin sitio");
    printf("> %s\n", anadir('L', 3) ? "3 luces anadidas" : "[!] sin sitio");

    printf("\n=== Arbol decorado ===\n");
    dibujar();

    encendidas = 0;
    printf("\n> Luces apagadas\n=== Con las luces apagadas ===\n");
    dibujar();
    return 0;
}
