/*
 * #39 - BATMAN DAY (reto doble) (C)
 *
 * =========================== TEORÍA ===========================
 * RETO 1: cálculo de fechas (tercer sábado de septiembre) con <time.h>.
 * RETO 2: matriz 20x20 con ventana deslizante 3x3 para hallar la zona de mayor
 * amenaza y la distancia Manhattan a la Batcueva (0,0).
 *
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>
#include <time.h>

static int dia_semana(int anio, int mes, int dia) {  /* 0=domingo..6=sabado */
    struct tm t = {0};
    t.tm_year = anio - 1900; t.tm_mon = mes - 1; t.tm_mday = dia;
    mktime(&t);
    return t.tm_wday;
}

int main(void) {
    printf("=== RETO 1: Batman Day hasta el 100 aniversario ===\n");
    const int PRIMER = 1939;
    for (int aniv = 85; aniv <= 100; ++aniv) {
        int anio = PRIMER + aniv, sabados = 0, dia = 0;
        for (int d = 1; d <= 30; ++d)
            if (dia_semana(anio, 9, d) == 6 && ++sabados == 3) { dia = d; break; }
        printf("  %do aniversario (%d): sabado %02d/09/%d\n", aniv, anio, dia, anio);
    }

    printf("\n=== RETO 2: seguridad de la Batcueva ===\n");
    int grid[20][20] = {{0}};
    int sensores[][3] = {{5,5,8},{6,5,7},{5,6,9},{6,6,6},{1,1,2},{18,18,10},{10,10,3},{4,5,4}};
    for (int i = 0; i < 8; ++i) grid[sensores[i][1]][sensores[i][0]] = sensores[i][2];

    int mejor = -1, cx = 0, cy = 0;
    for (int y = 1; y < 19; ++y)
        for (int x = 1; x < 19; ++x) {
            int suma = 0;
            for (int dy = -1; dy <= 1; ++dy)
                for (int dx = -1; dx <= 1; ++dx) suma += grid[y + dy][x + dx];
            if (suma > mejor) { mejor = suma; cx = x; cy = y; }
        }
    printf("  Centro mas amenazado: (%d, %d)\n", cx, cy);
    printf("  Suma de amenazas 3x3: %d\n", mejor);
    printf("  Distancia a la Batcueva: %d\n", cx + cy);
    printf("  Activar protocolo (>20)? %s\n", mejor > 20 ? "SI" : "no");
    return 0;
}
