/*
 * #46 - X VS BLUESKY (simulador de red social) (C)
 *
 * =========================== TEORÍA ===========================
 * Modelado con arrays de structs: usuarios (con lista de a quién siguen) y
 * posts (texto máx 200, id y orden). Los feeds se generan filtrando y
 * ordenando por orden de creación. Se controlan duplicados y límites.
 *
 * ============================ PRÁCTICA ========================
 */

#include <stdio.h>
#include <string.h>

#define MAX 64
#define MAX_TEXTO 200

typedef struct { char id[16]; char nombre[24]; char siguiendo[16][16]; int nSig; } Usuario;
typedef struct { int id; char autor[16]; char texto[256]; int orden; int likes; } Post;

static Usuario usuarios[MAX]; static int nUsuarios = 0;
static Post posts[MAX]; static int nPosts = 0;
static int reloj = 0;

static Usuario *buscar(const char *id) {
    for (int i = 0; i < nUsuarios; ++i) if (strcmp(usuarios[i].id, id) == 0) return &usuarios[i];
    return NULL;
}

static void registrar(const char *id, const char *nombre) {
    if (buscar(id)) { printf("  [!] '%s' ya existe\n", id); return; }
    Usuario *u = &usuarios[nUsuarios++];
    strcpy(u->id, id); strcpy(u->nombre, nombre); u->nSig = 0;
    printf("  Registrado %s (@%s)\n", nombre, id);
}

static void seguir(const char *a, const char *b) {
    Usuario *ua = buscar(a);
    if (!ua || !buscar(b)) { printf("  [!] usuario inexistente\n"); return; }
    for (int i = 0; i < ua->nSig; ++i) if (strcmp(ua->siguiendo[i], b) == 0) { printf("  [!] ya lo sigues\n"); return; }
    strcpy(ua->siguiendo[ua->nSig++], b);
    printf("  @%s ahora sigue a @%s\n", a, b);
}

static void publicar(const char *autor, const char *texto) {
    if (!buscar(autor)) { printf("  [!] usuario inexistente\n"); return; }
    if ((int)strlen(texto) > MAX_TEXTO) { printf("  [!] el texto supera los 200 caracteres\n"); return; }
    Post *p = &posts[nPosts++];
    p->id = nPosts; strcpy(p->autor, autor); strcpy(p->texto, texto); p->orden = ++reloj; p->likes = 0;
    printf("  Post #%d publicado por @%s\n", p->id, autor);
}

static void dar_like(int id, const char *usuario) {
    (void)usuario;
    for (int i = 0; i < nPosts; ++i) if (posts[i].id == id) { posts[i].likes++; printf("  like al post #%d\n", id); return; }
    printf("  [!] post inexistente\n");
}

static void feed(const char *id, int deSeguidos) {
    Usuario *u = buscar(id);
    /* imprimir por orden descendente */
    for (int o = reloj; o >= 1; --o)
        for (int i = 0; i < nPosts; ++i)
            if (posts[i].orden == o) {
                int mostrar = 0;
                if (deSeguidos) {
                    for (int k = 0; k < u->nSig; ++k) if (strcmp(u->siguiendo[k], posts[i].autor) == 0) mostrar = 1;
                } else mostrar = (strcmp(posts[i].autor, id) == 0);
                if (mostrar)
                    printf("    [@%s] \"%s\" - %d likes\n", posts[i].autor, posts[i].texto, posts[i].likes);
            }
}

int main(void) {
    printf("=== Simulador de red social ===\n");
    registrar("ecnaksa", "ecnaksa");
    registrar("mouredev", "Brais Moure");
    registrar("mouredev", "Duplicado");
    seguir("ecnaksa", "mouredev");
    seguir("ecnaksa", "mouredev");
    publicar("mouredev", "Nuevo reto del roadmap!");
    publicar("mouredev", "mouredev pro ya esta aqui");
    publicar("ecnaksa", "Resolviendo el reto #46");
    char largo[300]; memset(largo, 'x', 201); largo[201] = '\0';
    publicar("ecnaksa", largo);
    dar_like(1, "ecnaksa");

    printf("\n  Feed de @ecnaksa (sus posts):\n");
    feed("ecnaksa", 0);
    printf("  Feed de @ecnaksa (de quienes sigue):\n");
    feed("ecnaksa", 1);
    return 0;
}
