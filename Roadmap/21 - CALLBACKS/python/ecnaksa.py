"""
#21 - CALLBACKS

=========================== TEORÍA ===========================
Un CALLBACK es una función que se pasa como ARGUMENTO a otra función, para que
esta la invoque en un momento determinado. En Python las funciones son
"ciudadanos de primera clase": se pueden guardar en variables, pasar como
argumento y devolver. Los callbacks permiten desacoplar "qué se hace" de
"cuándo se hace" (muy usado en eventos, procesos por fases, asincronía...).

============================ PRÁCTICA ========================
"""

import random
import time
from typing import Callable


def ejemplo_simple(datos: list[int], al_procesar: Callable[[int], None]) -> None:
    """Recorre los datos e invoca el callback con cada elemento."""
    for elemento in datos:
        al_procesar(elemento)


# ----------------------- RETO EXTRA -----------------------


def procesar_pedido(
    plato: str,
    on_confirmado: Callable[[str], None],
    on_listo: Callable[[str], None],
    on_entregado: Callable[[str], None],
    escala: float = 1.0,
) -> None:
    """
    Procesa un pedido por fases invocando un callback en cada una.
    'escala' permite acelerar la demo (1.0 = segundos reales).
    """
    on_confirmado(plato)
    time.sleep(random.randint(1, 10) * escala)
    on_listo(plato)
    time.sleep(random.randint(1, 10) * escala)
    on_entregado(plato)


if __name__ == "__main__":
    print("=== Callback simple ===")
    ejemplo_simple([1, 2, 3], lambda n: print(f"  procesando {n} -> {n * n}"))

    print("\n=== Reto extra: simulador de pedidos de restaurante ===")
    procesar_pedido(
        "Ramen",
        on_confirmado=lambda p: print(f"  ✅ Pedido confirmado: {p}"),
        on_listo=lambda p: print(f"  🍜 '{p}' está listo"),
        on_entregado=lambda p: print(f"  🛵 '{p}' entregado. ¡Buen provecho!"),
        escala=0.05,  # demo rápida; usa 1.0 para tiempos reales
    )
