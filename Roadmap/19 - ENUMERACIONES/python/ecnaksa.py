"""
#19 - ENUMERACIONES

=========================== TEORÍA ===========================
Una ENUMERACIÓN (Enum) es un conjunto de nombres simbólicos ligados a valores
constantes y únicos. Aportan legibilidad y seguridad frente a usar "números
mágicos" o cadenas sueltas. En Python se usa el módulo `enum`:
  - class Color(Enum): ROJO = 1 ...
  - Cada miembro tiene .name y .value.
  - Se puede iterar sobre la enumeración y acceder por valor: Color(1).

============================ PRÁCTICA ========================
"""

from enum import Enum, auto


class DiaSemana(Enum):
    LUNES = 1
    MARTES = 2
    MIERCOLES = 3
    JUEVES = 4
    VIERNES = 5
    SABADO = 6
    DOMINGO = 7


def nombre_del_dia(numero: int) -> str:
    try:
        return DiaSemana(numero).name.capitalize()
    except ValueError:
        return "Día no válido (usa 1-7)"


# ----------------------- RETO EXTRA -----------------------


class EstadoPedido(Enum):
    PENDIENTE = auto()
    ENVIADO = auto()
    ENTREGADO = auto()
    CANCELADO = auto()


class Pedido:
    def __init__(self, identificador: int) -> None:
        self.identificador = identificador
        self.estado = EstadoPedido.PENDIENTE

    def enviar(self) -> None:
        if self.estado is EstadoPedido.PENDIENTE:
            self.estado = EstadoPedido.ENVIADO
        else:
            print(f"  [!] No se puede enviar desde {self.estado.name}")

    def entregar(self) -> None:
        if self.estado is EstadoPedido.ENVIADO:
            self.estado = EstadoPedido.ENTREGADO
        else:
            print(f"  [!] No se puede entregar si no está ENVIADO (está {self.estado.name})")

    def cancelar(self) -> None:
        if self.estado in (EstadoPedido.PENDIENTE, EstadoPedido.ENVIADO):
            self.estado = EstadoPedido.CANCELADO
        else:
            print(f"  [!] No se puede cancelar desde {self.estado.name}")

    def describir(self) -> str:
        textos = {
            EstadoPedido.PENDIENTE: "está pendiente de envío",
            EstadoPedido.ENVIADO: "va de camino",
            EstadoPedido.ENTREGADO: "ha sido entregado",
            EstadoPedido.CANCELADO: "fue cancelado",
        }
        return f"Pedido #{self.identificador} {textos[self.estado]}"


if __name__ == "__main__":
    print("=== Días de la semana ===")
    for n in (1, 5, 7, 9):
        print(f"  {n} -> {nombre_del_dia(n)}")

    print("\n=== Reto extra: gestión de estado de pedidos ===")
    p1 = Pedido(1)
    print(f"  {p1.describir()}")
    p1.enviar()
    print(f"  {p1.describir()}")
    p1.entregar()
    print(f"  {p1.describir()}")

    print("  --- Pedido 2: intento de entregar sin enviar ---")
    p2 = Pedido(2)
    p2.entregar()                 # inválido
    p2.cancelar()
    print(f"  {p2.describir()}")
