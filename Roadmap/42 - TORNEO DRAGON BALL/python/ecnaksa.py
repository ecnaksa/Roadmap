"""
#42 - TORNEO DRAGON BALL (Sparking! ZERO)

Simula un Torneo de Artes Marciales por rondas eliminatorias entre luchadores
con atributos de velocidad, ataque y defensa.

=========================== TEORÍA ===========================
Reto de SIMULACIÓN + estructura de torneo (bracket). Se modela cada luchador
con una clase, se define la mecánica de combate y se organiza un torneo por
eliminación que requiere un número de participantes potencia de 2.

Reglas de combate:
  - Empieza atacando el de más velocidad.
  - Daño = ataque_atacante - defensa_oponente.
  - 20% de probabilidad de esquivar.
  - Si la defensa supera al ataque, recibe el 10% del ataque.
  - La batalla acaba cuando un luchador se queda sin salud.

============================ PRÁCTICA ========================
"""

from __future__ import annotations

import math
import random
from dataclasses import dataclass


@dataclass
class Luchador:
    nombre: str
    velocidad: int
    ataque: int
    defensa: int
    salud: int = 100

    def reiniciar(self) -> None:
        self.salud = 100

    def esta_vivo(self) -> bool:
        return self.salud > 0


def _dano(atacante: Luchador, oponente: Luchador) -> int:
    if atacante.ataque > oponente.defensa:
        return atacante.ataque - oponente.defensa
    return max(1, round(atacante.ataque * 0.10))  # golpe mínimo


def combate(a: Luchador, b: Luchador, verboso: bool = True) -> Luchador:
    a.reiniciar()
    b.reiniciar()
    atacante, defensor = (a, b) if a.velocidad >= b.velocidad else (b, a)
    if verboso:
        print(f"    ⚔️  {a.nombre} vs {b.nombre} (empieza {atacante.nombre})")

    while a.esta_vivo() and b.esta_vivo():
        if random.random() < 0.20:
            if verboso:
                print(f"      {defensor.nombre} esquiva el ataque de {atacante.nombre}")
        else:
            dano = _dano(atacante, defensor)
            defensor.salud -= dano
            if verboso:
                print(f"      {atacante.nombre} golpea por {dano} -> {defensor.nombre}: {max(0, defensor.salud)} de salud")
        atacante, defensor = defensor, atacante

    ganador = a if a.esta_vivo() else b
    if verboso:
        print(f"    ✅ Gana {ganador.nombre}")
    return ganador


def torneo(luchadores: list[Luchador], verboso: bool = True) -> Luchador:
    n = len(luchadores)
    if n < 2 or (n & (n - 1)) != 0:
        raise ValueError("El número de luchadores debe ser potencia de 2 (2, 4, 8...)")

    ronda = luchadores[:]
    random.shuffle(ronda)
    numero_ronda = 1
    while len(ronda) > 1:
        if verboso:
            print(f"\n=== Ronda {numero_ronda} ({len(ronda)} luchadores) ===")
        siguiente = []
        for i in range(0, len(ronda), 2):
            siguiente.append(combate(ronda[i], ronda[i + 1], verboso))
        ronda = siguiente
        random.shuffle(ronda)
        numero_ronda += 1

    campeon = ronda[0]
    if verboso:
        print(f"\n🏆 ¡{campeon.nombre} es el campeón del torneo!")
    return campeon


def demo() -> None:
    random.seed(42)
    luchadores = [
        Luchador("Goku", 90, 85, 70),
        Luchador("Vegeta", 85, 88, 65),
        Luchador("Piccolo", 70, 75, 80),
        Luchador("Freezer", 95, 90, 60),
        Luchador("Gohan", 80, 82, 72),
        Luchador("Cell", 78, 86, 78),
        Luchador("Krilin", 65, 60, 55),
        Luchador("Trunks", 82, 80, 68),
    ]
    print("=== Torneo de Artes Marciales (8 luchadores) ===")
    torneo(luchadores)


if __name__ == "__main__":
    demo()
