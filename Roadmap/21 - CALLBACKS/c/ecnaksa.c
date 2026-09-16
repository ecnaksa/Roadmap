/*
 * #21 - CALLBACKS (C)
 *
 * =========================== TEORÍA ===========================
 * En C un CALLBACK se implementa con un PUNTERO A FUNCIÓN: se declara el tipo
 * (retorno y parámetros) y se pasa el nombre de una función como argumento.
 * La función receptora lo invoca cuando corresponde.
 *
 * DIFICULTAD EXTRA: simulador de pedidos de restaurante con callbacks.
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>

/* Tipo de callback: recibe un int */
typedef void (*Callback)(int);
typedef void (*CallbackPlato)(const char *);

void procesar(const int *datos, int n, Callback cb) {
    for (int i = 0; i < n; ++i) cb(datos[i]);
}

void al_procesar(int n) { printf("  procesando %d -> %d\n", n, n * n); }

void procesar_pedido(const char *plato, CallbackPlato onConfirmado,
                     CallbackPlato onListo, CallbackPlato onEntregado) {
    onConfirmado(plato);
    onListo(plato);
    onEntregado(plato);
}

void confirmado(const char *p) { printf("  [OK] confirmado: %s\n", p); }
void listo(const char *p)      { printf("  '%s' esta listo\n", p); }
void entregado(const char *p)  { printf("  '%s' entregado. Buen provecho!\n", p); }

int main(void) {
    printf("=== Callback simple ===\n");
    int datos[] = {1, 2, 3};
    procesar(datos, 3, al_procesar);

    printf("\n=== Reto extra: pedidos de restaurante ===\n");
    procesar_pedido("Ramen", confirmado, listo, entregado);
    return 0;
}
