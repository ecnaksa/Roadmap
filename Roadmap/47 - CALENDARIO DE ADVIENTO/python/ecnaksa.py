"""
#47 - CALENDARIO DE ADVIENTO (aDEViento)

Dibuja un calendario del 1 al 24 en 6 columnas. Cada día es una cuadrícula de
4x3 con bordes de asteriscos y el número en el centro. Al "descubrir" un día,
su cuadrícula queda cubierta de asteriscos (sin mostrar el número).

=========================== TEORÍA ===========================
Reto de DIBUJO POR TERMINAL (ASCII art) + gestión de estado (qué días están
descubiertos). La clave es componer una cuadrícula de celdas de tamaño fijo
fila a fila.

============================ PRÁCTICA ========================
"""

from __future__ import annotations

COLUMNAS = 6
DIAS = 24


def _celda(dia: int, descubierto: bool) -> list[str]:
    """Devuelve las 3 líneas (4 chars) de la cuadrícula de un día."""
    centro = "****" if descubierto else f"*{dia:02d}*"
    return ["****", centro, "****"]


def render(descubiertos: set[int]) -> str:
    lineas: list[str] = []
    for inicio in range(1, DIAS + 1, COLUMNAS):
        dias_fila = range(inicio, min(inicio + COLUMNAS, DIAS + 1))
        celdas = [_celda(d, d in descubiertos) for d in dias_fila]
        for i in range(3):                       # 3 líneas por fila de celdas
            lineas.append(" ".join(celda[i] for celda in celdas))
        lineas.append("")                        # espacio entre filas
    return "\n".join(lineas)


def seleccionar(descubiertos: set[int], dia: int) -> str:
    if not 1 <= dia <= DIAS:
        return f"[!] El día debe estar entre 1 y {DIAS}"
    if dia in descubiertos:
        return f"[!] El día {dia} ya estaba descubierto"
    descubiertos.add(dia)
    return f"🎁 ¡Has abierto el día {dia}!"


def jugar() -> None:
    """Modo interactivo real (usa input)."""
    descubiertos: set[int] = set()
    while len(descubiertos) < DIAS:
        print(render(descubiertos))
        entrada = input("¿Qué día quieres descubrir? (1-24, 'q' para salir): ").strip()
        if entrada.lower() == "q":
            break
        if entrada.isdigit():
            print(seleccionar(descubiertos, int(entrada)))
        else:
            print("[!] Introduce un número válido")


def demo() -> None:
    print("=== Calendario de adviento (inicial) ===")
    descubiertos: set[int] = set()
    print(render(descubiertos))
    for dia in (1, 5, 24, 5):   # el último (5 repetido) provoca aviso
        print(seleccionar(descubiertos, dia))
    print("\n=== Tras descubrir los días 1, 5 y 24 ===")
    print(render(descubiertos))


if __name__ == "__main__":
    demo()
    # Para jugar de verdad, descomenta:
    # jugar()
