/*
 * #35 - REPARTIENDO LOS ANILLOS DE PODER (C)
 *
 * =========================== TEORÍA ===========================
 * Búsqueda combinatoria con restricciones: 1 anillo para Sauron y una terna
 * elfos (impar) / enanos (primo) / hombres (par) que sume el resto.
 *
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>

int es_primo(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; ++i) if (n % i == 0) return 0;
    return 1;
}

void repartir(int total) {
    printf("\n=== Repartir %d anillos ===\n", total);
    int restante = total - 1;   /* Sauron */
    for (int elfos = 1; elfos <= restante; elfos += 2)
        for (int enanos = 2; enanos <= restante - elfos; ++enanos) {
            if (!es_primo(enanos)) continue;
            int hombres = restante - elfos - enanos;
            if (hombres >= 0 && hombres % 2 == 0) {
                printf("  Elfos:   %d\n  Enanos:  %d\n  Hombres: %d\n  Sauron:  1\n",
                       elfos, enanos, hombres);
                return;
            }
        }
    printf("  No existe un reparto valido.\n");
}

int main(void) {
    int totales[] = {20, 15, 3, 1};
    for (int i = 0; i < 4; ++i) repartir(totales[i]);
    return 0;
}
