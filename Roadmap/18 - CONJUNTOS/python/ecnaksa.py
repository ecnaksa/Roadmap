"""
#18 - CONJUNTOS

=========================== TEORÍA ===========================
El enunciado principal pide operaciones POSICIONALES (añadir al principio, en
una posición concreta, actualizar por índice...). Esas operaciones requieren
una estructura ORDENADA e indexable: en Python, la LIST.

El reto extra sí usa el tipo SET matemático de Python, que no admite
duplicados y ofrece operaciones de conjuntos:
  - Unión (|), Intersección (&), Diferencia (-), Diferencia simétrica (^).

============================ PRÁCTICA ========================
"""


def operaciones_posicionales() -> None:
    print("=== Operaciones sobre una colección ordenada (list) ===")
    datos = [1, 2, 3]
    print(f"  inicial:                 {datos}")

    datos.append(4)                        # añadir al final
    print(f"  append(4):               {datos}")

    datos.insert(0, 0)                     # añadir al principio
    print(f"  insert(0, 0):            {datos}")

    datos.extend([5, 6])                   # varios en bloque al final
    print(f"  extend([5, 6]):          {datos}")

    datos[2:2] = [10, 11]                  # varios en bloque en posición 2
    print(f"  datos[2:2]=[10,11]:      {datos}")

    del datos[2]                           # eliminar en posición concreta
    print(f"  del datos[2]:            {datos}")

    datos[0] = 99                          # actualizar valor en posición
    print(f"  datos[0]=99:             {datos}")

    print(f"  ¿99 en datos?            {99 in datos}")  # pertenencia

    datos.clear()                          # vaciar
    print(f"  clear():                 {datos}")


# ----------------------- RETO EXTRA -----------------------


def operaciones_de_conjuntos() -> None:
    print("\n=== Reto extra: operaciones con SET ===")
    a = {1, 2, 3, 4}
    b = {3, 4, 5, 6}
    print(f"  A = {a}")
    print(f"  B = {b}")
    print(f"  Unión (A | B):               {a | b}")
    print(f"  Intersección (A & B):        {a & b}")
    print(f"  Diferencia (A - B):          {a - b}")
    print(f"  Diferencia simétrica (A ^ B): {a ^ b}")


if __name__ == "__main__":
    operaciones_posicionales()
    operaciones_de_conjuntos()
