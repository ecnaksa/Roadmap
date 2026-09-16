/*
 * #13 - PRUEBAS UNITARIAS (C)
 *
 * =========================== TEORÍA ===========================
 * C ofrece la macro assert() de <assert.h>, que aborta si la condición es
 * falsa. Para tests más informativos (que sigan tras un fallo) es común
 * definir una macro propia. En proyectos reales se usan frameworks como Unity
 * o CMocka. Aquí montamos un mini-framework con la macro CHECK.
 *
 * DIFICULTAD EXTRA: tests sobre un "perfil".
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int fallos = 0, total = 0;
#define CHECK(cond) do { \
    ++total; \
    if (cond) printf("  [OK] %s\n", #cond); \
    else { printf("  [FALLO] %s\n", #cond); ++fallos; } \
} while (0)

int sumar(int a, int b) { return a + b; }

int main(void) {
    printf("=== Tests de sumar ===\n");
    CHECK(sumar(2, 3) == 5);
    CHECK(sumar(-2, -3) == -5);
    CHECK(sumar(0, 0) == 0);

    printf("\n=== Reto extra: perfil ===\n");
    const char *name = "ecnaksa";
    const char *age = "30";
    const char *birth = "1994-05-12";
    const char *langs[] = {"C", "Python"};
    int numLangs = 2;

    /* Test 1: campos presentes (no vacíos) */
    CHECK(name[0] != '\0' && age[0] != '\0' && birth[0] != '\0');
    CHECK(numLangs > 0);
    /* Test 2: datos correctos */
    CHECK(atoi(age) > 0);
    CHECK(strlen(birth) == 10);

    printf("\n=== Resultado: %d/%d tests OK ===\n", total - fallos, total);
    return fallos == 0 ? 0 : 1;
}
