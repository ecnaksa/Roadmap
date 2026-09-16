"""
#09 - HERENCIA

=========================== TEORÍA ===========================
La HERENCIA permite que una clase (subclase/hija) reutilice y extienda el
comportamiento de otra (superclase/padre). Favorece la reutilización de
código y el POLIMORFISMO: distintas subclases responden al mismo método de
forma diferente.

En Python:
  - `class Hija(Padre):` establece la herencia.
  - `super().__init__(...)` llama al inicializador del padre.
  - Sobrescribir (override) un método = redefinirlo en la hija.

============================ PRÁCTICA ========================
"""

from __future__ import annotations


class Animal:
    def __init__(self, nombre: str) -> None:
        self.nombre = nombre

    def hacer_sonido(self) -> str:
        return "..."

    def describir(self) -> None:
        print(f"  {self.nombre} dice: {self.hacer_sonido()}")


class Perro(Animal):
    def hacer_sonido(self) -> str:      # override
        return "¡Guau!"


class Gato(Animal):
    def hacer_sonido(self) -> str:      # override
        return "¡Miau!"


# ----------------------- RETO EXTRA -----------------------
# Jerarquía de una empresa de desarrollo.


class Empleado:
    def __init__(self, identificador: int, nombre: str) -> None:
        self.identificador = identificador
        self.nombre = nombre
        self.a_cargo: list[Empleado] = []

    def anadir_subordinado(self, empleado: Empleado) -> None:
        self.a_cargo.append(empleado)

    def rol(self) -> str:
        return "Empleado"

    def __str__(self) -> str:
        cargo = f", a cargo de {len(self.a_cargo)}" if self.a_cargo else ""
        return f"[{self.identificador}] {self.nombre} — {self.rol()}{cargo}"


class Programador(Empleado):
    def __init__(self, identificador: int, nombre: str, lenguaje: str) -> None:
        super().__init__(identificador, nombre)
        self.lenguaje = lenguaje

    def rol(self) -> str:
        return f"Programador ({self.lenguaje})"

    def programar(self) -> str:
        return f"{self.nombre} programa en {self.lenguaje}"


class GerenteProyectos(Empleado):
    def rol(self) -> str:
        return "Gerente de Proyectos"

    def planificar(self) -> str:
        return f"{self.nombre} planifica el proyecto"


class Gerente(Empleado):
    def rol(self) -> str:
        return "Gerente"

    def aprobar_presupuesto(self) -> str:
        return f"{self.nombre} aprueba el presupuesto"


if __name__ == "__main__":
    print("=== Herencia: Animal -> Perro / Gato ===")
    for animal in (Perro("Toby"), Gato("Michi"), Animal("Genérico")):
        animal.describir()

    print("\n=== Reto extra: jerarquía de empresa ===")
    dev1 = Programador(3, "Ana", "Python")
    dev2 = Programador(4, "Luis", "Rust")
    pm = GerenteProyectos(2, "Marta")
    ceo = Gerente(1, "Brais")

    pm.anadir_subordinado(dev1)
    pm.anadir_subordinado(dev2)
    ceo.anadir_subordinado(pm)

    for e in (ceo, pm, dev1, dev2):
        print(f"  {e}")
    print(f"  {dev1.programar()}")
    print(f"  {pm.planificar()}")
    print(f"  {ceo.aprobar_presupuesto()}")
