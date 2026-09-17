/*
 * #47 - CALENDARIO DE ADVIENTO (C)
 *
 * =========================== TEORÍA ===========================
 * Dibujo por terminal + estado (array de descubiertos). 24 días en 6 columnas;
 * cada celda es 4x3 de asteriscos con el número en el centro. Al descubrir un
 * día, el centro se cubre de asteriscos.
 *
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>

#define COLUMNAS 6
#define DIAS 24

static int descubierto[DIAS + 1];  /* 1..24 */

static void render(void) {
    for (int inicio = 1; inicio <= DIAS; inicio += COLUMNAS) {
        for (int fila = 0; fila < 3; ++fila) {
            for (int d = inicio; d < inicio + COLUMNAS && d <= DIAS; ++d) {
                if (fila == 1 && !descubierto[d]) printf("*%02d*", d);
                else printf("****");
                printf(" ");
            }
            printf("\n");
        }
        printf("\n");
    }
}

static void seleccionar(int dia) {
    if (dia < 1 || dia > DIAS) { printf("[!] el dia debe estar entre 1 y 24\n"); return; }
    if (descubierto[dia]) { printf("[!] el dia %d ya estaba descubierto\n", dia); return; }
    descubierto[dia] = 1;
    printf("Has abierto el dia %d!\n", dia);
}

int main(void) {
    printf("=== Calendario de adviento (inicial) ===\n");
    render();
    int dias[] = {1, 5, 24, 5};
    for (int i = 0; i < 4; ++i) seleccionar(dias[i]);
    printf("\n=== Tras descubrir 1, 5 y 24 ===\n");
    render();
    return 0;
}
