"""
#26 - SOLID: SRP (Single Responsibility Principle)

=========================== TEORÍA ===========================
SRP — Principio de Responsabilidad Única:
  "Una clase debe tener una, y solo una, razón para cambiar."
Es decir, cada clase/módulo debe encargarse de UNA sola responsabilidad.
Si una clase mezcla varias (persistencia + lógica + presentación), un cambio
en cualquiera de ellas obliga a tocarla, y aumenta el acoplamiento.

============================ PRÁCTICA ========================
"""

from dataclasses import dataclass, field


# ---------- INCORRECTO: una clase con demasiadas responsabilidades ----------
class BibliotecaMalDisenada:
    """Gestiona libros, usuarios Y préstamos: 3 razones para cambiar."""

    def __init__(self):
        self.libros, self.usuarios, self.prestamos = [], [], []

    def registrar_libro(self, titulo): self.libros.append(titulo)
    def registrar_usuario(self, nombre): self.usuarios.append(nombre)
    def prestar(self, libro, usuario): self.prestamos.append((libro, usuario))
    def guardar_en_bd(self): ...        # ¡además persistencia!
    def enviar_email(self): ...         # ¡y notificaciones!


# ---------- CORRECTO: responsabilidades separadas ----------
@dataclass
class Libro:
    titulo: str
    autor: str
    copias: int


@dataclass
class Usuario:
    nombre: str
    identificacion: str
    email: str


class RepositorioLibros:
    def __init__(self): self._libros: dict[str, Libro] = {}
    def agregar(self, libro: Libro): self._libros[libro.titulo] = libro
    def obtener(self, titulo: str) -> Libro | None: return self._libros.get(titulo)


class RepositorioUsuarios:
    def __init__(self): self._usuarios: dict[str, Usuario] = {}
    def agregar(self, u: Usuario): self._usuarios[u.identificacion] = u
    def obtener(self, ident: str) -> Usuario | None: return self._usuarios.get(ident)


@dataclass
class GestorPrestamos:
    libros: RepositorioLibros
    usuarios: RepositorioUsuarios
    activos: list = field(default_factory=list)

    def prestar(self, titulo: str, ident: str) -> str:
        libro = self.libros.obtener(titulo)
        usuario = self.usuarios.obtener(ident)
        if not libro or not usuario:
            return "Libro o usuario no encontrado"
        if libro.copias <= 0:
            return f"No quedan copias de '{titulo}'"
        libro.copias -= 1
        self.activos.append((titulo, ident))
        return f"'{titulo}' prestado a {usuario.nombre}"

    def devolver(self, titulo: str, ident: str) -> str:
        if (titulo, ident) not in self.activos:
            return "Ese préstamo no existe"
        self.activos.remove((titulo, ident))
        self.libros.obtener(titulo).copias += 1
        return f"'{titulo}' devuelto"


if __name__ == "__main__":
    print("=== SRP: diseño correcto (responsabilidades separadas) ===")
    libros = RepositorioLibros()
    usuarios = RepositorioUsuarios()
    libros.agregar(Libro("Clean Code", "R. Martin", 2))
    usuarios.agregar(Usuario("Ana", "U1", "ana@mail.com"))

    gestor = GestorPrestamos(libros, usuarios)
    print(f"  {gestor.prestar('Clean Code', 'U1')}")
    print(f"  {gestor.prestar('Clean Code', 'U1')}")
    print(f"  {gestor.prestar('Clean Code', 'U1')}  (sin copias)")
    print(f"  {gestor.devolver('Clean Code', 'U1')}")
