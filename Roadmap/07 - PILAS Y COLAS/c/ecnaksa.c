/*
 * #07 - PILAS Y COLAS (C)
 *
 * =========================== TEORÍA ===========================
 * PILA (LIFO) y COLA (FIFO). C no las trae de serie; se implementan con un
 * array y un índice (pila) o con dos índices frente/final (cola).
 *
 * DIFICULTAD EXTRA: navegador (dos pilas) e impresora (cola).
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>
#include <string.h>

#define MAX 100

/* --- Pila de enteros --- */
typedef struct { int datos[MAX]; int tope; } Pila;
void pila_init(Pila *p) { p->tope = -1; }
int pila_vacia(Pila *p) { return p->tope < 0; }
void pila_push(Pila *p, int v) { if (p->tope < MAX - 1) p->datos[++p->tope] = v; }
int pila_pop(Pila *p) { return p->datos[p->tope--]; }

/* --- Pila de cadenas (para el navegador) --- */
typedef struct { char datos[MAX][64]; int tope; } PilaStr;
void ps_init(PilaStr *p) { p->tope = -1; }
int ps_vacia(PilaStr *p) { return p->tope < 0; }
void ps_push(PilaStr *p, const char *v) { if (p->tope < MAX - 1) strcpy(p->datos[++p->tope], v); }
void ps_pop(PilaStr *p, char *out) { strcpy(out, p->datos[p->tope--]); }

int main(void) {
    printf("=== PILA (LIFO) ===\n  ");
    Pila p; pila_init(&p);
    for (int i = 1; i <= 3; ++i) pila_push(&p, i);
    while (!pila_vacia(&p)) printf("%d ", pila_pop(&p));

    printf("\n\n=== COLA (FIFO) ===\n  ");
    int cola[MAX], frente = 0, fin = 0;
    for (int i = 1; i <= 3; ++i) cola[fin++] = i;
    while (frente < fin) printf("%d ", cola[frente++]);
    printf("\n");

    printf("\n=== Reto extra: navegador (pilas) ===\n");
    const char *comandos[] = {"mouredev.com", "python.org", "atras", "atras", "github.com", "adelante"};
    PilaStr atras, adelante; ps_init(&atras); ps_init(&adelante);
    char actual[64] = "", tmp[64];
    for (int i = 0; i < 6; ++i) {
        if (strcmp(comandos[i], "atras") == 0) {
            if (!ps_vacia(&atras)) { ps_push(&adelante, actual); ps_pop(&atras, tmp); strcpy(actual, tmp);
                printf("  <- atras -> %s\n", actual); }
            else printf("  <- no hay anteriores\n");
        } else if (strcmp(comandos[i], "adelante") == 0) {
            if (!ps_vacia(&adelante)) { ps_push(&atras, actual); ps_pop(&adelante, tmp); strcpy(actual, tmp);
                printf("  -> adelante -> %s\n", actual); }
            else printf("  -> no hay siguientes\n");
        } else {
            if (actual[0]) ps_push(&atras, actual);
            strcpy(actual, comandos[i]); ps_init(&adelante);
            printf("  visitar '%s'\n", comandos[i]);
        }
    }

    printf("\n=== Reto extra: impresora (cola) ===\n");
    const char *docs[] = {"informe.pdf", "foto.png", "imprimir", "nomina.docx", "imprimir", "imprimir", "imprimir"};
    char q[MAX][64]; int qf = 0, qb = 0;
    for (int i = 0; i < 7; ++i) {
        if (strcmp(docs[i], "imprimir") == 0) {
            if (qf < qb) printf("  imprimiendo '%s'\n", q[qf++]);
            else printf("  no hay documentos\n");
        } else { strcpy(q[qb++], docs[i]); printf("  + en cola '%s'\n", docs[i]); }
    }
    return 0;
}
