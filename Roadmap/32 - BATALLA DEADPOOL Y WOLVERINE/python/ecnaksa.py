"""
#32 - BATALLA DEADPOOL Y WOLVERINE

Simula un combate por turnos entre Deadpool y Wolverine con daño aleatorio,
regeneración al recibir el golpe máximo y probabilidad de evasión.

=========================== TEORÍA ===========================
Reto de simulación por turnos. Modelamos cada personaje con una clase que
guarda su estado (vida, si debe regenerar) y su comportamiento (atacar,
evadir). El bucle principal alterna turnos hasta que uno cae.

============================ PRÁCTICA ========================
"""

from __future__ import annotations

import random
import time
from dataclasses import dataclass


@dataclass
class Luchador:
    nombre: str
    vida: int
    dano_min: int
    dano_max: int
    prob_evasion: float
    debe_regenerar: bool = False

    def atacar(self) -> tuple[int, bool]:
        """Devuelve (daño, es_maximo)."""
        dano = random.randint(self.dano_min, self.dano_max)
        return dano, dano == self.dano_max

    def evade(self) -> bool:
        return random.random() < self.prob_evasion

    def esta_vivo(self) -> bool:
        return self.vida > 0


def batalla(a: Luchador, b: Luchador, pausa: float = 1.0, verboso: bool = True) -> Luchador:
    def log(msg: str) -> None:
        if verboso:
            print(msg)

    turno = 0
    atacante, defensor = a, b
    while a.esta_vivo() and b.esta_vivo():
        turno += 1
        log(f"\n--- Turno {turno} ---")
        if pausa and verboso:
            time.sleep(pausa)

        if atacante.debe_regenerar:
            log(f"  {atacante.nombre} se regenera y pierde el turno.")
            atacante.debe_regenerar = False
        else:
            dano, es_maximo = atacante.atacar()
            if defensor.evade():
                log(f"  {atacante.nombre} ataca por {dano}, ¡pero {defensor.nombre} lo esquiva!")
            else:
                defensor.vida -= dano
                extra = " (¡golpe máximo! el rival deberá regenerarse)" if es_maximo else ""
                log(f"  {atacante.nombre} inflige {dano} de daño{extra}.")
                if es_maximo:
                    defensor.debe_regenerar = True

        log(f"  Vida -> {a.nombre}: {max(0, a.vida)} | {b.nombre}: {max(0, b.vida)}")
        atacante, defensor = defensor, atacante

    ganador = a if a.esta_vivo() else b
    log(f"\n🏆 ¡{ganador.nombre} gana la batalla!")
    return ganador


def demo() -> None:
    random.seed(7)
    deadpool = Luchador("Deadpool", vida=300, dano_min=10, dano_max=100, prob_evasion=0.25)
    wolverine = Luchador("Wolverine", vida=300, dano_min=10, dano_max=120, prob_evasion=0.20)
    print("=== ¡Deadpool vs Wolverine! ===")
    batalla(deadpool, wolverine, pausa=0)  # pausa=0 para la demo; usa 1 para el efecto real


if __name__ == "__main__":
    demo()
