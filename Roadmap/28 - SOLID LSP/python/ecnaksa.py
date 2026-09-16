"""
#28 - SOLID: LSP (Liskov Substitution Principle)

=========================== TEORÍA ===========================
LSP — Principio de Sustitución de Liskov:
  "Los objetos de una subclase deben poder sustituir a los de su superclase
   sin alterar el correcto funcionamiento del programa."
Si el código funciona con la clase base, debe seguir funcionando con
CUALQUIER subclase. Romper esto (p. ej. una subclase que lanza un error donde
la base no lo hace) viola el LSP.

============================ PRÁCTICA ========================
"""

from abc import ABC, abstractmethod


# ---------- INCORRECTO: la subclase rompe el contrato de la base ----------
class Ave:
    def volar(self) -> str:
        return "Vuela alto"


class PinguinoMal(Ave):
    def volar(self) -> str:
        # Un pingüino NO vuela: lanzar aquí rompe el código que espera un Ave.
        raise NotImplementedError("¡Los pingüinos no vuelan!")


# ---------- CORRECTO: jerarquía en la que todas las subclases cumplen ----------
class Vehiculo(ABC):
    def __init__(self, nombre: str):
        self.nombre = nombre
        self.velocidad = 0

    @abstractmethod
    def acelerar(self, incremento: int) -> None: ...

    @abstractmethod
    def frenar(self, decremento: int) -> None: ...


class Coche(Vehiculo):
    def acelerar(self, incremento): self.velocidad += incremento
    def frenar(self, decremento): self.velocidad = max(0, self.velocidad - decremento)


class Bicicleta(Vehiculo):
    def acelerar(self, incremento): self.velocidad += min(incremento, 5)  # límite humano
    def frenar(self, decremento): self.velocidad = max(0, self.velocidad - decremento)


class Tren(Vehiculo):
    def acelerar(self, incremento): self.velocidad += incremento * 2       # potente
    def frenar(self, decremento): self.velocidad = max(0, self.velocidad - decremento)


def prueba_lsp(vehiculo: Vehiculo) -> None:
    """Funciona con CUALQUIER Vehiculo -> demuestra el LSP."""
    vehiculo.acelerar(10)
    vehiculo.frenar(3)
    print(f"  {vehiculo.nombre:10} -> velocidad final {vehiculo.velocidad}")


if __name__ == "__main__":
    print("=== LSP: todas las subclases son sustituibles ===")
    for v in (Coche("Coche"), Bicicleta("Bicicleta"), Tren("Tren")):
        prueba_lsp(v)  # no hace falta saber el tipo concreto

    print("\n=== Contraejemplo (viola LSP) ===")
    try:
        PinguinoMal().volar()
    except NotImplementedError as e:
        print(f"  El código que trataba al pingüino como Ave falla: {e}")
