/*
 * #27 - SOLID: OCP (C)
 *
 * =========================== TEORÍA ===========================
 * OCP: "abierto a la extensión, cerrado a la modificación". En C se logra con
 * un REGISTRO de punteros a función: la calculadora guarda pares
 * (nombre, función). Añadir una operación es registrar una función nueva, sin
 * modificar la lógica central.
 *
 * DIFICULTAD EXTRA: calculadora extensible con una quinta operación.
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>
#include <string.h>
#include <math.h>

typedef double (*Operacion)(double, double);

typedef struct { char nombre[16]; Operacion op; } Entrada;

static Entrada registro[16];
static int num_ops = 0;

void registrar(const char *nombre, Operacion op) {
    strcpy(registro[num_ops].nombre, nombre);
    registro[num_ops].op = op;
    num_ops++;
}

double operar(const char *nombre, double a, double b) {
    for (int i = 0; i < num_ops; ++i)
        if (strcmp(registro[i].nombre, nombre) == 0) return registro[i].op(a, b);
    return 0;
}

double suma(double a, double b) { return a + b; }
double resta(double a, double b) { return a - b; }
double mult(double a, double b) { return a * b; }
double dividir(double a, double b) { return b ? a / b : 0; }
double potencia(double a, double b) { return pow(a, b); }  /* extension */

int main(void) {
    printf("=== OCP: calculadora extensible ===\n");
    registrar("suma", suma);
    registrar("resta", resta);
    registrar("mult", mult);
    registrar("div", dividir);
    printf("  suma(4,2)=%.0f\n", operar("suma", 4, 2));
    printf("  div(4,2)=%.0f\n", operar("div", 4, 2));

    registrar("pot", potencia);   /* añadida sin tocar operar() */
    printf("  pot(4,2)=%.0f  <- extension OCP\n", operar("pot", 4, 2));
    return 0;
}
