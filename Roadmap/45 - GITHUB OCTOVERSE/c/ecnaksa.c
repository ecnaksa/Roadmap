/* popen()/pclose() son POSIX */
#define _POSIX_C_SOURCE 200809L

/*
 * #45 - GITHUB OCTOVERSE (informe de usuario) (C)
 *
 * =========================== TEORÍA ===========================
 * Consumo de la API pública de GitHub con 'curl' vía popen(). Con
 * /users/{login} y /users/{login}/repos se calculan métricas contando
 * apariciones de claves en el JSON. GITHUB_TOKEN (opcional) sube el límite.
 *
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t run(const char *cmd, char *out, size_t cap) {
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

static long sumar_claves(const char *j, const char *marca) {
    long total = 0;
    const char *p = j;
    size_t len = strlen(marca);
    while ((p = strstr(p, marca)) != NULL) { p += len; total += atol(p); }
    return total;
}

int main(void) {
    const char *login = "mouredev";
    const char *token = getenv("GITHUB_TOKEN");
    char auth[600] = "";
    if (token) snprintf(auth, sizeof auth, " -H 'Authorization: Bearer %s'", token);

    static char usuario[65536], repos[400000];
    char cmd[1024];

    snprintf(cmd, sizeof cmd, "curl -s -H 'User-Agent: roadmap-ecnaksa'%s https://api.github.com/users/%s", auth, login);
    run(cmd, usuario, sizeof usuario);
    if (!strstr(usuario, "\"login\"")) {
        printf("No se pudo obtener el usuario (limite de la API o sin conexion).\n");
        return 0;
    }
    snprintf(cmd, sizeof cmd, "curl -s -H 'User-Agent: roadmap-ecnaksa'%s 'https://api.github.com/users/%s/repos?per_page=100'", auth, login);
    run(cmd, repos, sizeof repos);

    long stars = sumar_claves(repos, "\"stargazers_count\":");
    long forks = sumar_claves(repos, "\"forks_count\":");

    char publicRepos[32], seguidores[32], seguidos[32];
    campo(usuario, "public_repos", publicRepos);
    campo(usuario, "followers", seguidores);
    campo(usuario, "following", seguidos);

    printf("===== INFORME OCTOVERSE: @%s =====\n", login);
    printf("  1. Repositorios publicos: %s\n", publicRepos);
    printf("  2. Seguidores/Seguidos:   %s / %s\n", seguidores, seguidos);
    printf("  3. Stars totales:         %ld\n", stars);
    printf("  4. Forks totales:         %ld\n", forks);
    printf("  (metrica de lenguaje: ver version C++/Python)\n");
    return 0;
}
