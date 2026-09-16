/*
 * #12 - JSON Y XML (C)
 *
 * =========================== TEORÍA ===========================
 * C no incluye soporte para JSON ni XML (en la práctica se usan librerías como
 * cJSON o libxml2). Aquí escribimos ambos formatos con fprintf y los leemos de
 * vuelta con parseo manual (strstr) hacia un struct común.
 *
 * DIFICULTAD EXTRA: leer JSON y XML a un mismo struct.
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char nombre[64];
    int edad;
    char fecha[16];
} Persona;

/* Copia en 'out' el texto entre 'abre' y 'cierra' hallados en 'src'. */
static void entre(const char *src, const char *abre, const char *cierra, char *out) {
    const char *a = strstr(src, abre);
    if (!a) { out[0] = '\0'; return; }
    a += strlen(abre);
    const char *b = strstr(a, cierra);
    size_t len = b ? (size_t)(b - a) : strlen(a);
    strncpy(out, a, len);
    out[len] = '\0';
}

int main(void) {
    Persona original = {"ecnaksa", 30, "1994-05-12"};
    const char *langs[] = {"C", "Python", "Rust"};

    /* Escribir JSON */
    FILE *f = fopen("datos.json", "w");
    fprintf(f, "{\n  \"nombre\": \"%s\",\n  \"edad\": %d,\n  \"fecha_nacimiento\": \"%s\",\n  \"lenguajes\": [",
            original.nombre, original.edad, original.fecha);
    for (int i = 0; i < 3; ++i) fprintf(f, "\"%s\"%s", langs[i], i < 2 ? ", " : "");
    fprintf(f, "]\n}\n");
    fclose(f);

    /* Escribir XML */
    f = fopen("datos.xml", "w");
    fprintf(f, "<persona>\n  <nombre>%s</nombre>\n  <edad>%d</edad>\n  <fecha_nacimiento>%s</fecha_nacimiento>\n",
            original.nombre, original.edad, original.fecha);
    fprintf(f, "  <lenguajes>\n");
    for (int i = 0; i < 3; ++i) fprintf(f, "    <lenguaje>%s</lenguaje>\n", langs[i]);
    fprintf(f, "  </lenguajes>\n</persona>\n");
    fclose(f);

    /* Mostrar */
    printf("=== Contenido XML ===\n");
    f = fopen("datos.xml", "r");
    char linea[128];
    while (fgets(linea, sizeof linea, f)) fputs(linea, stdout);
    fclose(f);

    /* Reto extra: leer XML a struct */
    printf("\n=== Reto extra: leer XML a struct ===\n");
    f = fopen("datos.xml", "r");
    char buffer[1024]; size_t n = fread(buffer, 1, sizeof(buffer) - 1, f); buffer[n] = '\0';
    fclose(f);

    Persona leido; char edadStr[16];
    entre(buffer, "<nombre>", "</nombre>", leido.nombre);
    entre(buffer, "<edad>", "</edad>", edadStr); leido.edad = atoi(edadStr);
    entre(buffer, "<fecha_nacimiento>", "</fecha_nacimiento>", leido.fecha);
    printf("  nombre=%s edad=%d fecha=%s\n", leido.nombre, leido.edad, leido.fecha);

    remove("datos.json");
    remove("datos.xml");
    printf("  Ficheros borrados.\n");
    return 0;
}
