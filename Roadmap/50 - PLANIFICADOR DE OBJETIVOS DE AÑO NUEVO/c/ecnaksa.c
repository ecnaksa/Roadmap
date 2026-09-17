/*
 * #50 - PLANIFICADOR DE OBJETIVOS DE AÑO NUEVO (C)
 *
 * =========================== TEORÍA ===========================
 * Lógica + informe + escritura de ficheros. Cada objetivo reparte su cantidad
 * entre los meses de su plazo; se genera una vista mes a mes y se exporta a un
 * .txt (que no se sube). Escribimos a la vez por pantalla y al fichero.
 *
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>
#include <string.h>

static const char *MESES[] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
    "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};

typedef struct { char meta[32]; char unidades[16]; int cantidad, plazo; } Objetivo;

/* Escribe una línea en pantalla y en el fichero */
static void doble(FILE *f, const char *linea) {
    fputs(linea, stdout);
    fputs(linea, f);
}

int main(void) {
    Objetivo objetivos[] = {
        {"Leer libros", "libros", 12, 12},
        {"Estudiar Git", "curso", 1, 1},
        {"Correr", "km", 300, 6},
    };
    int n = 3, meses = 0;
    for (int i = 0; i < n; ++i) if (objetivos[i].plazo > meses) meses = objetivos[i].plazo;

    printf("=== Planificador de objetivos (demo) ===\n");
    FILE *f = fopen("propositos.txt", "w");
    doble(f, "=== PLAN DE OBJETIVOS DE ANIO NUEVO ===\n");
    char linea[128];
    for (int m = 0; m < meses; ++m) {
        snprintf(linea, sizeof linea, "\n%s:\n", MESES[m]);
        doble(f, linea);
        int idx = 1;
        for (int i = 0; i < n; ++i)
            if (m < objetivos[i].plazo) {
                double porMes = (double)objetivos[i].cantidad / objetivos[i].plazo;
                if (porMes == (long)porMes)
                    snprintf(linea, sizeof linea, "[ ] %d. %s (%ld %s/mes). Total: %d.\n",
                             idx++, objetivos[i].meta, (long)porMes, objetivos[i].unidades, objetivos[i].cantidad);
                else
                    snprintf(linea, sizeof linea, "[ ] %d. %s (%.2f %s/mes). Total: %d.\n",
                             idx++, objetivos[i].meta, porMes, objetivos[i].unidades, objetivos[i].cantidad);
                doble(f, linea);
            }
    }
    fclose(f);

    printf("\nPlan exportado a 'propositos.txt'\n");
    remove("propositos.txt");
    printf("(fichero borrado tras la demo)\n");
    return 0;
}
