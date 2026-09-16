"""
#34 - ÁRBOL GENEALÓGICO (LA CASA DEL DRAGÓN)

Modela un árbol genealógico: personas con id único, nombre, pareja (opcional)
e hijos (opcional). Permite crear/modificar el árbol con validaciones y lo
imprime.

=========================== TEORÍA ===========================
Reto de MODELADO DE RELACIONES (grafo/árbol). Cada persona referencia a otras
por su identificador. Se aplican reglas de negocio (una sola pareja; un hijo
no puede tener más de dos progenitores) para mantener el árbol coherente.

Reglas propias adoptadas para acotar la complejidad:
  - Pareja monógama y simétrica (si A es pareja de B, B lo es de A).
  - Un hijo puede tener como máximo 2 progenitores.

============================ PRÁCTICA ========================
"""

from __future__ import annotations

from dataclasses import dataclass, field


@dataclass
class Persona:
    id: str
    nombre: str
    pareja: str | None = None
    hijos: list[str] = field(default_factory=list)


class ArbolGenealogico:
    def __init__(self) -> None:
        self.personas: dict[str, Persona] = {}
        self._num_progenitores: dict[str, int] = {}

    def anadir_persona(self, id_: str, nombre: str) -> str:
        if id_ in self.personas:
            return f"[!] Ya existe una persona con id '{id_}'"
        self.personas[id_] = Persona(id_, nombre)
        return f"➕ Añadida: {nombre} ({id_})"

    def eliminar_persona(self, id_: str) -> str:
        persona = self.personas.pop(id_, None)
        if not persona:
            return f"[!] No existe '{id_}'"
        if persona.pareja and persona.pareja in self.personas:
            self.personas[persona.pareja].pareja = None
        for p in self.personas.values():
            if id_ in p.hijos:
                p.hijos.remove(id_)
        return f"➖ Eliminada: {persona.nombre}"

    def emparejar(self, id_a: str, id_b: str) -> str:
        a, b = self.personas.get(id_a), self.personas.get(id_b)
        if not a or not b:
            return "[!] Alguna persona no existe"
        if a.pareja or b.pareja:
            return "[!] Una de las personas ya tiene pareja (solo se permite una)"
        a.pareja, b.pareja = id_b, id_a
        return f"💞 {a.nombre} y {b.nombre} son pareja"

    def anadir_hijo(self, id_progenitor: str, id_hijo: str) -> str:
        progenitor = self.personas.get(id_progenitor)
        if not progenitor or id_hijo not in self.personas:
            return "[!] Progenitor o hijo inexistente"
        if self._num_progenitores.get(id_hijo, 0) >= 2:
            return f"[!] {self.personas[id_hijo].nombre} ya tiene 2 progenitores"
        if id_hijo in progenitor.hijos:
            return "[!] Ese hijo ya está asignado a este progenitor"
        progenitor.hijos.append(id_hijo)
        self._num_progenitores[id_hijo] = self._num_progenitores.get(id_hijo, 0) + 1
        # El hijo también lo es de la pareja del progenitor (si la tiene)
        if progenitor.pareja and id_hijo not in self.personas[progenitor.pareja].hijos:
            if self._num_progenitores.get(id_hijo, 0) < 2:
                self.personas[progenitor.pareja].hijos.append(id_hijo)
                self._num_progenitores[id_hijo] += 1
        return f"👶 {self.personas[id_hijo].nombre} es hijo/a de {progenitor.nombre}"

    def imprimir(self, id_raiz: str, nivel: int = 0, visitados: set | None = None) -> None:
        visitados = visitados if visitados is not None else set()
        if id_raiz in visitados or id_raiz not in self.personas:
            return
        visitados.add(id_raiz)
        persona = self.personas[id_raiz]
        pareja = f" ⚭ {self.personas[persona.pareja].nombre}" if persona.pareja else ""
        print("    " * nivel + f"• {persona.nombre}{pareja}")
        for id_hijo in persona.hijos:
            self.imprimir(id_hijo, nivel + 1, visitados)


def demo() -> None:
    arbol = ArbolGenealogico()
    for id_, nombre in [
        ("1", "Viserys I"), ("2", "Alicent"), ("3", "Rhaenyra"), ("4", "Daemon"),
        ("5", "Aegon II"), ("6", "Jacaerys"), ("7", "Lucerys"),
    ]:
        print(f"  {arbol.anadir_persona(id_, nombre)}")

    print()
    print(f"  {arbol.emparejar('1', '2')}")
    print(f"  {arbol.emparejar('3', '4')}")
    print(f"  {arbol.anadir_hijo('1', '3')}")   # Rhaenyra, hija de Viserys (y Alicent en esta versión simplificada)
    print(f"  {arbol.anadir_hijo('2', '5')}")   # Aegon, hijo de Alicent
    print(f"  {arbol.anadir_hijo('3', '6')}")   # Jacaerys
    print(f"  {arbol.anadir_hijo('3', '7')}")   # Lucerys
    print(f"  {arbol.emparejar('3', '1')}")     # inválido: ya tienen pareja

    print("\n=== Árbol genealógico ===")
    arbol.imprimir("1")


if __name__ == "__main__":
    demo()
