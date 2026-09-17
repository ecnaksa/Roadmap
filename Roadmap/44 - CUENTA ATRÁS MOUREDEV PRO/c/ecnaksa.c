/* pthread y sleep necesitan características POSIX */
#define _POSIX_C_SOURCE 200809L

/*
 * #44 - CUENTA ATRÁS MOUREDEV PRO (C)
 *
 * =========================== TEORÍA ===========================
 * Combina fechas (<time.h>), tiempo UTC (time() ya devuelve UTC) y concurrencia
 * con hilos POSIX (<pthread.h>). La cuenta atrás corre en un hilo, se actualiza
 * cada segundo y puede limpiar la terminal.
 *
 * ============================ PRÁCTICA ========================
 * La demo usa 3 segundos y NO limpia la pantalla.
 * Compilar: gcc ecnaksa.c -o ecnaksa -lpthread
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

typedef struct { time_t objetivo; int limpiar; } Args;

void *cuenta_atras(void *arg) {
    Args *a = (Args *)arg;
    while (1) {
        long restante = (long)(a->objetivo - time(NULL));
        if (a->limpiar) system("clear");
        if (restante <= 0) {
            printf("Es la hora! mouredev pro ya esta disponible: https://mouredev.pro\n");
            break;
        }
        long dias = restante / 86400, horas = (restante % 86400) / 3600;
        long min = (restante % 3600) / 60, seg = restante % 60;
        printf("Cuenta atras: %ldd %ldh %ldm %lds\n", dias, horas, min, seg);
        fflush(stdout);
        sleep(1);
    }
    return NULL;
}

int main(void) {
    printf("=== Cuenta atras (demo 3s, sin limpiar) ===\n");
    Args args = {time(NULL) + 3, 0};
    pthread_t hilo;
    pthread_create(&hilo, NULL, cuenta_atras, &args);
    pthread_join(hilo, NULL);
    return 0;
}
