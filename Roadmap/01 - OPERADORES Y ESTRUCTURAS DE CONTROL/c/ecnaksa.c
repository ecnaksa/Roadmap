/*
 * #01 - OPERADORES Y ESTRUCTURAS DE CONTROL (C)
 *
 * =========================== TEORÍA ===========================
 * OPERADORES en C: aritméticos (+ - * / %), comparación (== != < > <= >=),
 * lógicos (&& || !), asignación (= += ...), bits (& | ^ ~ << >>) e
 * incremento/decremento (++ --). No hay potencia nativa: se usa pow() de
 * <math.h>. ESTRUCTURAS DE CONTROL: if/else, switch, for, while, do-while.
 * C no tiene excepciones; los errores se gestionan con códigos de retorno.
 *
 * DIFICULTAD EXTRA: números 10..55 pares, que no sean 16 ni múltiplos de 3.
 * ============================ PRÁCTICA ========================
 * Compilar: gcc -std=c11 ecnaksa.c -o ecnaksa -lm && ./ecnaksa
 */

#include <stdio.h>
#include <math.h>

int main(void) {
    printf("=== Aritméticos ===\n");
    printf("7+2=%d  7/2=%d  7%%2=%d  pow(7,2)=%.0f\n", 7 + 2, 7 / 2, 7 % 2, pow(7, 2));

    printf("\n=== Comparación y lógicos ===\n");
    printf("(7>2 && 2>1) = %d\n", (7 > 2 && 2 > 1));

    printf("\n=== Bits ===\n");
    printf("5&3=%d  5|3=%d  5<<1=%d\n", 5 & 3, 5 | 3, 5 << 1);

    printf("\n=== Condicional (if/else) ===\n");
    int nota = 7;
    if (nota >= 9) printf("Sobresaliente\n");
    else if (nota >= 5) printf("Aprobado\n");
    else printf("Suspenso\n");

    printf("\n=== switch ===\n");
    switch (nota) {
        case 7: printf("La nota es 7\n"); break;
        default: printf("Otra nota\n");
    }

    printf("\n=== Bucles ===\n");
    for (int i = 0; i < 3; ++i) printf("for %d  ", i);
    printf("\n");
    int n = 3;
    while (n-- > 0) printf("while %d  ", n);
    printf("\n");

    printf("\n=== Reto extra: 10..55 pares, sin 16 ni múltiplos de 3 ===\n");
    for (int i = 10; i <= 55; ++i)
        if (i % 2 == 0 && i != 16 && i % 3 != 0)
            printf("%d ", i);
    printf("\n");
    return 0;
}
