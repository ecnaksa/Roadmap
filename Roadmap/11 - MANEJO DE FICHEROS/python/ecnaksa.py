"""
#11 - MANEJO DE FICHEROS

=========================== TEORÍA ===========================
Python maneja ficheros con la función open(ruta, modo). Modos habituales:
  - "r" leer, "w" escribir (trunca), "a" añadir, "r+" leer/escribir.
Es una buena práctica usar `with open(...) as f:` porque cierra el fichero
automáticamente al salir del bloque, incluso si hay una excepción.
El módulo `os` permite operaciones del sistema como borrar (os.remove).

============================ PRÁCTICA ========================
"""

import os

USUARIO = "ecnaksa"


def ejercicio_basico() -> None:
    ruta = f"{USUARIO}.txt"
    print("=== Fichero básico ===")
    # Escribir varias líneas
    with open(ruta, "w", encoding="utf-8") as f:
        f.write("Nombre: ecnaksa\n")
        f.write("Edad: 30\n")
        f.write("Lenguaje favorito: Python\n")

    # Leer e imprimir
    with open(ruta, "r", encoding="utf-8") as f:
        print(f.read(), end="")

    # Borrar
    os.remove(ruta)
    print(f"Fichero '{ruta}' borrado: {not os.path.exists(ruta)}")


# ----------------------- RETO EXTRA -----------------------
# Gestión de ventas en un .txt con formato: nombre,cantidad,precio

RUTA_VENTAS = "ventas.txt"


def _leer_productos() -> list[tuple[str, int, float]]:
    if not os.path.exists(RUTA_VENTAS):
        return []
    productos = []
    with open(RUTA_VENTAS, "r", encoding="utf-8") as f:
        for linea in f:
            linea = linea.strip()
            if not linea:
                continue
            nombre, cantidad, precio = linea.split(",")
            productos.append((nombre, int(cantidad), float(precio)))
    return productos


def _guardar_productos(productos: list[tuple[str, int, float]]) -> None:
    with open(RUTA_VENTAS, "w", encoding="utf-8") as f:
        for nombre, cantidad, precio in productos:
            f.write(f"{nombre},{cantidad},{precio}\n")


def anadir_producto(nombre: str, cantidad: int, precio: float) -> None:
    productos = _leer_productos()
    productos.append((nombre, cantidad, precio))
    _guardar_productos(productos)


def total_por_producto(nombre: str) -> float:
    return sum(c * p for n, c, p in _leer_productos() if n == nombre)


def total_ventas() -> float:
    return sum(c * p for _, c, p in _leer_productos())


def reto_extra() -> None:
    print("\n=== Reto extra: gestión de ventas (demo) ===")
    if os.path.exists(RUTA_VENTAS):
        os.remove(RUTA_VENTAS)
    anadir_producto("Teclado", 3, 25.0)
    anadir_producto("Ratón", 5, 12.5)
    anadir_producto("Teclado", 2, 25.0)
    print(f"  Productos: {_leer_productos()}")
    print(f"  Total 'Teclado': {total_por_producto('Teclado')} €")
    print(f"  Total ventas:    {total_ventas()} €")
    os.remove(RUTA_VENTAS)   # la opción "salir" borra el fichero
    print(f"  Fichero borrado: {not os.path.exists(RUTA_VENTAS)}")


if __name__ == "__main__":
    ejercicio_basico()
    reto_extra()
