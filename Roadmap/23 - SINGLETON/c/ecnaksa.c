/*
 * #23 - SINGLETON (C)
 *
 * =========================== TEORÍA ===========================
 * En C el SINGLETON se logra con una variable STATIC a nivel de fichero (única
 * y con vida durante todo el programa) y una función que da acceso a su
 * dirección. Al ser static, no es visible fuera del fichero: se accede solo a
 * través de la función, imitando la instancia única.
 *
 * DIFICULTAD EXTRA: sesión de usuario única.
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>
#include <string.h>

typedef struct {
    int activo;
    int id;
    char username[32];
    char email[64];
} Sesion;

/* Devuelve siempre la misma instancia (static local) */
Sesion *sesion_instancia(void) {
    static Sesion unica = {0};
    return &unica;
}

void sesion_iniciar(int id, const char *username, const char *email) {
    Sesion *s = sesion_instancia();
    s->activo = 1;
    s->id = id;
    strcpy(s->username, username);
    strcpy(s->email, email);
}

void sesion_mostrar(void) {
    Sesion *s = sesion_instancia();
    if (s->activo) printf("  Usuario: [%d] %s (%s)\n", s->id, s->username, s->email);
    else printf("  (sin sesion)\n");
}

void sesion_cerrar(void) { sesion_instancia()->activo = 0; }

int main(void) {
    printf("=== Singleton: sesion de usuario ===\n");
    Sesion *s1 = sesion_instancia();
    sesion_iniciar(1, "ecnaksa", "hola@ecnaksa.dev");

    Sesion *s2 = sesion_instancia();  /* misma instancia */
    printf("  s1 y s2 son el mismo objeto? %d\n", s1 == s2);
    sesion_mostrar();

    sesion_cerrar();
    printf("  Tras cerrar, s1 ve:\n");
    sesion_mostrar();
    return 0;
}
