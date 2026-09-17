/*
 * #49 - EL ALMACÉN DE PAPÁ NOEL (C)
 *
 * =========================== TEORÍA ===========================
 * Juego tipo Mastermind. Código de 4 caracteres (letras A-C y números 1-3, sin
 * repetidos). Cada intento se compara carácter a carácter: Correcto (bien
 * colocado), Presente (existe en otra posición) o Incorrecto.
 *
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LONGITUD 4

static void generar_codigo(char *out) {
    char chars[] = "ABC123";
    int n = 6;
    for (int i = n - 1; i > 0; --i) { int j = rand() % (i + 1); char t = chars[i]; chars[i] = chars[j]; chars[j] = t; }
    strncpy(out, chars, LONGITUD);
    out[LONGITUD] = '\0';
}

static const char *validar(const char *intento) {
    if (strlen(intento) != LONGITUD) return "el codigo debe tener 4 caracteres";
    for (int i = 0; intento[i]; ++i)
        if (!strchr("ABC123", intento[i])) return "caracter no soportado";
    return NULL;
}

static void evaluar(const char *secreto, const char *intento) {
    printf("  ");
    for (int i = 0; i < LONGITUD; ++i) {
        const char *estado;
        if (intento[i] == secreto[i]) estado = "Correcto";
        else if (strchr(secreto, intento[i])) estado = "Presente";
        else estado = "Incorrecto";
        printf("%c:%s  ", intento[i], estado);
    }
    printf("\n");
}

int main(void) {
    srand(49);
    char secreto[LONGITUD + 1];
    generar_codigo(secreto);
    printf("=== El almacen de Papa Noel (demo) ===\n");
    printf("(codigo secreto para la demo: %s)\n", secreto);

    const char *intentos[3];
    intentos[0] = "AB12"; intentos[1] = "XY99"; intentos[2] = secreto;
    for (int i = 0; i < 3; ++i) {
        const char *err = validar(intentos[i]);
        if (err) { printf("  Intento %d '%s': [!] %s\n", i + 1, intentos[i], err); continue; }
        printf("  Intento %d '%s':\n", i + 1, intentos[i]);
        evaluar(secreto, intentos[i]);
        if (strcmp(intentos[i], secreto) == 0) { printf("  Codigo descifrado!\n"); break; }
    }
    return 0;
}
