"""
#23 - SINGLETON

=========================== TEORÍA ===========================
El patrón SINGLETON garantiza que una clase tenga UNA ÚNICA instancia y
proporciona un punto de acceso global a ella. Útil para recursos compartidos:
configuración, conexión a base de datos, sesión de usuario, logger...

En Python se puede implementar sobrescribiendo __new__ para devolver siempre
la misma instancia. (Alternativas: un módulo, un decorador o una metaclase.)

============================ PRÁCTICA ========================
"""

from __future__ import annotations
from typing import Optional


class Singleton:
    _instancia: Optional[Singleton] = None

    def __new__(cls) -> "Singleton":
        if cls._instancia is None:
            cls._instancia = super().__new__(cls)
        return cls._instancia


# ----------------------- RETO EXTRA -----------------------


class SesionUsuario:
    """Sesión única de la aplicación (singleton)."""

    _instancia: Optional[SesionUsuario] = None

    def __new__(cls) -> "SesionUsuario":
        if cls._instancia is None:
            cls._instancia = super().__new__(cls)
            cls._instancia._usuario = None
        return cls._instancia

    def iniciar_sesion(self, id_: int, username: str, nombre: str, email: str) -> None:
        self._usuario = {"id": id_, "username": username, "nombre": nombre, "email": email}

    def usuario_actual(self) -> Optional[dict]:
        return self._usuario

    def cerrar_sesion(self) -> None:
        self._usuario = None


if __name__ == "__main__":
    print("=== Singleton genérico ===")
    a = Singleton()
    b = Singleton()
    print(f"  a is b -> {a is b} (misma instancia)")

    print("\n=== Reto extra: sesión de usuario ===")
    sesion1 = SesionUsuario()
    sesion1.iniciar_sesion(1, "ecnaksa", "ecnaksa dev", "hola@ecnaksa.dev")

    sesion2 = SesionUsuario()  # se obtiene la MISMA sesión
    print(f"  sesion1 is sesion2 -> {sesion1 is sesion2}")
    print(f"  Usuario desde sesion2: {sesion2.usuario_actual()}")

    sesion2.cerrar_sesion()
    print(f"  Tras cerrar en sesion2, sesion1 ve: {sesion1.usuario_actual()}")
