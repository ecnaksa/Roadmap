"""
#05 - VALOR Y REFERENCIA

=========================== TEORÍA ===========================
En Python TODO son objetos y las variables son "etiquetas" que apuntan a
ellos. Lo que determina el comportamiento es si el objeto es MUTABLE o no:

  - Inmutables (int, float, str, tuple, bool): al "modificarlos" se crea un
    objeto nuevo. Se comportan como "por valor": reasignar dentro de una
    función NO afecta a la variable externa.
  - Mutables (list, dict, set): se comparte la referencia al mismo objeto.
    Si se modifica su contenido dentro de una función, el cambio SÍ se ve
    fuera ("por referencia").

Técnicamente Python usa "paso por asignación" (call by object reference):
se pasa la referencia del objeto, pero reasignar el parámetro solo cambia
la etiqueta local.

============================ PRÁCTICA ========================
"""


def modifica_inmutable(numero: int) -> None:
    numero += 100          # crea un nuevo int; no afecta al exterior
    print(f"  dentro (inmutable): {numero}")


def modifica_mutable(lista: list) -> None:
    lista.append(99)       # muta el MISMO objeto; sí afecta al exterior
    print(f"  dentro (mutable):   {lista}")


def demostrar() -> None:
    print("=== Inmutable (int) se comporta 'por valor' ===")
    n = 5
    modifica_inmutable(n)
    print(f"  fuera: {n} (sin cambios)")

    print("\n=== Mutable (list) se comporta 'por referencia' ===")
    valores = [1, 2, 3]
    modifica_mutable(valores)
    print(f"  fuera: {valores} (modificado)")

    print("\n=== id() confirma el objeto compartido ===")
    a = [1, 2]
    b = a               # misma referencia
    c = a.copy()        # copia -> objeto distinto
    print(f"  a is b -> {a is b} (id igual: {id(a) == id(b)})")
    print(f"  a is c -> {a is c} (copia independiente)")


# ----------------------- RETO EXTRA -----------------------


def intercambio_por_valor(x: int, y: int) -> tuple[int, int]:
    """Recibe dos inmutables, los intercambia y los retorna."""
    return y, x


def intercambio_por_referencia(lista_a: list, lista_b: list) -> tuple[list, list]:
    """Intercambia el CONTENIDO de dos listas mutables in-place y las retorna."""
    lista_a[:], lista_b[:] = lista_b[:], lista_a[:]
    return lista_a, lista_b


def reto_extra() -> None:
    print("\n=== Reto extra: intercambio por valor ===")
    orig_x, orig_y = 10, 20
    nuevo_x, nuevo_y = intercambio_por_valor(orig_x, orig_y)
    print(f"  originales: x={orig_x}, y={orig_y} (conservados)")
    print(f"  nuevas:     x={nuevo_x}, y={nuevo_y} (invertidas)")

    print("\n=== Reto extra: intercambio por referencia ===")
    orig_a, orig_b = [1, 2], [3, 4]
    # Guardamos copias para demostrar el estado 'original' antes de mutar
    copia_a, copia_b = orig_a.copy(), orig_b.copy()
    nueva_a, nueva_b = intercambio_por_referencia(orig_a.copy(), orig_b.copy())
    print(f"  originales: a={copia_a}, b={copia_b} (conservados)")
    print(f"  nuevas:     a={nueva_a}, b={nueva_b} (invertidas)")


if __name__ == "__main__":
    demostrar()
    reto_extra()
