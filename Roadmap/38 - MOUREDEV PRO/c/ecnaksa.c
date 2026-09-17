/*
 * #38 - MOUREDEV PRO (sorteo desde CSV) (C)
 *
 * =========================== TEORÍA ===========================
 * Lectura de CSV con fscanf/fgets: se salta la cabecera, se filtran los
 * "activo" y se eligen 3 ganadores distintos barajando (Fisher-Yates) y
 * tomando los 3 primeros.
 *
 * NOTA: el .csv no se sube; se genera y se borra.
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { char id[8]; char email[48]; } Registro;

int main(void) {
    const char *ruta = "suscriptores.csv";
    FILE *f = fopen(ruta, "w");
    fprintf(f, "id,email,status\n");
    for (int i = 1; i <= 10; ++i)
        fprintf(f, "%d,user%d@test.com,%s\n", i, i, (i % 3) ? "activo" : "inactivo");
    fclose(f);

    Registro activos[16]; int n = 0;
    f = fopen(ruta, "r");
    char linea[128];
    fgets(linea, sizeof linea, f);  /* cabecera */
    while (fgets(linea, sizeof linea, f)) {
        char id[8], email[48], status[16];
        if (sscanf(linea, "%7[^,],%47[^,],%15[^\n]", id, email, status) == 3 &&
            strcmp(status, "activo") == 0) {
            strcpy(activos[n].id, id); strcpy(activos[n].email, email); n++;
        }
    }
    fclose(f);

    printf("=== Sorteo mouredev pro ===\n");
    const char *premios[] = {"Suscripcion", "Descuento", "Libro"};
    if (n < 3) printf("  No hay suficientes activos.\n");
    else {
        srand(38);
        for (int i = n - 1; i > 0; --i) {  /* barajar */
            int j = rand() % (i + 1);
            Registro t = activos[i]; activos[i] = activos[j]; activos[j] = t;
        }
        for (int i = 0; i < 3; ++i)
            printf("  %s -> id %s  %s\n", premios[i], activos[i].id, activos[i].email);
    }
    remove(ruta);
    printf("  Fichero de datos borrado.\n");
    return 0;
}
