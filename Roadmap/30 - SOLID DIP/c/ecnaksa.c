/*
 * #30 - SOLID: DIP (C)
 *
 * =========================== TEORÍA ===========================
 * DIP: depender de abstracciones, no de implementaciones. En C la abstracción
 * es un PUNTERO A FUNCIÓN (el "contrato" enviar). El servicio de alto nivel
 * recibe un array de canales (punteros a función) y los usa sin conocer su
 * implementación concreta: se le inyectan desde fuera.
 *
 * DIFICULTAD EXTRA: sistema de notificaciones (Email, SMS, Push).
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>

/* Abstracción: un canal es una función que envía un mensaje */
typedef void (*Canal)(const char *);

static void email(const char *m) { printf("  EMAIL: %s\n", m); }
static void sms(const char *m)   { printf("  SMS:   %s\n", m); }
static void push(const char *m)  { printf("  PUSH:  %s\n", m); }

/* Alto nivel: depende de la abstracción (Canal), no de las implementaciones */
void servicio_notificar(Canal *canales, int n, const char *msg) {
    for (int i = 0; i < n; ++i) canales[i](msg);
}

int main(void) {
    printf("=== DIP: inyeccion de dependencias ===\n");
    Canal canales[] = {email, sms, push};   /* se inyectan desde fuera */
    servicio_notificar(canales, 3, "Nuevo reto disponible!");

    printf("\n=== Solo push (sin cambiar el servicio) ===\n");
    Canal solo[] = {push};
    servicio_notificar(solo, 1, "Recordatorio");
    printf("  Cambiar canales no obliga a modificar el servicio -> cumple DIP\n");
    return 0;
}
