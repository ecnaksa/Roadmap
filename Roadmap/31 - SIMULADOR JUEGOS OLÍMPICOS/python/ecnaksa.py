"""
#31 - SIMULADOR DE JUEGOS OLÍMPICOS

Simula la celebración de unos JJOO: registro de eventos y participantes,
simulación aleatoria de resultados, reparto de medallas y rankings.

=========================== TEORÍA ===========================
Este reto integra estructuras de datos (dict/list), aleatoriedad (random),
programación orientada a objetos y generación de informes. La clave es
modelar el dominio con clases claras: Participante, Evento y los propios
Juegos como orquestador.

============================ PRÁCTICA ========================
"""

from __future__ import annotations

import random
from collections import Counter
from dataclasses import dataclass, field

MEDALLAS = ("🥇 Oro", "🥈 Plata", "🥉 Bronce")


@dataclass
class Participante:
    nombre: str
    pais: str

    def __str__(self) -> str:
        return f"{self.nombre} ({self.pais})"


@dataclass
class Evento:
    nombre: str
    participantes: list[Participante] = field(default_factory=list)
    podio: list[Participante] = field(default_factory=list)

    def simular(self) -> None:
        if len(self.participantes) < 3:
            raise ValueError(f"'{self.nombre}' necesita al menos 3 participantes")
        clasificacion = random.sample(self.participantes, len(self.participantes))
        self.podio = clasificacion[:3]


class JuegosOlimpicos:
    def __init__(self, sede: str) -> None:
        self.sede = sede
        self.eventos: dict[str, Evento] = {}

    def registrar_evento(self, nombre: str) -> None:
        self.eventos.setdefault(nombre, Evento(nombre))

    def registrar_participante(self, evento: str, nombre: str, pais: str) -> None:
        self.eventos[evento].participantes.append(Participante(nombre, pais))

    def simular_todo(self) -> None:
        for evento in self.eventos.values():
            evento.simular()

    def informe(self) -> str:
        lineas = [f"\n===== INFORME JJOO {self.sede} =====", ""]
        medallero: Counter[str] = Counter()
        for evento in self.eventos.values():
            lineas.append(f"🏅 {evento.nombre}:")
            for medalla, ganador in zip(MEDALLAS, evento.podio):
                lineas.append(f"    {medalla}: {ganador}")
                medallero[ganador.pais] += 1
            lineas.append("")
        lineas.append("----- RANKING DE PAÍSES -----")
        for pos, (pais, total) in enumerate(medallero.most_common(), 1):
            lineas.append(f"  {pos}. {pais}: {total} medalla(s)")
        return "\n".join(lineas)


def demo() -> None:
    random.seed(2024)  # resultados reproducibles en la demo
    jjoo = JuegosOlimpicos("París 2024")

    datos = {
        "100m lisos": [("Bolt", "Jamaica"), ("Gatlin", "EE.UU."), ("Blake", "Jamaica"), ("Coleman", "EE.UU.")],
        "Natación 200m": [("Phelps", "EE.UU."), ("Popov", "Rusia"), ("Thorpe", "Australia")],
        "Maratón": [("Kipchoge", "Kenia"), ("Bekele", "Etiopía"), ("Farah", "Reino Unido"), ("Rupp", "EE.UU.")],
    }
    for evento, participantes in datos.items():
        jjoo.registrar_evento(evento)
        for nombre, pais in participantes:
            jjoo.registrar_participante(evento, nombre, pais)

    jjoo.simular_todo()
    print(jjoo.informe())


if __name__ == "__main__":
    demo()
