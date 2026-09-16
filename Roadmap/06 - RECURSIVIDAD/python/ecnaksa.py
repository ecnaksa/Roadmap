"""
#06 - RECURSIVIDAD

=========================== TEORÍA ===========================
La RECURSIVIDAD es la técnica en la que una función se llama a sí misma para
resolver un problema dividiéndolo en subproblemas más pequeños.

Toda función recursiva necesita:
  1. CASO BASE: condición que detiene la recursión (evita bucle infinito).
  2. CASO RECURSIVO: la función se llama a sí misma acercándose al caso base.

Cada llamada se apila en la "pila de llamadas". Python limita la profundidad
(por defecto ~1000, ver sys.getrecursionlimit) para evitar desbordamientos.

============================ PRÁCTICA ========================
"""


def cuenta_atras(n: int) -> None:
    """Imprime del n al 0 de forma recursiva."""
    if n < 0:                 # caso base
        return
    print(n, end=" ")
    cuenta_atras(n - 1)       # caso recursivo


# ----------------------- RETO EXTRA -----------------------


def factorial(n: int) -> int:
    """n! = n * (n-1)!  con  0! = 1."""
    if n < 0:
        raise ValueError("El factorial no está definido para negativos")
    if n <= 1:                # caso base
        return 1
    return n * factorial(n - 1)


def fibonacci(posicion: int) -> int:
    """
    Devuelve el elemento en 'posicion' de Fibonacci (0-indexado):
    0, 1, 1, 2, 3, 5, 8, ...
    """
    if posicion < 0:
        raise ValueError("La posición no puede ser negativa")
    if posicion < 2:          # casos base: fib(0)=0, fib(1)=1
        return posicion
    return fibonacci(posicion - 1) + fibonacci(posicion - 2)


if __name__ == "__main__":
    print("=== Cuenta atrás recursiva (100 -> 0) ===")
    cuenta_atras(100)
    print("\n")

    print("=== Reto extra: factorial ===")
    for n in (0, 1, 5, 10):
        print(f"  {n}! = {factorial(n)}")

    print("\n=== Reto extra: Fibonacci ===")
    print("  " + ", ".join(str(fibonacci(i)) for i in range(15)))
    print(f"  fibonacci(10) = {fibonacci(10)}")
