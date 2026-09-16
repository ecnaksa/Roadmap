/*
 * #18 - CONJUNTOS (C)
 *
 * =========================== TEORÍA ===========================
 * El ejercicio principal (operaciones posicionales) se resuelve con un ARRAY
 * y desplazamientos manuales. El reto extra (operaciones de conjuntos) se
 * implementa a mano: unión, intersección, diferencia y diferencia simétrica
 * comprobando la pertenencia elemento a elemento.
 *
 * DIFICULTAD EXTRA: unión, intersección, diferencia y diferencia simétrica.
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>

static int contiene(const int *s, int n, int v) {
    for (int i = 0; i < n; ++i) if (s[i] == v) return 1;
    return 0;
}

static void imprimir(const char *etq, const int *s, int n) {
    printf("  %s", etq);
    for (int i = 0; i < n; ++i) printf("%d ", s[i]);
    printf("\n");
}

int main(void) {
    printf("=== Operaciones posicionales (array) ===\n");
    int d[20] = {1, 2, 3};
    int n = 3;
    d[n++] = 4;                                  /* final */
    for (int i = n; i > 0; --i) d[i] = d[i - 1]; /* hueco al principio */
    d[0] = 0; n++;
    d[n++] = 5; d[n++] = 6;                       /* varios al final */
    d[0] = 99;                                    /* actualizar */
    imprimir("estado: ", d, n);
    printf("  contiene 99? %d\n", contiene(d, n, 99));

    printf("\n=== Reto extra: operaciones de conjuntos ===\n");
    int a[] = {1, 2, 3, 4}, b[] = {3, 4, 5, 6};
    int na = 4, nb = 4, res[20], nr;

    nr = 0;
    for (int i = 0; i < na; ++i) res[nr++] = a[i];
    for (int i = 0; i < nb; ++i) if (!contiene(a, na, b[i])) res[nr++] = b[i];
    imprimir("union:        ", res, nr);

    nr = 0;
    for (int i = 0; i < na; ++i) if (contiene(b, nb, a[i])) res[nr++] = a[i];
    imprimir("interseccion: ", res, nr);

    nr = 0;
    for (int i = 0; i < na; ++i) if (!contiene(b, nb, a[i])) res[nr++] = a[i];
    imprimir("diferencia:   ", res, nr);

    nr = 0;
    for (int i = 0; i < na; ++i) if (!contiene(b, nb, a[i])) res[nr++] = a[i];
    for (int i = 0; i < nb; ++i) if (!contiene(a, na, b[i])) res[nr++] = b[i];
    imprimir("dif. simetrica: ", res, nr);
    return 0;
}
