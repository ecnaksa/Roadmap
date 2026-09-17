/*
 * #36 - EL SOMBRERO SELECCIONADOR (C)
 *
 * =========================== TEORÍA ===========================
 * Sistema de puntuación: 10 preguntas con 4 respuestas; cada respuesta suma un
 * punto a una de las 4 casas. Se elige el máximo y los empates se resuelven al
 * azar (rand).
 *
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const char *casas[] = {"Frontend", "Backend", "Mobile", "Data"};
    srand(1);

    int respuestas[10];
    for (int i = 0; i < 10; ++i) respuestas[i] = rand() % 4;

    int puntos[4] = {0, 0, 0, 0};
    for (int i = 0; i < 10; ++i) puntos[respuestas[i]]++;

    int maximo = 0;
    for (int i = 0; i < 4; ++i) if (puntos[i] > maximo) maximo = puntos[i];
    int empatadas[4], n = 0;
    for (int i = 0; i < 4; ++i) if (puntos[i] == maximo) empatadas[n++] = i;
    int elegida = empatadas[rand() % n];

    printf("=== El Sombrero Seleccionador (demo) ===\n");
    printf("Respuestas: ");
    for (int i = 0; i < 10; ++i) printf("%d ", respuestas[i]);
    printf("\n\nEl sombrero medita... %s\n", n > 1 ? "Dificil decision!" : "");
    printf("  ecnaksa, tu casa es: %s\n  Puntuaciones: ", casas[elegida]);
    for (int i = 0; i < 4; ++i) printf("%s=%d ", casas[i], puntos[i]);
    printf("\n");
    return 0;
}
