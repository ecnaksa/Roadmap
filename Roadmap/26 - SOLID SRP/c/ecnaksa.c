/*
 * #26 - SOLID: SRP (C)
 *
 * =========================== TEORÍA ===========================
 * SRP: "una unidad de código, una responsabilidad". En C se aplica separando
 * las funciones por módulo/tema: unas funciones gestionan libros, otras
 * usuarios y otras préstamos, cada grupo operando sobre su propia estructura.
 *
 * DIFICULTAD EXTRA: biblioteca con responsabilidades separadas.
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>
#include <string.h>

/* Responsabilidad 1: libros */
typedef struct { char titulo[32]; char autor[32]; int copias; } Libro;
Libro *libro_buscar(Libro *libros, int n, const char *titulo) {
    for (int i = 0; i < n; ++i) if (strcmp(libros[i].titulo, titulo) == 0) return &libros[i];
    return NULL;
}

/* Responsabilidad 2: usuarios */
typedef struct { char nombre[32]; char id[8]; } Usuario;
Usuario *usuario_buscar(Usuario *usuarios, int n, const char *id) {
    for (int i = 0; i < n; ++i) if (strcmp(usuarios[i].id, id) == 0) return &usuarios[i];
    return NULL;
}

/* Responsabilidad 3: prestamos */
const char *prestar(Libro *libros, int nl, Usuario *usuarios, int nu,
                    const char *titulo, const char *id) {
    Libro *l = libro_buscar(libros, nl, titulo);
    Usuario *u = usuario_buscar(usuarios, nu, id);
    if (!l || !u) return "Libro o usuario no encontrado";
    if (l->copias <= 0) return "No quedan copias";
    l->copias--;
    return "prestado correctamente";
}

int main(void) {
    printf("=== SRP: responsabilidades separadas ===\n");
    Libro libros[] = {{"Clean Code", "R. Martin", 2}};
    Usuario usuarios[] = {{"Ana", "U1"}};
    for (int i = 0; i < 3; ++i)
        printf("  intento %d: %s (copias restantes: %d)\n",
               i + 1, prestar(libros, 1, usuarios, 1, "Clean Code", "U1"), libros[0].copias);
    return 0;
}
