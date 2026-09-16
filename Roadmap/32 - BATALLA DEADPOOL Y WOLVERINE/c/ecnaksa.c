/*
 * #32 - BATALLA DEADPOOL Y WOLVERINE (C)
 *
 * =========================== TEORÍA ===========================
 * Simulación por turnos con rand(). Cada luchador es un struct con vida, rango
 * de daño, probabilidad de evasión y estado de regeneración. El bucle alterna
 * atacante/defensor hasta que uno cae.
 *
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *nombre;
    int vida, danoMin, danoMax;
    double probEvasion;
    int debeRegenerar;
} Luchador;

static int aleatorio(int min, int max) { return min + rand() % (max - min + 1); }
static double azar(void) { return (double)rand() / RAND_MAX; }

int main(void) {
    srand(7);
    Luchador deadpool = {"Deadpool", 300, 10, 100, 0.25, 0};
    Luchador wolverine = {"Wolverine", 300, 10, 120, 0.20, 0};

    printf("=== Deadpool vs Wolverine! ===\n");
    Luchador *ata = &deadpool, *def = &wolverine;
    int turno = 0;
    while (deadpool.vida > 0 && wolverine.vida > 0) {
        printf("\n--- Turno %d ---\n", ++turno);
        if (ata->debeRegenerar) {
            printf("  %s se regenera y pierde el turno.\n", ata->nombre);
            ata->debeRegenerar = 0;
        } else {
            int dano = aleatorio(ata->danoMin, ata->danoMax);
            int maximo = (dano == ata->danoMax);
            if (azar() < def->probEvasion) {
                printf("  %s ataca por %d, pero %s lo esquiva!\n", ata->nombre, dano, def->nombre);
            } else {
                def->vida -= dano;
                printf("  %s inflige %d de danio%s.\n", ata->nombre, dano, maximo ? " (golpe maximo!)" : "");
                if (maximo) def->debeRegenerar = 1;
            }
        }
        printf("  Vida -> %s: %d | %s: %d\n", deadpool.nombre, deadpool.vida > 0 ? deadpool.vida : 0,
               wolverine.nombre, wolverine.vida > 0 ? wolverine.vida : 0);
        Luchador *tmp = ata; ata = def; def = tmp;
    }
    printf("\n%s gana la batalla!\n", deadpool.vida > 0 ? deadpool.nombre : wolverine.nombre);
    return 0;
}
