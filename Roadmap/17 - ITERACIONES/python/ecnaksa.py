"""
#17 - ITERACIONES

=========================== TEORÍA ===========================
ITERAR es recorrer los elementos de una colección o repetir una acción.
Python ofrece muchos mecanismos: el bucle for, while, comprensiones de lista,
funciones como map/filter, generadores, enumerate, zip, iteradores, etc.
Un ITERABLE es cualquier objeto que se puede recorrer; un ITERADOR produce
sus elementos uno a uno con next().

============================ PRÁCTICA ========================
"""


def tres_mecanismos() -> None:
    print("=== 3 mecanismos para imprimir del 1 al 10 ===")

    print("  1) for + range:", end=" ")
    for i in range(1, 11):
        print(i, end=" ")
    print()

    print("  2) while:      ", end=" ")
    i = 1
    while i <= 10:
        print(i, end=" ")
        i += 1
    print()

    print("  3) comprensión:", end=" ")
    print(*[i for i in range(1, 11)])


# ----------------------- RETO EXTRA -----------------------


def muchos_mecanismos() -> None:
    print("\n=== Reto extra: 10 mecanismos de iteración ===")
    numeros = list(range(1, 11))

    print("  1) for-range:      ", *range(1, 11))
    print("  2) while:          ", end=" ")
    i = 1
    while i <= 10:
        print(i, end=" ")
        i += 1
    print()
    print("  3) comprensión:    ", *[n for n in numeros])
    print("  4) enumerate:      ", *[f"{idx}:{val}" for idx, val in enumerate(numeros, 1)][:5], "...")
    print("  5) map:            ", *map(lambda n: n, numeros))
    print("  6) filter:         ", *filter(lambda n: n <= 10, numeros))
    print("  7) iterador+next:  ", end=" ")
    it = iter(numeros)
    try:
        while True:
            print(next(it), end=" ")
    except StopIteration:
        print()
    print("  8) zip:            ", *[a for a, _ in zip(numeros, numeros)])
    print("  9) reversed:       ", *reversed(list(reversed(numeros))))

    def generador():
        for n in range(1, 11):
            yield n
    print("  10) generador:     ", *generador())


if __name__ == "__main__":
    tres_mecanismos()
    muchos_mecanismos()
