/*
 * #29 - SOLID: ISP (C)
 *
 * =========================== TEORÍA ===========================
 * ISP: cada cliente depende solo de lo que usa. En C, una "interfaz" es un
 * conjunto de punteros a función. En vez de un struct enorme con todas las
 * capacidades, definimos structs pequeños (Impresora, Escaner, Fax) y cada
 * dispositivo rellena solo los que soporta.
 *
 * DIFICULTAD EXTRA: gestor de impresoras con interfaces segregadas.
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>

/* "Interfaces" segregadas */
typedef struct { void (*imprimir)(const char *); } Impresora;
typedef struct { void (*escanear)(const char *); } Escaner;
typedef struct { void (*enviar_fax)(const char *); } Fax;

static void imprimir_bn(const char *d)    { printf("  (B/N) imprimiendo '%s'\n", d); }
static void imprimir_multi(const char *d) { printf("  imprimiendo '%s'\n", d); }
static void escanear_multi(const char *d) { printf("  escaneando '%s'\n", d); }
static void fax_multi(const char *d)      { printf("  enviando fax '%s'\n", d); }

int main(void) {
    printf("=== ISP: interfaces segregadas ===\n");

    /* Impresora sencilla: solo implementa Impresora */
    Impresora bn = {imprimir_bn};
    bn.imprimir("carta.txt");

    /* Multifuncion: combina las tres interfaces */
    Impresora mp = {imprimir_multi};
    Escaner me = {escanear_multi};
    Fax mf = {fax_multi};
    mp.imprimir("informe.pdf");
    me.escanear("dni.jpg");
    mf.enviar_fax("contrato.pdf");

    printf("\n  La impresora B/N no tiene puntero de escaneo: no depende de lo que no usa.\n");
    return 0;
}
