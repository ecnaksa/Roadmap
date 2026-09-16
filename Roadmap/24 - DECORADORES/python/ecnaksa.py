"""
#24 - DECORADORES

=========================== TEORÍA ===========================
Un DECORADOR es una función que recibe otra función y devuelve una versión
"envuelta" con comportamiento añadido, SIN modificar el código original.
Se aplican con la sintaxis @decorador encima de la función.

Sirven para añadir responsabilidades transversales: logging, medición de
tiempos, control de acceso, caché, conteo de llamadas... Se usa
functools.wraps para conservar el nombre y docstring de la función original.

============================ PRÁCTICA ========================
"""

import functools
import time


def cronometro(func):
    """Decorador genérico que mide el tiempo de ejecución."""

    @functools.wraps(func)
    def envoltura(*args, **kwargs):
        inicio = time.perf_counter()
        resultado = func(*args, **kwargs)
        print(f"  ⏱ '{func.__name__}' tardó {time.perf_counter() - inicio:.6f}s")
        return resultado

    return envoltura


@cronometro
def suma_lenta(n: int) -> int:
    return sum(range(n))


# ----------------------- RETO EXTRA -----------------------


def contador_llamadas(func):
    """Cuenta cuántas veces se ha llamado a la función decorada."""

    @functools.wraps(func)
    def envoltura(*args, **kwargs):
        envoltura.llamadas += 1
        print(f"  '{func.__name__}' llamada #{envoltura.llamadas}")
        return func(*args, **kwargs)

    envoltura.llamadas = 0
    return envoltura


@contador_llamadas
def saludar(nombre: str) -> str:
    return f"Hola, {nombre}"


if __name__ == "__main__":
    print("=== Decorador cronómetro ===")
    print(f"  resultado = {suma_lenta(1_000_000)}")

    print("\n=== Reto extra: contador de llamadas ===")
    saludar("Ana")
    saludar("Luis")
    saludar("Marta")
    print(f"  Total de llamadas a 'saludar': {saludar.llamadas}")
