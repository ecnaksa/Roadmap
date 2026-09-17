/* popen()/pclose() son POSIX */
#define _POSIX_C_SOURCE 200809L

/*
 * #40 - FORTNITE RUBIUS CUP (API de Twitch) (C)
 *
 * =========================== TEORÍA ===========================
 * Consumo de la API de Twitch con OAuth (Client Credentials) usando 'curl' vía
 * popen(): se pide un app access token y se consultan /helix/users y
 * /helix/channels/followers. Credenciales por variables de entorno (no se
 * suben): TWITCH_CLIENT_ID / TWITCH_CLIENT_SECRET.
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

static void campo(const char *j, const char *clave, char *out) {
    char buscado[64];
    snprintf(buscado, sizeof buscado, "\"%s\"", clave);
    const char *p = strstr(j, buscado);
    if (!p || !(p = strchr(p, ':'))) { out[0] = '\0'; return; }
    p++;
    while (*p == ' ' || *p == '"') p++;
    int i = 0;
    while (*p && *p != '"' && *p != ',' && *p != '}' && i < 63) out[i++] = *p++;
    out[i] = '\0';
}

int main(void) {
    const char *id = getenv("TWITCH_CLIENT_ID");
    const char *secret = getenv("TWITCH_CLIENT_SECRET");
    printf("=== Fortnite Rubius Cup (Twitch) ===\n");
    if (!id || !secret) {
        printf("Faltan credenciales. Configura TWITCH_CLIENT_ID y TWITCH_CLIENT_SECRET\n"
               "(registro en https://dev.twitch.tv/console).\n");
        return 0;
    }

    static char buffer[65536];
    char cmd[1024];
    snprintf(cmd, sizeof cmd, "curl -s -X POST 'https://id.twitch.tv/oauth2/token' "
             "-d 'client_id=%s&client_secret=%s&grant_type=client_credentials'", id, secret);
    ejecutar(cmd, buffer, sizeof buffer);
    char token[512];
    campo(buffer, "access_token", token);
    if (token[0] == '\0') { printf("No se pudo obtener token.\n"); return 0; }

    const char *participantes[] = {"rubius", "auronplay", "ibai", "usuario_inexistente_xyz"};
    printf("Seguidores por canal:\n");
    for (int i = 0; i < 4; ++i) {
        snprintf(cmd, sizeof cmd, "curl -s 'https://api.twitch.tv/helix/users?login=%s' "
                 "-H 'Client-Id: %s' -H 'Authorization: Bearer %s'", participantes[i], id, token);
        ejecutar(cmd, buffer, sizeof buffer);
        char uid[32], creada[32];
        campo(buffer, "id", uid);
        campo(buffer, "created_at", creada); creada[10] = '\0';
        if (uid[0] == '\0') { printf("  %s: (sin cuenta en Twitch)\n", participantes[i]); continue; }
        snprintf(cmd, sizeof cmd, "curl -s 'https://api.twitch.tv/helix/channels/followers?broadcaster_id=%s' "
                 "-H 'Client-Id: %s' -H 'Authorization: Bearer %s'", uid, id, token);
        ejecutar(cmd, buffer, sizeof buffer);
        char total[32];
        campo(buffer, "total", total);
        printf("  %s: %s seguidores, creada %s\n", participantes[i], total, creada);
    }
    return 0;
}
