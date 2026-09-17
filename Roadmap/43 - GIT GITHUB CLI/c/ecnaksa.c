/* popen()/pclose() son POSIX */
#define _POSIX_C_SOURCE 200809L

/*
 * #43 - GIT / GITHUB CLI (C)
 *
 * =========================== TEORÍA ===========================
 * Integración con el sistema: se invoca 'git' con popen() para capturar su
 * salida (o system() cuando no interesa capturarla). Cada opción del CLI
 * corresponde a comandos de Git. La demo opera sobre un repo temporal.
 *
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>
#include <stdlib.h>

static void run(const char *cmd) {
    char full[512];
    snprintf(full, sizeof full, "%s 2>&1", cmd);
    FILE *p = popen(full, "r");
    if (!p) return;
    char linea[512];
    while (fgets(linea, sizeof linea, p)) fputs(linea, stdout);
    pclose(p);
}

int main(void) {
    printf("=== Git CLI (demo sobre repo temporal) ===\n");
    const char *dir = "/tmp/git_demo_c";
    system("rm -rf /tmp/git_demo_c && mkdir -p /tmp/git_demo_c");

    printf("2) init:   "); run("git -C /tmp/git_demo_c init -b main");
    system("git -C /tmp/git_demo_c config user.email demo@demo.com");
    system("git -C /tmp/git_demo_c config user.name demo");
    system("echo hola > /tmp/git_demo_c/hola.txt");
    printf("5) status:\n"); run("git -C /tmp/git_demo_c status --short");
    system("git -C /tmp/git_demo_c add .");
    printf("6) commit: "); run("git -C /tmp/git_demo_c commit -m 'primer commit' -q; echo commit hecho");
    printf("3) branch: "); system("git -C /tmp/git_demo_c branch feature"); printf("rama 'feature' creada\n");
    printf("7) log:    "); run("git -C /tmp/git_demo_c log --oneline");

    system("rm -rf /tmp/git_demo_c");
    (void)dir;
    printf("(repositorio temporal eliminado)\n");
    return 0;
}
