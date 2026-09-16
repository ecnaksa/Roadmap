/* popen()/pclose() son POSIX: hay que pedirlos antes de incluir stdio.h */
#define _POSIX_C_SOURCE 200809L

/*
 * #20 - PETICIONES HTTP (C)
 *
 * =========================== TEORÍA ===========================
 * C no tiene cliente HTTP en su librería estándar (se usa libcurl). Aquí, sin
 * dependencias de desarrollo, ejecutamos el binario 'curl' con popen() y
 * capturamos su salida. El JSON se parsea manualmente con strstr().
 *
 * DIFICULTAD EXTRA: cliente de la PokéAPI.
 * Requiere el comando 'curl' y conexión a internet.
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Descarga 'url' en 'out' (máx cap-1 bytes). Devuelve longitud. */
static size_t http_get(const char *url, char *out, size_t cap) {
    char cmd[512];
    snprintf(cmd, sizeof cmd, "curl -s --max-time 15 '%s'", url);
    FILE *pipe = popen(cmd, "r");
    if (!pipe) return 0;
    size_t total = fread(out, 1, cap - 1, pipe);
    out[total] = '\0';
    pclose(pipe);
    return total;
}

/* Extrae el valor (string o número) de "clave": en 'json' a 'out'. */
static void campo(const char *json, const char *clave, char *out) {
    char buscado[64];
    snprintf(buscado, sizeof buscado, "\"%s\"", clave);
    const char *p = strstr(json, buscado);
    if (!p) { out[0] = '\0'; return; }
    p = strchr(p, ':');
    if (!p) { out[0] = '\0'; return; }
    p++;
    while (*p == ' ' || *p == '"') p++;
    int i = 0;
    while (*p && *p != '"' && *p != ',' && *p != '}' && i < 63) out[i++] = *p++;
    out[i] = '\0';
}

int main(void) {
    static char buffer[400000];
    printf("=== Peticion HTTP basica ===\n");
    size_t n = http_get("https://example.com", buffer, sizeof buffer);
    if (n == 0) printf("  (sin conexion o curl no disponible)\n");
    else printf("  Recibidos %zu bytes. Inicio: %.60s...\n", n, buffer);

    printf("\n=== Reto extra: PokeAPI ===\n");
    n = http_get("https://pokeapi.co/api/v2/pokemon/pikachu", buffer, sizeof buffer);
    if (n == 0 || !strstr(buffer, "\"name\"")) {
        printf("  No se pudo obtener el Pokemon (sin conexion o no encontrado).\n");
        return 0;
    }
    char valor[64];
    campo(buffer, "name", valor);   printf("  Nombre: %s\n", valor);
    campo(buffer, "id", valor);     printf("  Id:     %s\n", valor);
    campo(buffer, "weight", valor); printf("  Peso:   %s (hectogramos)\n", valor);
    campo(buffer, "height", valor); printf("  Altura: %s (decimetros)\n", valor);

    printf("  Tipos:  ");
    const char *marca = "\"type\":{\"name\":\"";
    const char *p = buffer;
    while ((p = strstr(p, marca)) != NULL) {
        p += strlen(marca);
        const char *fin = strchr(p, '"');
        if (!fin) break;                 /* respuesta incompleta: evitamos leer fuera */
        printf("%.*s ", (int)(fin - p), p);
        p = fin;
    }
    printf("\n");
    return 0;
}
