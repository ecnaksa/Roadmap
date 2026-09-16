/*
 * #03 - ESTRUCTURAS DE DATOS (C)
 *
 * =========================== TEORÍA ===========================
 * C no trae contenedores dinámicos; la estructura básica es el ARRAY (tamaño
 * fijo) y el STRUCT para agrupar datos heterogéneos. Las operaciones de
 * inserción/borrado en un array se hacen desplazando elementos manualmente.
 * qsort() (de <stdlib.h>) ordena arrays con una función de comparación.
 *
 * DIFICULTAD EXTRA: agenda de contactos con array de structs (demo).
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int cmp_int(const void *a, const void *b) {
    return (*(const int *)a) - (*(const int *)b);
}

typedef struct { char nombre[32]; char telefono[16]; } Contacto;

static int telefono_valido(const char *t) {
    size_t len = strlen(t);
    if (len == 0 || len > 11) return 0;
    for (size_t i = 0; i < len; ++i) if (!isdigit((unsigned char)t[i])) return 0;
    return 1;
}

int main(void) {
    printf("=== Array (insertar/borrar/actualizar/ordenar) ===\n");
    int a[10] = {3, 1, 2};
    int n = 3;
    a[n++] = 4;                 /* insertar al final */
    a[1] = 10;                  /* actualizar */
    /* borrar posicion 2 desplazando */
    for (int i = 2; i < n - 1; ++i) a[i] = a[i + 1];
    n--;
    qsort(a, n, sizeof(int), cmp_int);  /* ordenar */
    printf("  ");
    for (int i = 0; i < n; ++i) printf("%d ", a[i]);
    printf("\n");

    printf("\n=== Reto extra: agenda (demo) ===\n");
    Contacto agenda[10];
    int total = 0;
    const char *nombres[] = {"Ana", "Luis", "Marta"};
    const char *tels[] = {"600111222", "abc", "999"};
    for (int i = 0; i < 3; ++i) {
        if (telefono_valido(tels[i])) {
            strcpy(agenda[total].nombre, nombres[i]);
            strcpy(agenda[total].telefono, tels[i]);
            total++;
            printf("  insertado %s: %s\n", nombres[i], tels[i]);
        } else {
            printf("  rechazado %s ('%s' no valido)\n", nombres[i], tels[i]);
        }
    }
    /* actualizar Ana */
    for (int i = 0; i < total; ++i)
        if (strcmp(agenda[i].nombre, "Ana") == 0) strcpy(agenda[i].telefono, "600999888");
    printf("  final: ");
    for (int i = 0; i < total; ++i) printf("%s=%s ", agenda[i].nombre, agenda[i].telefono);
    printf("\n");
    return 0;
}
