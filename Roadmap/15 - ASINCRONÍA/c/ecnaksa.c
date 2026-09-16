/*
 * #15 - ASINCRONÍA (C)
 *
 * =========================== TEORÍA ===========================
 * C no tiene async/await. La concurrencia se logra con HILOS del sistema. En
 * POSIX se usa <pthread.h>: pthread_create lanza un hilo y pthread_join espera
 * a que termine. Lanzando varios hilos a la vez se obtiene paralelismo.
 *
 * DIFICULTAD EXTRA: C, B, A en paralelo; D cuando terminan las tres.
 * Compilar: gcc ecnaksa.c -o ecnaksa -lpthread
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

typedef struct { const char *nombre; int segundos; } Tarea;

void *ejecutar(void *arg) {
    Tarea *t = (Tarea *)arg;
    printf("  > '%s' empieza (durara %ds)\n", t->nombre, t->segundos);
    fflush(stdout);
    sleep(t->segundos);
    printf("  # '%s' finaliza\n", t->nombre);
    fflush(stdout);
    return NULL;
}

int main(void) {
    printf("=== Tarea asincrona simple ===\n");
    pthread_t h;
    Tarea simple = {"Sencilla", 1};
    pthread_create(&h, NULL, ejecutar, &simple);
    pthread_join(h, NULL);

    printf("\n=== Reto extra: C, B, A en paralelo; luego D ===\n");
    pthread_t hc, hb, ha, hd;
    Tarea tc = {"C", 3}, tb = {"B", 2}, ta = {"A", 1}, td = {"D", 1};
    pthread_create(&hc, NULL, ejecutar, &tc);
    pthread_create(&hb, NULL, ejecutar, &tb);
    pthread_create(&ha, NULL, ejecutar, &ta);
    pthread_join(hc, NULL);
    pthread_join(hb, NULL);
    pthread_join(ha, NULL);
    pthread_create(&hd, NULL, ejecutar, &td);  /* D empieza al terminar las tres */
    pthread_join(hd, NULL);
    return 0;
}
