/*
 * #42 - TORNEO DRAGON BALL (C)
 *
 * =========================== TEORÍA ===========================
 * Simulación de combates + torneo por eliminación. Requiere un número de
 * luchadores potencia de 2 (se comprueba con n & (n-1) == 0). En cada ronda se
 * barajan y emparejan; el ganador avanza.
 *
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct { const char *nombre; int velocidad, ataque, defensa, salud; } Luchador;

static int dano(const Luchador *a, const Luchador *d) {
    if (a->ataque > d->defensa) return a->ataque - d->defensa;
    int min = (int)(a->ataque * 0.10);
    return min > 1 ? min : 1;
}

static Luchador combate(Luchador a, Luchador b) {
    a.salud = b.salud = 100;
    Luchador *ata = a.velocidad >= b.velocidad ? &a : &b;
    Luchador *def = (ata == &a) ? &b : &a;
    printf("    %s vs %s (empieza %s)\n", a.nombre, b.nombre, ata->nombre);
    while (a.salud > 0 && b.salud > 0) {
        if ((double)rand() / RAND_MAX >= 0.20) def->salud -= dano(ata, def);
        Luchador *t = ata; ata = def; def = t;
    }
    Luchador ganador = a.salud > 0 ? a : b;
    printf("    -> gana %s\n", ganador.nombre);
    return ganador;
}

static void barajar(Luchador *a, int n) {
    for (int i = n - 1; i > 0; --i) { int j = rand() % (i + 1); Luchador t = a[i]; a[i] = a[j]; a[j] = t; }
}

int main(void) {
    srand(42);
    Luchador luchadores[] = {
        {"Goku", 90, 85, 70, 100}, {"Vegeta", 85, 88, 65, 100}, {"Piccolo", 70, 75, 80, 100},
        {"Freezer", 95, 90, 60, 100}, {"Gohan", 80, 82, 72, 100}, {"Cell", 78, 86, 78, 100},
        {"Krilin", 65, 60, 55, 100}, {"Trunks", 82, 80, 68, 100},
    };
    int n = 8;
    if ((n & (n - 1)) != 0) { printf("Debe ser potencia de 2.\n"); return 1; }

    printf("=== Torneo de Artes Marciales ===\n");
    barajar(luchadores, n);
    int ronda = 1;
    while (n > 1) {
        printf("\n--- Ronda %d (%d luchadores) ---\n", ronda++, n);
        for (int i = 0; i < n / 2; ++i)
            luchadores[i] = combate(luchadores[2 * i], luchadores[2 * i + 1]);
        n /= 2;
        barajar(luchadores, n);
    }
    printf("\n%s es el campeon del torneo!\n", luchadores[0].nombre);
    return 0;
}
