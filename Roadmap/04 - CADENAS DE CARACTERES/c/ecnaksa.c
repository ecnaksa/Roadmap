/*
 * #04 - CADENAS DE CARACTERES (C)
 *
 * =========================== TEORÍA ===========================
 * En C una cadena es un array de char terminado en '\0'. La librería
 * <string.h> ofrece funciones: strlen, strcpy, strcat, strcmp, strchr...
 * No hay comprobación automática de límites: hay que reservar memoria
 * suficiente para evitar desbordamientos.
 *
 * DIFICULTAD EXTRA: palíndromos, anagramas e isogramas.
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/* Normaliza: copia solo alfanuméricos en minúscula a 'out'. */
static void normalizar(const char *s, char *out) {
    int j = 0;
    for (int i = 0; s[i]; ++i)
        if (isalnum((unsigned char)s[i])) out[j++] = (char)tolower((unsigned char)s[i]);
    out[j] = '\0';
}

static int es_palindromo(const char *s) {
    char n[256]; normalizar(s, n);
    int len = (int)strlen(n);
    for (int i = 0; i < len / 2; ++i)
        if (n[i] != n[len - 1 - i]) return 0;
    return 1;
}

static int cmp_char(const void *a, const void *b) {
    return *(const char *)a - *(const char *)b;
}

static int son_anagramas(const char *a, const char *b) {
    char x[256], y[256]; normalizar(a, x); normalizar(b, y);
    if (strlen(x) != strlen(y)) return 0;
    qsort(x, strlen(x), 1, cmp_char);
    qsort(y, strlen(y), 1, cmp_char);
    return strcmp(x, y) == 0;
}

static int es_isograma(const char *s) {
    char n[256]; normalizar(s, n);
    for (int i = 0; n[i]; ++i)
        for (int j = i + 1; n[j]; ++j)
            if (n[i] == n[j]) return 0;
    return 1;
}

int main(void) {
    char s[] = "Hola, C";
    printf("=== Operaciones ===\n");
    printf("longitud: %zu\n", strlen(s));
    printf("s[0]: %c\n", s[0]);
    printf("subcadena desde 6: %s\n", s + 6);
    char copia[32]; strcpy(copia, s); strcat(copia, "!");
    printf("concat: %s\n", copia);
    for (int i = 0; s[i]; ++i) s[i] = (char)toupper((unsigned char)s[i]);
    printf("mayusculas: %s\n", s);

    printf("\n=== Reto extra ===\n");
    const char *pares[][2] = {{"Roma", "Amor"}, {"Anita lava la tina", "casa"}};
    for (int i = 0; i < 2; ++i) {
        printf("  '%s' palindromo? %d\n", pares[i][0], es_palindromo(pares[i][0]));
        printf("  '%s' y '%s' anagramas? %d\n", pares[i][0], pares[i][1], son_anagramas(pares[i][0], pares[i][1]));
        printf("  '%s' isograma? %d\n", pares[i][0], es_isograma(pares[i][0]));
    }
    return 0;
}
