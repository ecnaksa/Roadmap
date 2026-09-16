"""
#39 - BATMAN DAY (reto doble)

RETO 1: calcular la fecha del Batman Day (tercer sábado de septiembre) hasta
        su 100 aniversario.
RETO 2: sistema de seguridad de la Batcueva sobre una cuadrícula 20x20 que
        detecta el área 3x3 con mayor concentración de amenazas.

=========================== TEORÍA ===========================
RETO 1: manejo de FECHAS y calendario (localizar el n-ésimo día de la semana
de un mes). RETO 2: recorrido de MATRICES con "ventana deslizante" 3x3 para
encontrar el máximo local, más geometría básica (distancia Manhattan).

============================ PRÁCTICA ========================
"""

from __future__ import annotations

import calendar
from datetime import date

PRIMER_ANIO = 1939  # primera aparición de Batman
UMBRAL = 20


# ----------------------- RETO 1 -----------------------


def batman_day(anio: int) -> date:
    """Tercer sábado de septiembre del año dado."""
    c = calendar.Calendar()
    sabados = [
        d for d in c.itermonthdates(anio, 9)
        if d.month == 9 and d.weekday() == calendar.SATURDAY
    ]
    return sabados[2]  # el tercero


def reto1() -> None:
    print("=== RETO 1: Batman Day hasta el 100 aniversario ===")
    for aniversario in range(85, 101):          # del 85 (2024) al 100
        anio = PRIMER_ANIO + aniversario
        fecha = batman_day(anio)
        print(f"  {aniversario}º aniversario ({anio}): {fecha.strftime('%A %d/%m/%Y')}")


# ----------------------- RETO 2 -----------------------


def analizar_amenazas(sensores: list[tuple[int, int, int]]) -> dict:
    """Encuentra el área 3x3 con mayor suma de amenazas en un grid 20x20."""
    grid = [[0] * 20 for _ in range(20)]
    for x, y, amenaza in sensores:
        if 0 <= x < 20 and 0 <= y < 20:
            grid[y][x] = amenaza

    mejor = {"centro": (0, 0), "suma": -1}
    for cy in range(1, 19):
        for cx in range(1, 19):
            suma = sum(
                grid[cy + dy][cx + dx]
                for dy in (-1, 0, 1)
                for dx in (-1, 0, 1)
            )
            if suma > mejor["suma"]:
                mejor = {"centro": (cx, cy), "suma": suma}

    cx, cy = mejor["centro"]
    mejor["distancia"] = abs(cx) + abs(cy)          # Manhattan desde (0,0)
    mejor["protocolo"] = mejor["suma"] > UMBRAL
    return mejor


def reto2() -> None:
    print("\n=== RETO 2: seguridad de la Batcueva ===")
    sensores = [
        (5, 5, 8), (6, 5, 7), (5, 6, 9), (6, 6, 6),   # foco caliente ~ (5-6, 5-6)
        (1, 1, 2), (18, 18, 10), (10, 10, 3), (4, 5, 4),
    ]
    r = analizar_amenazas(sensores)
    print(f"  Centro del área más amenazada: {r['centro']}")
    print(f"  Suma de amenazas (3x3):        {r['suma']}")
    print(f"  Distancia a la Batcueva (0,0): {r['distancia']}")
    print(f"  ¿Activar protocolo? (>{UMBRAL}): {'🚨 SÍ' if r['protocolo'] else 'no'}")


if __name__ == "__main__":
    reto1()
    reto2()
