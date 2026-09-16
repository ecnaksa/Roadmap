"""
#08 - CLASES

=========================== TEORÍA ===========================
Una CLASE es una plantilla para crear objetos. Define atributos (datos) y
métodos (comportamiento). Un OBJETO es una instancia concreta de la clase.

En Python:
  - __init__ es el inicializador (constructor): se ejecuta al crear el objeto.
  - `self` es la referencia a la instancia actual; siempre es el primer
    parámetro de los métodos de instancia.
  - __str__ define la representación legible del objeto (lo que muestra print).

============================ PRÁCTICA ========================
"""


class Persona:
    def __init__(self, nombre: str, edad: int) -> None:
        self.nombre = nombre      # atributo de instancia
        self.edad = edad

    def presentarse(self) -> None:
        print(f"  Me llamo {self.nombre} y tengo {self.edad} años.")

    def __str__(self) -> str:
        return f"Persona(nombre={self.nombre!r}, edad={self.edad})"


# ----------------------- RETO EXTRA -----------------------


class Pila:
    """Estructura LIFO como clase."""

    def __init__(self) -> None:
        self._items: list = []

    def apilar(self, item) -> None:
        self._items.append(item)

    def desapilar(self):
        return self._items.pop() if self._items else None

    def tamanio(self) -> int:
        return len(self._items)

    def imprimir(self) -> None:
        print(f"  Pila (tope a la derecha): {self._items}")


class Cola:
    """Estructura FIFO como clase."""

    def __init__(self) -> None:
        self._items: list = []

    def encolar(self, item) -> None:
        self._items.append(item)

    def desencolar(self):
        return self._items.pop(0) if self._items else None

    def tamanio(self) -> int:
        return len(self._items)

    def imprimir(self) -> None:
        print(f"  Cola (frente a la izquierda): {self._items}")


if __name__ == "__main__":
    print("=== Clase Persona ===")
    p = Persona("ecnaksa", 30)
    p.presentarse()
    p.edad = 31                       # modificamos un atributo
    p.presentarse()
    print(f"  __str__ -> {p}")

    print("\n=== Reto extra: Pila como clase ===")
    pila = Pila()
    for x in (1, 2, 3):
        pila.apilar(x)
    pila.imprimir()
    print(f"  desapilar -> {pila.desapilar()}  (tamaño={pila.tamanio()})")
    pila.imprimir()

    print("\n=== Reto extra: Cola como clase ===")
    cola = Cola()
    for x in ("a", "b", "c"):
        cola.encolar(x)
    cola.imprimir()
    print(f"  desencolar -> {cola.desencolar()}  (tamaño={cola.tamanio()})")
    cola.imprimir()
