"""
#03 - ESTRUCTURAS DE DATOS

=========================== TEORÍA ===========================
Python trae varias estructuras de datos integradas:
  - list  -> ordenada y MUTABLE. Permite duplicados.        [1, 2, 3]
  - tuple -> ordenada e INMUTABLE. Permite duplicados.       (1, 2, 3)
  - set   -> NO ordenada, MUTABLE, sin duplicados.           {1, 2, 3}
  - dict  -> pares clave:valor, MUTABLE, claves únicas.      {"a": 1}

Operaciones típicas: inserción, borrado, actualización, búsqueda y
ordenación. Cada estructura ofrece métodos propios (append, pop, add,
update, ...).

============================ PRÁCTICA ========================
"""


def demostrar_estructuras() -> None:
    print("=== LIST (mutable, ordenada) ===")
    lista = [3, 1, 2]
    lista.append(4)          # inserción al final
    lista.insert(0, 0)       # inserción por posición
    lista[1] = 10            # actualización
    lista.remove(2)          # borrado por valor
    lista.sort()             # ordenación in-place
    print(f"  {lista}")

    print("\n=== TUPLE (inmutable) ===")
    tupla = (1, 2, 3)
    print(f"  {tupla}  primer elemento: {tupla[0]}")
    print("  No admite modificación (es inmutable).")

    print("\n=== SET (sin duplicados) ===")
    conjunto = {1, 2, 2, 3}
    conjunto.add(4)          # inserción
    conjunto.discard(1)      # borrado seguro
    print(f"  {conjunto}")

    print("\n=== DICT (clave:valor) ===")
    agenda = {"Ana": 111, "Luis": 222}
    agenda["Marta"] = 333    # inserción
    agenda["Ana"] = 999      # actualización
    del agenda["Luis"]       # borrado
    ordenado = dict(sorted(agenda.items()))  # ordenación por clave
    print(f"  {ordenado}")


# ----------------------- RETO EXTRA -----------------------
# Agenda de contactos por terminal.

MAX_DIGITOS = 11


def _telefono_valido(telefono: str) -> bool:
    return telefono.isdigit() and len(telefono) <= MAX_DIGITOS


def agenda_de_contactos() -> None:
    """Menú interactivo (usa input). Lógica en funciones puras arriba."""
    contactos: dict[str, str] = {}
    menu = (
        "\n--- AGENDA DE CONTACTOS ---\n"
        "1. Buscar\n2. Insertar\n3. Actualizar\n4. Eliminar\n"
        "5. Listar\n6. Salir\nOpción: "
    )
    while True:
        opcion = input(menu).strip()
        if opcion == "1":
            nombre = input("Nombre a buscar: ").strip()
            print(contactos.get(nombre, "No encontrado."))
        elif opcion in ("2", "3"):
            nombre = input("Nombre: ").strip()
            telefono = input("Teléfono: ").strip()
            if not _telefono_valido(telefono):
                print(f"Teléfono no válido (solo dígitos, máx {MAX_DIGITOS}).")
                continue
            contactos[nombre] = telefono
            print("Guardado.")
        elif opcion == "4":
            nombre = input("Nombre a eliminar: ").strip()
            print("Eliminado." if contactos.pop(nombre, None) else "No existía.")
        elif opcion == "5":
            print(contactos or "Agenda vacía.")
        elif opcion == "6":
            print("¡Hasta pronto!")
            break
        else:
            print("Opción no válida.")


def _demo_no_interactiva() -> None:
    """Demostración de la lógica de la agenda sin pedir input."""
    print("\n=== Reto extra: agenda (demo no interactiva) ===")
    contactos: dict[str, str] = {}
    for nombre, tel in [("Ana", "600111222"), ("Luis", "abc"), ("Marta", "999")]:
        if _telefono_valido(tel):
            contactos[nombre] = tel
            print(f"  Insertado {nombre}: {tel}")
        else:
            print(f"  Rechazado {nombre}: '{tel}' no es un teléfono válido")
    contactos["Ana"] = "600999888"      # actualización
    contactos.pop("Marta", None)        # eliminación
    print(f"  Estado final: {contactos}")


if __name__ == "__main__":
    demostrar_estructuras()
    _demo_no_interactiva()
    # Para el modo interactivo real, descomenta:
    # agenda_de_contactos()
