/*
 * #19 - ENUMERACIONES (C)
 *
 * =========================== TEORÍA ===========================
 * En C un 'enum' define constantes enteras con nombre. Por defecto empiezan en
 * 0 y se incrementan de 1 en 1, pero se puede fijar el valor inicial. A
 * diferencia de C++, no hay 'enum class': los nombres viven en el ámbito
 * global, así que conviene prefijarlos.
 *
 * DIFICULTAD EXTRA: gestión de estado de pedidos.
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>

typedef enum { LUNES = 1, MARTES, MIERCOLES, JUEVES, VIERNES, SABADO, DOMINGO } Dia;

const char *nombre_dia(int n) {
    static const char *nombres[] = {"Lunes", "Martes", "Miercoles", "Jueves",
                                    "Viernes", "Sabado", "Domingo"};
    if (n < 1 || n > 7) return "Dia no valido";
    return nombres[n - 1];
}

/* --- Reto extra --- */
typedef enum { PENDIENTE, ENVIADO, ENTREGADO, CANCELADO } Estado;

typedef struct { int id; Estado estado; } Pedido;

void enviar(Pedido *p)   { if (p->estado == PENDIENTE) p->estado = ENVIADO; else printf("  [!] No se puede enviar\n"); }
void entregar(Pedido *p) { if (p->estado == ENVIADO) p->estado = ENTREGADO; else printf("  [!] No se puede entregar si no esta enviado\n"); }
void cancelar(Pedido *p) { if (p->estado == PENDIENTE || p->estado == ENVIADO) p->estado = CANCELADO; else printf("  [!] No se puede cancelar\n"); }

const char *describir(const Pedido *p) {
    const char *t[] = {"pendiente", "enviado", "entregado", "cancelado"};
    return t[p->estado];
}

int main(void) {
    printf("=== Dias de la semana ===\n");
    int dias[] = {1, 5, 7, 9};
    for (int i = 0; i < 4; ++i) printf("  %d -> %s\n", dias[i], nombre_dia(dias[i]));

    printf("\n=== Reto extra: pedidos ===\n");
    Pedido p1 = {1, PENDIENTE};
    printf("  Pedido #%d %s\n", p1.id, describir(&p1));
    enviar(&p1);   printf("  Pedido #%d %s\n", p1.id, describir(&p1));
    entregar(&p1); printf("  Pedido #%d %s\n", p1.id, describir(&p1));

    Pedido p2 = {2, PENDIENTE};
    entregar(&p2);  /* invalido */
    cancelar(&p2);
    printf("  Pedido #%d %s\n", p2.id, describir(&p2));
    return 0;
}
