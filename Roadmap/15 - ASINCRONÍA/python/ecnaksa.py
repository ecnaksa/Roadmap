"""
#15 - ASINCRONÍA

=========================== TEORÍA ===========================
La ASINCRONÍA permite ejecutar tareas que "esperan" (I/O, temporizadores)
sin bloquear el resto del programa. Python usa `asyncio`:
  - `async def` define una corrutina.
  - `await` cede el control mientras se espera (p. ej. asyncio.sleep).
  - asyncio.gather(...) ejecuta varias corrutinas EN PARALELO (concurrencia).
  - asyncio.run(...) arranca el bucle de eventos.

Es concurrencia cooperativa en un solo hilo: mientras una tarea espera, otra
avanza. Ideal para operaciones limitadas por entrada/salida.

============================ PRÁCTICA ========================
"""

import asyncio
import time

_INICIO = time.monotonic()


def _t() -> str:
    """Tiempo relativo desde el arranque, para ver el paralelismo."""
    return f"[t+{time.monotonic() - _INICIO:4.1f}s]"


async def tarea(nombre: str, segundos: float) -> str:
    print(f"{_t()} ▶ '{nombre}' empieza (durará {segundos}s)")
    await asyncio.sleep(segundos)
    print(f"{_t()} ■ '{nombre}' finaliza")
    return nombre


async def main() -> None:
    print("=== Tarea asíncrona simple ===")
    await tarea("Sencilla", 1)

    # ----------------------- RETO EXTRA -----------------------
    print("\n=== Reto extra: C, B, A en paralelo; D al terminar ===")
    # C(3s), B(2s), A(1s) en paralelo -> total ~3s
    await asyncio.gather(
        tarea("C", 3),
        tarea("B", 2),
        tarea("A", 1),
    )
    # D solo empieza cuando las tres anteriores han acabado
    await tarea("D", 1)


if __name__ == "__main__":
    asyncio.run(main())
