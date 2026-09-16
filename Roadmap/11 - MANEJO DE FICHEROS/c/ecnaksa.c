/*
 * #11 - MANEJO DE FICHEROS (C)
 *
 * =========================== TEORÍA ===========================
 * C usa <stdio.h>: fopen(ruta, modo) devuelve un FILE*. Modos: "r" leer,
 * "w" escribir, "a" añadir. Siempre hay que fclose() al terminar. remove()
 * borra un fichero. fgets/fscanf leen; fprintf escribe.
 *
 * DIFICULTAD EXTRA: gestión de ventas en un .txt.
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>
#include <string.h>

int main(void) {
    const char *usuario = "ecnaksa.txt";
    printf("=== Fichero basico ===\n");
    FILE *f = fopen(usuario, "w");
    fprintf(f, "Nombre: ecnaksa\nEdad: 30\nLenguaje favorito: C\n");
    fclose(f);

    f = fopen(usuario, "r");
    char linea[128];
    while (fgets(linea, sizeof linea, f)) fputs(linea, stdout);
    fclose(f);
    remove(usuario);
    printf("Fichero borrado.\n");

    printf("\n=== Reto extra: ventas (demo) ===\n");
    const char *ventas = "ventas.txt";
    f = fopen(ventas, "w");
    fprintf(f, "Teclado,3,25.0\nRaton,5,12.5\nTeclado,2,25.0\n");
    fclose(f);

    f = fopen(ventas, "r");
    char nombre[32]; int cantidad; double precio;
    double total = 0, totalTeclado = 0; int n = 0;
    while (fscanf(f, " %31[^,],%d,%lf", nombre, &cantidad, &precio) == 3) {
        total += cantidad * precio;
        if (strcmp(nombre, "Teclado") == 0) totalTeclado += cantidad * precio;
        n++;
    }
    fclose(f);
    printf("  Productos leidos: %d\n", n);
    printf("  Total 'Teclado': %.2f EUR\n", totalTeclado);
    printf("  Total ventas:    %.2f EUR\n", total);
    remove(ventas);
    printf("  Fichero borrado.\n");
    return 0;
}
