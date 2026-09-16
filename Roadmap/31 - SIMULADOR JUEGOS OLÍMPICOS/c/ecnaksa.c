/*
 * #31 - SIMULADOR DE JUEGOS OLÍMPICOS (C)
 *
 * =========================== TEORÍA ===========================
 * Integra structs, arrays y aleatoriedad (rand/srand). Cada evento tiene sus
 * participantes; se barajan (Fisher-Yates) y se reparten medallas al podio.
 * El medallero se acumula por país.
 *
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { char nombre[24]; char pais[16]; } Participante;
typedef struct { char nombre[24]; Participante parts[8]; int n; } Evento;

static void barajar(Participante *a, int n) {
    for (int i = n - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        Participante t = a[i]; a[i] = a[j]; a[j] = t;
    }
}

int main(void) {
    srand(2024);
    Evento eventos[] = {
        {"100m lisos", {{"Bolt", "Jamaica"}, {"Gatlin", "EE.UU."}, {"Blake", "Jamaica"}, {"Coleman", "EE.UU."}}, 4},
        {"Natacion 200m", {{"Phelps", "EE.UU."}, {"Popov", "Rusia"}, {"Thorpe", "Australia"}}, 3},
        {"Maraton", {{"Kipchoge", "Kenia"}, {"Bekele", "Etiopia"}, {"Farah", "Reino Unido"}, {"Rupp", "EE.UU."}}, 4},
    };
    int numEventos = 3;
    const char *medallas[] = {"Oro", "Plata", "Bronce"};

    char paises[32][16]; int conteo[32]; int numPaises = 0;

    printf("===== INFORME JJOO Paris 2024 =====\n");
    for (int e = 0; e < numEventos; ++e) {
        barajar(eventos[e].parts, eventos[e].n);
        printf("\n%s:\n", eventos[e].nombre);
        for (int i = 0; i < 3 && i < eventos[e].n; ++i) {
            Participante *g = &eventos[e].parts[i];
            printf("  %s: %s (%s)\n", medallas[i], g->nombre, g->pais);
            int idx = -1;
            for (int k = 0; k < numPaises; ++k) if (strcmp(paises[k], g->pais) == 0) idx = k;
            if (idx < 0) { idx = numPaises++; strcpy(paises[idx], g->pais); conteo[idx] = 0; }
            conteo[idx]++;
        }
    }

    printf("\n----- RANKING DE PAISES -----\n");
    /* ordenar por conteo desc (selection sort) */
    for (int i = 0; i < numPaises; ++i)
        for (int j = i + 1; j < numPaises; ++j)
            if (conteo[j] > conteo[i]) {
                int c = conteo[i]; conteo[i] = conteo[j]; conteo[j] = c;
                char t[16]; strcpy(t, paises[i]); strcpy(paises[i], paises[j]); strcpy(paises[j], t);
            }
    for (int i = 0; i < numPaises; ++i)
        printf("  %d. %s: %d medalla(s)\n", i + 1, paises[i], conteo[i]);
    return 0;
}
