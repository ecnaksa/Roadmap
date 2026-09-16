"""
#48 - ÁRBOL DE NAVIDAD

Crea un árbol de Navidad de altura dinámica y permite decorarlo: estrella (@),
bolas (o, de dos en dos), luces (+ encendidas / * apagadas, de tres en tres).
Una luz y una bola no pueden ocupar el mismo sitio.

=========================== TEORÍA ===========================
Reto de DIBUJO POR TERMINAL + gestión de estado con conjuntos de posiciones.
Cada posición de follaje es una coordenada (fila, columna). Bolas y luces se
guardan en conjuntos disjuntos; al renderizar se decide qué símbolo mostrar.

============================ PRÁCTICA ========================
"""

from __future__ import annotations

import random


class ArbolNavidad:
    def __init__(self, altura: int) -> None:
        if altura < 1:
            raise ValueError("La altura debe ser >= 1")
        self.altura = altura
        self.apex = (0, 0)
        self.estrella = False
        self.bolas: set[tuple[int, int]] = set()
        self.luces: set[tuple[int, int]] = set()
        self.luces_encendidas = True

    # --- posiciones ---
    def _todas(self) -> set[tuple[int, int]]:
        return {(i, c) for i in range(self.altura) for c in range(2 * i + 1)}

    def _libres(self) -> list[tuple[int, int]]:
        ocupadas = self.bolas | self.luces | {self.apex}
        return list(self._todas() - ocupadas)

    # --- estrella ---
    def estrella_toggle(self) -> str:
        self.estrella = not self.estrella
        return "⭐ Estrella añadida" if self.estrella else "Estrella retirada"

    # --- bolas ---
    def anadir_bolas(self) -> str:
        libres = self._libres()
        if len(libres) < 2:
            return "[!] No hay sitio para 2 bolas más"
        for pos in random.sample(libres, 2):
            self.bolas.add(pos)
        return "🔴 Añadidas 2 bolas"

    def quitar_bolas(self) -> str:
        if len(self.bolas) < 2:
            return "[!] No hay 2 bolas que quitar"
        for pos in random.sample(list(self.bolas), 2):
            self.bolas.discard(pos)
        return "Retiradas 2 bolas"

    # --- luces ---
    def anadir_luces(self) -> str:
        libres = self._libres()
        if len(libres) < 3:
            return "[!] No hay sitio para 3 luces más"
        for pos in random.sample(libres, 3):
            self.luces.add(pos)
        return "💡 Añadidas 3 luces"

    def quitar_luces(self) -> str:
        if len(self.luces) < 3:
            return "[!] No hay 3 luces que quitar"
        for pos in random.sample(list(self.luces), 3):
            self.luces.discard(pos)
        return "Retiradas 3 luces"

    def interruptor(self) -> str:
        self.luces_encendidas = not self.luces_encendidas
        return "🔆 Luces encendidas" if self.luces_encendidas else "🌙 Luces apagadas"

    # --- render ---
    def _simbolo(self, pos: tuple[int, int]) -> str:
        if pos == self.apex and self.estrella:
            return "@"
        if pos in self.bolas:
            return "o"
        if pos in self.luces:
            return "+" if self.luces_encendidas else "*"
        return "*"

    def dibujar(self) -> str:
        base = 2 * self.altura - 1
        lineas = []
        for i in range(self.altura):
            fila = "".join(self._simbolo((i, c)) for c in range(2 * i + 1))
            lineas.append(" " * (self.altura - 1 - i) + fila)
        tronco = " " * max(0, (base - 3) // 2) + "|||"
        lineas.extend([tronco, tronco])
        return "\n".join(lineas)


def demo() -> None:
    random.seed(48)
    arbol = ArbolNavidad(7)
    print("=== Árbol base (altura 7) ===")
    print(arbol.dibujar())

    print("\n>", arbol.estrella_toggle())
    print(">", arbol.anadir_bolas())
    print(">", arbol.anadir_luces())
    print(">", arbol.anadir_luces())
    print("\n=== Árbol decorado ===")
    print(arbol.dibujar())

    print("\n>", arbol.interruptor())
    print("=== Con las luces apagadas (mantienen su posición) ===")
    print(arbol.dibujar())


if __name__ == "__main__":
    demo()
