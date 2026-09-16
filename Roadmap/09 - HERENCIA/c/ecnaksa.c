/*
 * #09 - HERENCIA (C)
 *
 * =========================== TEORÍA ===========================
 * C NO soporta herencia. Se puede EMULAR con dos técnicas:
 *  1. Composición/embebido: colocar el struct "base" como primer campo del
 *     struct "derivado" (así un puntero al derivado puede tratarse como base).
 *  2. Punteros a función dentro del struct para lograr polimorfismo (cada
 *     "objeto" apunta a su propia implementación).
 * Aquí usamos ambas para imitar Animal -> Perro/Gato.
 *
 * DIFICULTAD EXTRA: jerarquía de empleados (con puntero a función 'rol').
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>
#include <string.h>

/* "Base" Animal con puntero a función (polimorfismo manual) */
typedef struct Animal {
    char nombre[32];
    const char *(*hacerSonido)(void);
} Animal;

const char *sonido_perro(void) { return "Guau!"; }
const char *sonido_gato(void)  { return "Miau!"; }

void animal_describir(const Animal *a) {
    printf("  %s dice: %s\n", a->nombre, a->hacerSonido());
}

/* "Base" Empleado embebida en los "derivados" */
typedef struct { int id; char nombre[32]; const char *rol; } Empleado;
typedef struct { Empleado base; char lenguaje[16]; } Programador;

int main(void) {
    printf("=== Herencia emulada: Animal ===\n");
    Animal toby = {"Toby", sonido_perro};
    Animal michi = {"Michi", sonido_gato};
    animal_describir(&toby);
    animal_describir(&michi);

    printf("\n=== Reto extra: empresa ===\n");
    Programador ana = {{3, "Ana", "Programador (C)"}, "C"};
    Empleado marta = {2, "Marta", "Gerente de Proyectos"};
    /* Un Programador* se puede tratar como Empleado* por el embebido */
    Empleado *lista[] = {(Empleado *)&ana, &marta};
    for (int i = 0; i < 2; ++i)
        printf("  [%d] %s - %s\n", lista[i]->id, lista[i]->nombre, lista[i]->rol);
    return 0;
}
