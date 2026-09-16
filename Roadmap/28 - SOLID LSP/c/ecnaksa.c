/*
 * #28 - SOLID: LSP (C)
 *
 * =========================== TEORÍA ===========================
 * LSP: los "subtipos" deben poder usarse donde se espera el tipo base sin
 * romper nada. En C emulamos el polimorfismo con un struct Vehiculo que
 * contiene punteros a función (acelerar/frenar). Una misma función de prueba
 * sirve para todos los vehículos porque todos respetan el mismo contrato.
 *
 * DIFICULTAD EXTRA: jerarquía de vehículos que cumple el LSP.
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>

typedef struct Vehiculo {
    const char *nombre;
    int velocidad;
    void (*acelerar)(struct Vehiculo *, int);
    void (*frenar)(struct Vehiculo *, int);
} Vehiculo;

static void frenar_base(Vehiculo *v, int dec) { v->velocidad -= dec; if (v->velocidad < 0) v->velocidad = 0; }
static void acel_coche(Vehiculo *v, int inc) { v->velocidad += inc; }
static void acel_bici(Vehiculo *v, int inc)  { v->velocidad += (inc < 5 ? inc : 5); }
static void acel_tren(Vehiculo *v, int inc)  { v->velocidad += inc * 2; }

/* Funciona con cualquier vehiculo -> LSP */
static void prueba_lsp(Vehiculo *v) {
    v->acelerar(v, 10);
    v->frenar(v, 3);
    printf("  %s -> velocidad %d\n", v->nombre, v->velocidad);
}

int main(void) {
    printf("=== LSP: subtipos sustituibles ===\n");
    Vehiculo coche = {"Coche", 0, acel_coche, frenar_base};
    Vehiculo bici  = {"Bicicleta", 0, acel_bici, frenar_base};
    Vehiculo tren  = {"Tren", 0, acel_tren, frenar_base};
    Vehiculo *lista[] = {&coche, &bici, &tren};
    for (int i = 0; i < 3; ++i) prueba_lsp(lista[i]);
    return 0;
}
