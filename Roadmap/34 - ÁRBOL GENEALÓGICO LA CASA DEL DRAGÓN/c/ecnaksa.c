/*
 * #34 - ÁRBOL GENEALÓGICO (LA CASA DEL DRAGÓN) (C)
 *
 * =========================== TEORÍA ===========================
 * Modelado de relaciones con un array de structs. Cada persona guarda su id,
 * nombre, el índice de su pareja y los índices de sus hijos. Reglas: una sola
 * pareja y máximo dos progenitores por hijo. El recorrido para imprimir es
 * recursivo.
 *
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>
#include <string.h>

#define MAX 32

typedef struct {
    char id[4];
    char nombre[24];
    int pareja;          /* índice o -1 */
    int hijos[8];
    int numHijos;
    int numProgenitores;
} Persona;

static Persona personas[MAX];
static int total = 0;

static int buscar(const char *id) {
    for (int i = 0; i < total; ++i) if (strcmp(personas[i].id, id) == 0) return i;
    return -1;
}

static void anadir(const char *id, const char *nombre) {
    Persona *p = &personas[total++];
    strcpy(p->id, id); strcpy(p->nombre, nombre);
    p->pareja = -1; p->numHijos = 0; p->numProgenitores = 0;
}

static void emparejar(const char *a, const char *b) {
    int ia = buscar(a), ib = buscar(b);
    if (ia < 0 || ib < 0) { printf("  [!] persona inexistente\n"); return; }
    if (personas[ia].pareja >= 0 || personas[ib].pareja >= 0) { printf("  [!] ya tienen pareja\n"); return; }
    personas[ia].pareja = ib; personas[ib].pareja = ia;
    printf("  %s y %s son pareja\n", personas[ia].nombre, personas[ib].nombre);
}

static void anadir_hijo(const char *padre, const char *hijo) {
    int ip = buscar(padre), ih = buscar(hijo);
    if (ip < 0 || ih < 0) { printf("  [!] inexistente\n"); return; }
    if (personas[ih].numProgenitores >= 2) { printf("  [!] %s ya tiene 2 progenitores\n", personas[ih].nombre); return; }
    personas[ip].hijos[personas[ip].numHijos++] = ih;
    personas[ih].numProgenitores++;
    printf("  %s es hijo/a de %s\n", personas[ih].nombre, personas[ip].nombre);
}

static void imprimir(int idx, int nivel) {
    if (idx < 0) return;
    for (int i = 0; i < nivel * 4; ++i) putchar(' ');
    printf("* %s", personas[idx].nombre);
    if (personas[idx].pareja >= 0) printf(" & %s", personas[personas[idx].pareja].nombre);
    putchar('\n');
    for (int i = 0; i < personas[idx].numHijos; ++i) imprimir(personas[idx].hijos[i], nivel + 1);
}

int main(void) {
    const char *datos[][2] = {{"1", "Viserys I"}, {"2", "Alicent"}, {"3", "Rhaenyra"},
        {"4", "Daemon"}, {"5", "Aegon II"}, {"6", "Jacaerys"}};
    for (int i = 0; i < 6; ++i) anadir(datos[i][0], datos[i][1]);

    emparejar("1", "2");
    anadir_hijo("1", "3");
    anadir_hijo("2", "5");
    anadir_hijo("3", "6");
    emparejar("3", "1");   /* invalido */

    printf("\n=== Arbol genealogico ===\n");
    imprimir(buscar("1"), 0);
    return 0;
}
