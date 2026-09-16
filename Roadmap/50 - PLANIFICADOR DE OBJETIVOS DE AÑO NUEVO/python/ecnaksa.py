"""
#50 - PLANIFICADOR DE OBJETIVOS DE AÑO NUEVO

Gestor de propósitos: añade objetivos (máx 10), calcula un plan detallado
mes a mes y lo exporta a .txt.

=========================== TEORÍA ===========================
Reto de LÓGICA + generación de informes + escritura de ficheros. Cada objetivo
reparte su cantidad total entre los meses de su plazo. Se genera una vista por
meses y se puede exportar.

============================ PRÁCTICA ========================
"""

from __future__ import annotations

import os
from dataclasses import dataclass

MESES = [
    "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
    "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre",
]
MAX_OBJETIVOS = 10
MAX_PLAZO = 12


@dataclass
class Objetivo:
    meta: str
    cantidad: int
    unidades: str
    plazo: int  # en meses (1..12)

    def por_mes(self) -> float:
        return self.cantidad / self.plazo


class Planificador:
    def __init__(self) -> None:
        self.objetivos: list[Objetivo] = []

    def anadir(self, meta: str, cantidad: int, unidades: str, plazo: int) -> str:
        if len(self.objetivos) >= MAX_OBJETIVOS:
            return f"[!] Máximo {MAX_OBJETIVOS} objetivos"
        if not 1 <= plazo <= MAX_PLAZO:
            return f"[!] El plazo debe estar entre 1 y {MAX_PLAZO} meses"
        if cantidad <= 0:
            return "[!] La cantidad debe ser positiva"
        self.objetivos.append(Objetivo(meta, cantidad, unidades, plazo))
        return f"🎯 Objetivo añadido: {meta}"

    def _fmt(self, valor: float) -> str:
        return str(int(valor)) if valor == int(valor) else f"{valor:.2f}"

    def calcular_plan(self) -> str:
        if not self.objetivos:
            return "(No hay objetivos)"
        meses_totales = max(o.plazo for o in self.objetivos)
        lineas = ["=== PLAN DE OBJETIVOS DE AÑO NUEVO ==="]
        for m in range(meses_totales):
            lineas.append(f"\n{MESES[m]}:")
            n = 1
            for o in self.objetivos:
                if m < o.plazo:
                    por_mes = self._fmt(o.por_mes())
                    lineas.append(
                        f"[ ] {n}. {o.meta} ({por_mes} {o.unidades}/mes). Total: {o.cantidad}."
                    )
                    n += 1
        return "\n".join(lineas)

    def exportar(self, ruta: str) -> str:
        with open(ruta, "w", encoding="utf-8") as f:
            f.write(self.calcular_plan())
        return f"💾 Plan exportado a '{ruta}'"


def demo() -> None:
    planificador = Planificador()
    print("=== Planificador de objetivos (demo) ===")
    print(" ", planificador.anadir("Leer libros", 12, "libros", 12))
    print(" ", planificador.anadir("Estudiar Git", 1, "curso", 1))
    print(" ", planificador.anadir("Correr", 300, "km", 6))
    print(" ", planificador.anadir("Fallo", 5, "x", 13))  # error: plazo inválido

    print("\n" + planificador.calcular_plan())

    ruta = "propositos.txt"
    print("\n" + planificador.exportar(ruta))
    os.remove(ruta)  # no se sube el fichero
    print(f"(Fichero '{ruta}' borrado tras la demo)")


if __name__ == "__main__":
    demo()
