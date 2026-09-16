"""
#10 - EXCEPCIONES

=========================== TEORÍA ===========================
Una EXCEPCIÓN es un evento que interrumpe el flujo normal del programa cuando
ocurre un error. En Python se gestionan con:
  - try     : bloque donde puede ocurrir el error.
  - except  : captura y maneja un tipo de error concreto.
  - else    : se ejecuta si NO hubo excepción.
  - finally : se ejecuta SIEMPRE (haya error o no); ideal para limpieza.

Podemos lanzar excepciones manualmente con `raise` y crear excepciones
personalizadas heredando de Exception.

============================ PRÁCTICA ========================
"""


def demostrar_captura() -> None:
    print("=== Capturar errores comunes ===")
    try:
        _ = 10 / 0
    except ZeroDivisionError as e:
        print(f"  ZeroDivisionError: {e}")

    try:
        lista = [1, 2, 3]
        _ = lista[10]
    except IndexError as e:
        print(f"  IndexError: {e}")

    print("  El programa continúa sin detenerse.")


# ----------------------- RETO EXTRA -----------------------


class EdadInvalidaError(Exception):
    """Excepción personalizada: la edad no es válida."""


def procesar_edad(valor) -> int:
    """
    Puede lanzar 3 excepciones:
      - TypeError            (valor de tipo incorrecto)
      - ValueError           (no convertible a entero)
      - EdadInvalidaError    (personalizada, lanzada manualmente)
    """
    if isinstance(valor, (list, dict, set, tuple)):
        raise TypeError(f"Tipo no admitido: {type(valor).__name__}")
    edad = int(valor)                       # puede lanzar ValueError
    if edad < 0 or edad > 150:              # regla de negocio
        raise EdadInvalidaError(f"Edad fuera de rango: {edad}")
    return edad


def evaluar(valor) -> None:
    try:
        edad = procesar_edad(valor)
    except TypeError as e:
        print(f"  [TypeError] {e}")
    except ValueError as e:
        print(f"  [ValueError] {e}")
    except EdadInvalidaError as e:
        print(f"  [EdadInvalidaError] {e}")
    else:
        print(f"  OK: edad procesada = {edad} (sin errores)")
    finally:
        print("  -> ejecución finalizada")


if __name__ == "__main__":
    demostrar_captura()

    print("\n=== Reto extra: función con 3 tipos de excepción ===")
    for entrada in (25, "abc", [1, 2], 200, "40"):
        print(f"Entrada: {entrada!r}")
        evaluar(entrada)
