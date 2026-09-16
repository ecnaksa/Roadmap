"""
#22 - FUNCIONES DE ORDEN SUPERIOR

=========================== TEORÍA ===========================
Una FUNCIÓN DE ORDEN SUPERIOR (Higher-Order Function) es aquella que cumple
al menos una de estas condiciones:
  - Recibe una o más funciones como argumento.
  - Devuelve una función como resultado.
Ejemplos integrados: map (transforma), filter (filtra), sorted con `key`,
functools.reduce (acumula). Fomentan un estilo declarativo y reutilizable.

============================ PRÁCTICA ========================
"""

from datetime import date
from functools import reduce


def ejemplos_basicos() -> None:
    numeros = [1, 2, 3, 4, 5, 6]
    print("=== HOF integradas ===")
    print(f"  map (x2):    {list(map(lambda x: x * 2, numeros))}")
    print(f"  filter par:  {list(filter(lambda x: x % 2 == 0, numeros))}")
    print(f"  reduce suma: {reduce(lambda a, b: a + b, numeros)}")
    print(f"  sorted key:  {sorted(numeros, key=lambda x: -x)}")

    def multiplicador(factor: int):        # devuelve una función
        return lambda x: x * factor

    triple = multiplicador(3)
    print(f"  función que devuelve función: triple(10) = {triple(10)}")


# ----------------------- RETO EXTRA -----------------------

ESTUDIANTES = [
    {"nombre": "Ana", "nacimiento": date(2001, 3, 12), "notas": [8.5, 9.0, 7.5]},
    {"nombre": "Luis", "nacimiento": date(1999, 11, 5), "notas": [9.2, 9.5, 9.8]},
    {"nombre": "Marta", "nacimiento": date(2003, 7, 20), "notas": [6.0, 7.0, 8.0]},
    {"nombre": "Iker", "nacimiento": date(2000, 1, 30), "notas": [9.0, 9.1, 9.3]},
]


def _validar_notas(estudiantes: list[dict]) -> None:
    for e in estudiantes:
        for nota in e["notas"]:
            if not 0 <= nota <= 10:
                raise ValueError(f"Nota fuera de rango en {e['nombre']}: {nota}")


def promedios(estudiantes: list[dict]) -> list[tuple[str, float]]:
    return list(map(
        lambda e: (e["nombre"], round(sum(e["notas"]) / len(e["notas"]), 2)),
        estudiantes,
    ))


def mejores(estudiantes: list[dict]) -> list[str]:
    return [n for n, prom in promedios(estudiantes) if prom >= 9]


def ordenados_por_juventud(estudiantes: list[dict]) -> list[str]:
    return [e["nombre"] for e in sorted(estudiantes, key=lambda e: e["nacimiento"], reverse=True)]


def mayor_calificacion(estudiantes: list[dict]) -> float:
    return reduce(lambda mejor, e: max(mejor, max(e["notas"])), estudiantes, 0.0)


if __name__ == "__main__":
    ejemplos_basicos()

    print("\n=== Reto extra: análisis de estudiantes ===")
    _validar_notas(ESTUDIANTES)
    print(f"  Promedios:          {promedios(ESTUDIANTES)}")
    print(f"  Mejores (>=9):      {mejores(ESTUDIANTES)}")
    print(f"  Del más joven:      {ordenados_por_juventud(ESTUDIANTES)}")
    print(f"  Mayor calificación: {mayor_calificacion(ESTUDIANTES)}")
