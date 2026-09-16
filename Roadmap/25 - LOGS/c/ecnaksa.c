/*
 * #25 - LOGS (C)
 *
 * =========================== TEORÍA ===========================
 * C no incluye un sistema de logging; se implementa a mano. Aquí definimos una
 * función log_msg con niveles (DEBUG < INFO < WARNING < ERROR < CRITICAL), un
 * nivel mínimo configurable y una marca de tiempo con strftime. El uso de
 * variadic (...) permite formatear como printf.
 *
 * DIFICULTAD EXTRA: gestor de tareas con logs y tiempos.
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

typedef enum { DEBUG, INFO, WARNING, ERROR, CRITICAL } Nivel;
static const char *ETIQUETAS[] = {"DEBUG", "INFO", "WARNING", "ERROR", "CRITICAL"};
static Nivel NIVEL_MIN = DEBUG;

void log_msg(Nivel n, const char *fmt, ...) {
    if (n < NIVEL_MIN) return;
    time_t t = time(NULL);
    char hora[16];
    strftime(hora, sizeof hora, "%H:%M:%S", localtime(&t));
    printf("%s [%s] ", hora, ETIQUETAS[n]);
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    printf("\n");
}

int main(void) {
    printf("=== Niveles de severidad ===\n");
    log_msg(DEBUG, "detalle para desarrolladores");
    log_msg(INFO, "todo va segun lo esperado");
    log_msg(WARNING, "algo inusual");
    log_msg(ERROR, "ha fallado una operacion");
    log_msg(CRITICAL, "fallo grave");

    printf("\n=== Reto extra: gestor de tareas con logs ===\n");
    char tareas[10][32];
    int n = 0;
    /* anadir */
    strcpy(tareas[n++], "Estudiar"); log_msg(INFO, "tarea anadida: 'Estudiar'");
    strcpy(tareas[n++], "Comprar");  log_msg(INFO, "tarea anadida: 'Comprar'");
    /* eliminar inexistente */
    int encontrada = 0;
    for (int i = 0; i < n; ++i) if (strcmp(tareas[i], "Inexistente") == 0) encontrada = 1;
    if (!encontrada) log_msg(ERROR, "no existe: 'Inexistente'");
    /* eliminar Comprar */
    for (int i = 0; i < n; ++i)
        if (strcmp(tareas[i], "Comprar") == 0) {
            for (int j = i; j < n - 1; ++j) strcpy(tareas[j], tareas[j + 1]);
            n--; log_msg(INFO, "tarea eliminada: 'Comprar'");
            break;
        }
    return 0;
}
