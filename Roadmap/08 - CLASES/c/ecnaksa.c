/*
 * #08 - CLASES (C)
 *
 * =========================== TEORÍA ===========================
 * C NO tiene clases. El equivalente idiomático es un STRUCT (los datos) junto
 * con FUNCIONES que reciben un puntero a ese struct como primer parámetro
 * (haciendo el papel de 'this'). No hay encapsulación real ni métodos, pero se
 * consigue el mismo objetivo: agrupar estado y comportamiento.
 *
 * DIFICULTAD EXTRA: "clases" Pila y Cola (struct + funciones).
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>
#include <string.h>

#define MAX 100

/* --- "Clase" Persona --- */
typedef struct { char nombre[32]; int edad; } Persona;
void persona_init(Persona *p, const char *nombre, int edad) { strcpy(p->nombre, nombre); p->edad = edad; }
void persona_presentarse(const Persona *p) { printf("  Me llamo %s y tengo %d anios.\n", p->nombre, p->edad); }

/* --- "Clase" Pila --- */
typedef struct { int datos[MAX]; int n; } Pila;
void pila_init(Pila *p) { p->n = 0; }
void pila_apilar(Pila *p, int v) { if (p->n < MAX) p->datos[p->n++] = v; }
int pila_desapilar(Pila *p) { return p->datos[--p->n]; }
void pila_imprimir(const Pila *p) { printf("  Pila: "); for (int i = 0; i < p->n; ++i) printf("%d ", p->datos[i]); printf("\n"); }

/* --- "Clase" Cola --- */
typedef struct { int datos[MAX]; int frente, fin; } Cola;
void cola_init(Cola *c) { c->frente = c->fin = 0; }
void cola_encolar(Cola *c, int v) { if (c->fin < MAX) c->datos[c->fin++] = v; }
int cola_desencolar(Cola *c) { return c->datos[c->frente++]; }
int cola_tam(const Cola *c) { return c->fin - c->frente; }

int main(void) {
    printf("=== 'Clase' Persona ===\n");
    Persona p; persona_init(&p, "ecnaksa", 30);
    persona_presentarse(&p);
    p.edad = 31;
    persona_presentarse(&p);

    printf("\n=== Reto extra: Pila ===\n");
    Pila pila; pila_init(&pila);
    for (int i = 1; i <= 3; ++i) pila_apilar(&pila, i);
    pila_imprimir(&pila);
    printf("  desapilar -> %d (tam=%d)\n", pila_desapilar(&pila), pila.n);

    printf("\n=== Reto extra: Cola ===\n");
    Cola cola; cola_init(&cola);
    for (int i = 1; i <= 3; ++i) cola_encolar(&cola, i);
    printf("  desencolar -> %d (tam=%d)\n", cola_desencolar(&cola), cola_tam(&cola));
    return 0;
}
