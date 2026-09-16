"""
#30 - SOLID: DIP (Dependency Inversion Principle)

=========================== TEORÍA ===========================
DIP — Principio de Inversión de Dependencias:
  1. Los módulos de alto nivel no deben depender de los de bajo nivel;
     ambos deben depender de ABSTRACCIONES.
  2. Las abstracciones no deben depender de los detalles; los detalles
     deben depender de las abstracciones.
En la práctica: en lugar de instanciar clases concretas dentro de una clase,
se le "inyecta" la dependencia a través de una abstracción (interfaz).

============================ PRÁCTICA ========================
"""

from abc import ABC, abstractmethod


# ---------- INCORRECTO: alto nivel depende de una implementación concreta ----------
class EmailConcreto:
    def enviar(self, mensaje): print(f"  (email) {mensaje}")


class NotificadorMal:
    def __init__(self):
        self.email = EmailConcreto()      # acoplado a una clase concreta

    def notificar(self, mensaje):
        self.email.enviar(mensaje)        # imposible cambiar el canal sin editar


# ---------- CORRECTO: se depende de una abstracción ----------
class CanalNotificacion(ABC):
    @abstractmethod
    def enviar(self, mensaje: str) -> None: ...


class Email(CanalNotificacion):
    def enviar(self, mensaje): print(f"  📧 EMAIL: {mensaje}")


class SMS(CanalNotificacion):
    def enviar(self, mensaje): print(f"  📱 SMS: {mensaje}")


class Push(CanalNotificacion):
    def enviar(self, mensaje): print(f"  🔔 PUSH: {mensaje}")


class ServicioNotificaciones:
    """Alto nivel: depende de la abstracción, no de las implementaciones."""

    def __init__(self, canales: list[CanalNotificacion]):
        self.canales = canales           # inyección de dependencias

    def enviar(self, mensaje: str) -> None:
        for canal in self.canales:
            canal.enviar(mensaje)


if __name__ == "__main__":
    print("=== DIP: el servicio no conoce las implementaciones concretas ===")
    servicio = ServicioNotificaciones([Email(), SMS(), Push()])
    servicio.enviar("¡Nuevo reto disponible en el roadmap!")

    print("\n=== Comprobación del principio ===")
    # Podemos cambiar/añadir canales sin tocar ServicioNotificaciones
    solo_push = ServicioNotificaciones([Push()])
    solo_push.enviar("Recordatorio")
    print("  Se cambió el canal sin modificar el módulo de alto nivel -> cumple DIP")
