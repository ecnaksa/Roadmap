"""
#27 - SOLID: OCP (Open/Closed Principle)

=========================== TEORÍA ===========================
OCP — Principio Abierto/Cerrado:
  "Las entidades de software deben estar ABIERTAS a la extensión, pero
   CERRADAS a la modificación."
Debemos poder añadir comportamiento nuevo SIN tocar el código ya probado.
La clave: programar contra abstracciones (interfaces/clases base) y añadir
nuevas implementaciones en lugar de editar cadenas de if/elif.

============================ PRÁCTICA ========================
"""

from abc import ABC, abstractmethod


# ---------- INCORRECTO: cada nueva operación exige modificar la clase ----------
class CalculadoraMal:
    def operar(self, op: str, a: float, b: float) -> float:
        if op == "suma":
            return a + b
        elif op == "resta":
            return a - b
        # Añadir "potencia" obligaría a MODIFICAR este método (viola OCP).
        raise ValueError("Operación no soportada")


# ---------- CORRECTO: se extiende creando nuevas clases ----------
class Operacion(ABC):
    @abstractmethod
    def calcular(self, a: float, b: float) -> float: ...


class Suma(Operacion):
    def calcular(self, a, b): return a + b


class Resta(Operacion):
    def calcular(self, a, b): return a - b


class Multiplicacion(Operacion):
    def calcular(self, a, b): return a * b


class Division(Operacion):
    def calcular(self, a, b):
        if b == 0:
            raise ZeroDivisionError("No se puede dividir entre 0")
        return a / b


class Calculadora:
    """No necesita cambiar cuando se añaden nuevas operaciones."""

    def __init__(self):
        self._operaciones: dict[str, Operacion] = {}

    def registrar(self, nombre: str, operacion: Operacion) -> None:
        self._operaciones[nombre] = operacion

    def operar(self, nombre: str, a: float, b: float) -> float:
        if nombre not in self._operaciones:
            raise ValueError(f"Operación '{nombre}' no registrada")
        return self._operaciones[nombre].calcular(a, b)


# ---------- EXTENSIÓN: quinta operación SIN tocar Calculadora ----------
class Potencia(Operacion):
    def calcular(self, a, b): return a ** b


if __name__ == "__main__":
    print("=== OCP: calculadora extensible ===")
    calc = Calculadora()
    for nombre, op in {
        "suma": Suma(), "resta": Resta(),
        "mult": Multiplicacion(), "div": Division(),
    }.items():
        calc.registrar(nombre, op)

    print(f"  suma(4,2) = {calc.operar('suma', 4, 2)}")
    print(f"  resta(4,2) = {calc.operar('resta', 4, 2)}")
    print(f"  mult(4,2) = {calc.operar('mult', 4, 2)}")
    print(f"  div(4,2) = {calc.operar('div', 4, 2)}")

    # Se agrega la potencia sin modificar código existente -> cumple OCP
    calc.registrar("pot", Potencia())
    print(f"  pot(4,2) = {calc.operar('pot', 4, 2)}   <- añadida sin tocar Calculadora")
