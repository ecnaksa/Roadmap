"""
#33 - RESCATANDO A MICKEY

Mickey está atrapado en un laberinto mágico de 6x6. El usuario lo guía
(arriba/abajo/izquierda/derecha) hasta la salida, validando límites y
obstáculos.

=========================== TEORÍA ===========================
Reto de MATRICES (listas de listas). Se representa el laberinto como una
cuadrícula, se controla la posición de Mickey con coordenadas (fila, col) y
se validan los movimientos antes de aplicarlos.

============================ PRÁCTICA ========================
"""

from __future__ import annotations

VACIO, OBSTACULO, MICKEY, SALIDA = "⬜️", "⬛️", "🐭", "🚪"

MOVIMIENTOS = {
    "arriba": (-1, 0),
    "abajo": (1, 0),
    "izquierda": (0, -1),
    "derecha": (0, 1),
}


class Laberinto:
    def __init__(self) -> None:
        # 0 = vacío, 1 = obstáculo
        plano = [
            [0, 0, 0, 1, 0, 0],
            [1, 1, 0, 1, 0, 1],
            [0, 0, 0, 0, 0, 0],
            [0, 1, 1, 1, 1, 0],
            [0, 0, 0, 0, 1, 0],
            [1, 1, 0, 1, 0, 0],
        ]
        self.grid = [[OBSTACULO if c else VACIO for c in fila] for fila in plano]
        self.pos = (0, 0)
        self.salida = (5, 5)
        self.grid[5][5] = SALIDA

    def dibujar(self) -> None:
        for f, fila in enumerate(self.grid):
            print("  " + "".join(
                MICKEY if (f, c) == self.pos else celda
                for c, celda in enumerate(fila)
            ))

    def mover(self, direccion: str) -> str:
        if direccion not in MOVIMIENTOS:
            return "Dirección no válida (usa arriba/abajo/izquierda/derecha)."
        df, dc = MOVIMIENTOS[direccion]
        nf, nc = self.pos[0] + df, self.pos[1] + dc
        if not (0 <= nf < 6 and 0 <= nc < 6):
            return "🚧 ¡Fuera de los límites del laberinto!"
        if self.grid[nf][nc] == OBSTACULO:
            return "🧱 ¡Hay un obstáculo ahí!"
        self.pos = (nf, nc)
        return "✅ Movimiento realizado."

    def ha_escapado(self) -> bool:
        return self.pos == self.salida


def jugar() -> None:
    """Modo interactivo real (usa input)."""
    lab = Laberinto()
    print("¡Ayuda a Mickey a escapar! (arriba/abajo/izquierda/derecha)")
    while not lab.ha_escapado():
        lab.dibujar()
        print(lab.mover(input("Movimiento: ").strip().lower()))
    lab.dibujar()
    print("🎉 ¡Mickey ha encontrado la salida!")


def demo() -> None:
    """Demostración con una ruta predefinida que llega a la salida."""
    lab = Laberinto()
    ruta = [
        "derecha", "derecha", "abajo", "abajo", "derecha", "derecha",
        "derecha", "arriba", "arriba", "arriba",  # incluye un intento inválido
        "abajo", "abajo", "abajo", "abajo",
    ]
    print("=== Laberinto inicial ===")
    lab.dibujar()
    for direccion in ruta:
        resultado = lab.mover(direccion)
        print(f"\n> {direccion}: {resultado}")
        lab.dibujar()
        if lab.ha_escapado():
            print("\n🎉 ¡Mickey ha encontrado la salida!")
            return
    print("\n(Fin de la ruta de demostración)")


if __name__ == "__main__":
    demo()
    # Para jugar de verdad, descomenta:
    # jugar()
