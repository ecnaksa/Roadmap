/*
 * #16 - EXPRESIONES REGULARES (C)
 *
 * =========================== TEORÍA ===========================
 * C dispone de las expresiones regulares POSIX en <regex.h>: regcomp() compila
 * el patrón, regexec() lo ejecuta y regfree() libera. La sintaxis POSIX
 * extendida (REG_EXTENDED) usa [[:digit:]] para dígitos, + para "una o más",
 * ^ y $ para anclas.
 *
 * DIFICULTAD EXTRA: validar email, teléfono y URL.
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>
#include <regex.h>
#include <string.h>

static int coincide(const char *patron, const char *texto) {
    regex_t re;
    if (regcomp(&re, patron, REG_EXTENDED | REG_NOSUB) != 0) return 0;
    int r = regexec(&re, texto, 0, NULL, 0);
    regfree(&re);
    return r == 0;
}

int main(void) {
    const char *texto = "El pedido 12 costo 34.50 euros y llego en 7 dias, codigo 007.";
    printf("=== Extraer numeros ===\n  ");
    regex_t re;
    regcomp(&re, "[0-9]+(\\.[0-9]+)?", REG_EXTENDED);
    regmatch_t m;
    const char *p = texto;
    while (regexec(&re, p, 1, &m, 0) == 0) {
        printf("%.*s ", (int)(m.rm_eo - m.rm_so), p + m.rm_so);
        p += m.rm_eo;
    }
    regfree(&re);
    printf("\n");

    const char *email = "^[a-zA-Z0-9._+-]+@[a-zA-Z0-9-]+\\.[a-zA-Z0-9.-]+$";
    const char *tel = "^(\\+[0-9]{1,3}[ ]?)?[0-9]{8,12}$";
    const char *url = "^https?://([a-zA-Z0-9-]+\\.)+[a-zA-Z0-9-]+(/[a-zA-Z0-9./?%&=_-]*)?$";

    printf("\n=== Reto extra: validaciones ===\n");
    const char *emails[] = {"hola@dominio.com", "malo@@x"};
    const char *tels[] = {"+34 600123456", "abc"};
    const char *urls[] = {"https://mouredev.com", "sin-protocolo.com"};
    for (int i = 0; i < 2; ++i) printf("  email %-22s -> %d\n", emails[i], coincide(email, emails[i]));
    for (int i = 0; i < 2; ++i) printf("  tel   %-22s -> %d\n", tels[i], coincide(tel, tels[i]));
    for (int i = 0; i < 2; ++i) printf("  url   %-22s -> %d\n", urls[i], coincide(url, urls[i]));
    return 0;
}
