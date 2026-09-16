"""
#46 - X VS BLUESKY (simulador de red social)

Simula el comportamiento básico de una red social: usuarios, seguir/dejar de
seguir, posts (máx 200 caracteres), likes y feeds.

=========================== TEORÍA ===========================
Reto de MODELADO DE DOMINIO. Se representan Usuarios y Posts con
identificadores únicos, relaciones de seguimiento (grafo dirigido) y se
generan feeds ordenados por fecha. Se controlan errores de duplicados y
acciones no permitidas.

============================ PRÁCTICA ========================
"""

from __future__ import annotations

import itertools
from dataclasses import dataclass, field
from datetime import datetime, timedelta

MAX_TEXTO = 200


@dataclass
class Post:
    id: int
    autor_id: str
    texto: str
    creado: datetime
    likes: set[str] = field(default_factory=set)


@dataclass
class Usuario:
    id: str
    nombre: str
    siguiendo: set[str] = field(default_factory=set)


class RedSocial:
    def __init__(self) -> None:
        self.usuarios: dict[str, Usuario] = {}
        self.posts: dict[int, Post] = {}
        self._ids = itertools.count(1)

    # --- Usuarios ---
    def registrar(self, id_: str, nombre: str) -> str:
        if id_ in self.usuarios:
            return f"[!] El usuario '{id_}' ya existe"
        self.usuarios[id_] = Usuario(id_, nombre)
        return f"👤 Registrado {nombre} (@{id_})"

    def seguir(self, id_: str, objetivo: str) -> str:
        if id_ not in self.usuarios or objetivo not in self.usuarios:
            return "[!] Usuario inexistente"
        if id_ == objetivo:
            return "[!] No puedes seguirte a ti mismo"
        if objetivo in self.usuarios[id_].siguiendo:
            return "[!] Ya lo sigues"
        self.usuarios[id_].siguiendo.add(objetivo)
        return f"➕ @{id_} ahora sigue a @{objetivo}"

    def dejar_de_seguir(self, id_: str, objetivo: str) -> str:
        if objetivo not in self.usuarios.get(id_, Usuario("", "")).siguiendo:
            return "[!] No lo seguías"
        self.usuarios[id_].siguiendo.discard(objetivo)
        return f"➖ @{id_} deja de seguir a @{objetivo}"

    # --- Posts ---
    def publicar(self, autor_id: str, texto: str, cuando: datetime | None = None) -> str:
        if autor_id not in self.usuarios:
            return "[!] Usuario inexistente"
        if len(texto) > MAX_TEXTO:
            return f"[!] El texto supera los {MAX_TEXTO} caracteres"
        post = Post(next(self._ids), autor_id, texto, cuando or datetime.now())
        self.posts[post.id] = post
        return f"📝 Post #{post.id} publicado por @{autor_id}"

    def eliminar_post(self, post_id: int) -> str:
        if self.posts.pop(post_id, None) is None:
            return "[!] Ese post no existe"
        return f"🗑️  Post #{post_id} eliminado"

    def like(self, post_id: int, usuario_id: str) -> str:
        post = self.posts.get(post_id)
        if not post:
            return "[!] Post inexistente"
        if usuario_id in post.likes:
            return "[!] Ya habías dado like"
        post.likes.add(usuario_id)
        return f"❤️  @{usuario_id} dio like al post #{post_id}"

    def quitar_like(self, post_id: int, usuario_id: str) -> str:
        post = self.posts.get(post_id)
        if not post or usuario_id not in post.likes:
            return "[!] No habías dado like"
        post.likes.discard(usuario_id)
        return f"💔 @{usuario_id} quitó su like del post #{post_id}"

    # --- Feeds ---
    def _formatear(self, post: Post) -> str:
        autor = self.usuarios[post.autor_id]
        return (f"    [@{autor.id}] {autor.nombre}: \"{post.texto}\" "
                f"({post.creado:%Y-%m-%d %H:%M}) · {len(post.likes)} likes")

    def feed_usuario(self, id_: str, limite: int = 10) -> list[str]:
        propios = [p for p in self.posts.values() if p.autor_id == id_]
        propios.sort(key=lambda p: p.creado, reverse=True)
        return [self._formatear(p) for p in propios[:limite]]

    def feed_seguidos(self, id_: str, limite: int = 10) -> list[str]:
        seguidos = self.usuarios[id_].siguiendo
        posts = [p for p in self.posts.values() if p.autor_id in seguidos]
        posts.sort(key=lambda p: p.creado, reverse=True)
        return [self._formatear(p) for p in posts[:limite]]


def demo() -> None:
    red = RedSocial()
    ahora = datetime(2024, 11, 20, 12, 0, 0)
    print("=== Simulador de red social ===")
    print(" ", red.registrar("ecnaksa", "ecnaksa"))
    print(" ", red.registrar("mouredev", "Brais Moure"))
    print(" ", red.registrar("mouredev", "Duplicado"))  # error
    print(" ", red.seguir("ecnaksa", "mouredev"))
    print(" ", red.seguir("ecnaksa", "mouredev"))         # error (ya lo sigue)

    print(" ", red.publicar("mouredev", "¡Nuevo reto del roadmap!", ahora))
    print(" ", red.publicar("mouredev", "mouredev pro ya está aquí 🚀", ahora + timedelta(hours=1)))
    print(" ", red.publicar("ecnaksa", "Resolviendo el reto #46", ahora + timedelta(hours=2)))
    print(" ", red.publicar("ecnaksa", "x" * 201))        # error (>200)
    print(" ", red.like(1, "ecnaksa"))
    print(" ", red.like(1, "ecnaksa"))                     # error (like repetido)

    print("\n  📰 Feed de @ecnaksa (sus posts):")
    print("\n".join(red.feed_usuario("ecnaksa")))
    print("\n  📰 Feed de @ecnaksa (de quienes sigue):")
    print("\n".join(red.feed_seguidos("ecnaksa")))


if __name__ == "__main__":
    demo()
