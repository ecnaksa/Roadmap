/* popen()/pclose() y setenv() son POSIX */
#define _POSIX_C_SOURCE 200809L

/*
 * #37 - OASIS VS LINKIN PARK (API de Spotify) (C)
 *
 * =========================== TEORÍA ===========================
 * Consumo de la Web API de Spotify con OAuth 2.0 (Client Credentials). Con
 * 'curl' vía popen(): se pide un token con las credenciales y luego se
 * consulta el endpoint de búsqueda. Credenciales por variables de entorno
 * (no se suben): SPOTIFY_CLIENT_ID / SPOTIFY_CLIENT_SECRET.
 *
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t ejecutar(const char *cmd, char *out, size_t cap) {
    FILE *p = popen(cmd, "r");
    if (!p) return 0;
    size_t n = fread(out, 1, cap - 1, p);
    out[n] = '\0';
    pclose(p);
    return n;
}

static void campo(const char *json, const char *clave, char *out) {
    char buscado[64];
    snprintf(buscado, sizeof buscado, "\"%s\"", clave);
    const char *p = strstr(json, buscado);
    if (!p || !(p = strchr(p, ':'))) { out[0] = '\0'; return; }
    p++;
    while (*p == ' ' || *p == '"') p++;
    int i = 0;
    while (*p && *p != '"' && *p != ',' && *p != '}' && i < 63) out[i++] = *p++;
    out[i] = '\0';
}

int main(void) {
    const char *id = getenv("SPOTIFY_CLIENT_ID");
    const char *secret = getenv("SPOTIFY_CLIENT_SECRET");
    printf("=== Oasis vs Linkin Park (Spotify) ===\n");
    if (!id || !secret) {
        printf("Faltan credenciales. Configura SPOTIFY_CLIENT_ID y SPOTIFY_CLIENT_SECRET\n"
               "(registro en https://developer.spotify.com).\n");
        return 0;
    }

    static char buffer[65536];
    char cmd[1024];
    snprintf(cmd, sizeof cmd,
             "curl -s -X POST 'https://accounts.spotify.com/api/token' "
             "-d grant_type=client_credentials -u '%s:%s'", id, secret);
    ejecutar(cmd, buffer, sizeof buffer);
    char token[512];
    campo(buffer, "access_token", token);
    if (token[0] == '\0') { printf("No se pudo obtener token.\n"); return 0; }

    const char *bandas[] = {"Oasis", "Linkin+Park"};
    for (int i = 0; i < 2; ++i) {
        snprintf(cmd, sizeof cmd,
                 "curl -s 'https://api.spotify.com/v1/search?q=%s&type=artist&limit=1' "
                 "-H 'Authorization: Bearer %s'", bandas[i], token);
        ejecutar(cmd, buffer, sizeof buffer);
        char seguidores[64], popularidad[64];
        campo(buffer, "total", seguidores);
        campo(buffer, "popularity", popularidad);
        printf("  %s: seguidores=%s popularidad=%s\n", bandas[i], seguidores, popularidad);
    }
    return 0;
}
