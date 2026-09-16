/*
 * #14 - FECHAS (C)
 *
 * =========================== TEORÍA ===========================
 * C maneja fechas con <time.h>: time() da el tiempo actual (segundos desde
 * 1970), localtime() lo convierte a struct tm y strftime() lo formatea a
 * texto con códigos: %d día, %m mes, %Y año, %H:%M:%S hora, %A día de la
 * semana, %B nombre del mes, %j día del año...
 *
 * DIFICULTAD EXTRA: mostrar la fecha de nacimiento en 10 formatos.
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>
#include <time.h>

static void formatear(const struct tm *t, const char *patron) {
    char buffer[128];
    strftime(buffer, sizeof buffer, patron, t);
    printf("%s", buffer);
}

int main(void) {
    time_t ahora_t = time(NULL);
    struct tm ahora = *localtime(&ahora_t);

    struct tm nacimiento = {0};
    nacimiento.tm_year = 1994 - 1900;
    nacimiento.tm_mon = 5 - 1;
    nacimiento.tm_mday = 12;
    nacimiento.tm_hour = 8; nacimiento.tm_min = 30;
    mktime(&nacimiento);   /* normaliza y calcula día de la semana */

    int anios = ahora.tm_year - nacimiento.tm_year;
    if (ahora.tm_mon < nacimiento.tm_mon ||
        (ahora.tm_mon == nacimiento.tm_mon && ahora.tm_mday < nacimiento.tm_mday))
        --anios;

    printf("=== Fechas ===\n  Ahora:      ");
    formatear(&ahora, "%Y-%m-%d %H:%M:%S");
    printf("\n  Nacimiento: ");
    formatear(&nacimiento, "%Y-%m-%d %H:%M:%S");
    printf("\n  Anios transcurridos: %d\n", anios);

    printf("\n=== Reto extra: 10 formatos ===\n");
    const char *patrones[][2] = {
        {"Dia/Mes/Anio", "%d/%m/%Y"}, {"ISO", "%Y-%m-%d"},
        {"Hora:Min:Seg", "%H:%M:%S"}, {"Dia del anio", "%j"},
        {"Dia de la semana", "%A"}, {"Nombre del mes", "%B"},
        {"Semana del anio", "%U"}, {"Fecha completa", "%c"},
        {"12h AM/PM", "%I:%M %p"}, {"Largo", "%A %d %B %Y %H:%M"},
    };
    for (int i = 0; i < 10; ++i) {
        printf("  %s: ", patrones[i][0]);
        formatear(&nacimiento, patrones[i][1]);
        printf("\n");
    }
    return 0;
}
