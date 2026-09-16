"""
#01 - OPERADORES Y ESTRUCTURAS DE CONTROL

=========================== TEORÍA ===========================
Los OPERADORES combinan valores para producir un resultado. En Python:
  - Aritméticos:  + - * / // % **   (// división entera, ** potencia)
  - Comparación:  == != > < >= <=    (devuelven bool)
  - Asignación:   = += -= *= /= ...  (asignan y operan a la vez)
  - Lógicos:      and or not         (evaluación perezosa / cortocircuito)
  - Identidad:    is / is not        (¿mismo objeto en memoria?)
  - Pertenencia:  in / not in        (¿está contenido en una colección?)
  - Bits:         & | ^ ~ << >>      (operan sobre la representación binaria)

Las ESTRUCTURAS DE CONTROL deciden qué código se ejecuta:
  - Condicionales: if / elif / else
  - Iterativas:    for (recorre iterables) y while (repite mientras se cumpla)
  - Excepciones:   try / except / else / finally
  - Control de bucle: break (rompe), continue (salta a la siguiente vuelta)

============================ PRÁCTICA ========================
"""


def demostrar_operadores() -> None:
    print("=== Aritméticos ===")
    print(f"7 + 2 = {7 + 2}   7 - 2 = {7 - 2}   7 * 2 = {7 * 2}")
    print(f"7 / 2 = {7 / 2}   7 // 2 = {7 // 2}   7 % 2 = {7 % 2}   7 ** 2 = {7 ** 2}")

    print("\n=== Comparación ===")
    print(f"7 == 2 -> {7 == 2}   7 != 2 -> {7 != 2}   7 > 2 -> {7 > 2}")

    print("\n=== Asignación ===")
    x = 10
    x += 5
    print(f"x += 5 -> {x}")
    x **= 2
    print(f"x **= 2 -> {x}")

    print("\n=== Lógicos ===")
    print(f"True and False -> {True and False}")
    print(f"True or False  -> {True or False}")
    print(f"not True       -> {not True}")

    print("\n=== Identidad y pertenencia ===")
    a = [1, 2, 3]
    b = a
    c = list(a)
    print(f"a is b -> {a is b} (mismo objeto)")
    print(f"a is c -> {a is c} (contenido igual, distinto objeto)")
    print(f"2 in a -> {2 in a}    9 not in a -> {9 not in a}")

    print("\n=== Bits ===")
    print(f"5 & 3 = {5 & 3}   5 | 3 = {5 | 3}   5 ^ 3 = {5 ^ 3}")
    print(f"~5 = {~5}   5 << 1 = {5 << 1}   5 >> 1 = {5 >> 1}")


def demostrar_estructuras_control() -> None:
    print("\n=== Condicional ===")
    nota = 7
    if nota >= 9:
        print("Sobresaliente")
    elif nota >= 5:
        print("Aprobado")
    else:
        print("Suspenso")

    print("\n=== Iterativa for ===")
    for i in range(3):
        print(f"  vuelta for {i}")

    print("\n=== Iterativa while ===")
    n = 3
    while n > 0:
        print(f"  cuenta atrás {n}")
        n -= 1

    print("\n=== Excepciones ===")
    try:
        _ = 10 / 0
    except ZeroDivisionError as error:
        print(f"  Capturado: {error}")
    finally:
        print("  Bloque finally siempre se ejecuta")


def reto_extra() -> None:
    """
    Imprime los números entre 10 y 55 (incluidos), pares, que NO sean el 16
    ni múltiplos de 3.
    """
    print("\n=== Reto extra: 10..55 pares, sin 16 ni múltiplos de 3 ===")
    resultado = [
        n
        for n in range(10, 56)
        if n % 2 == 0 and n != 16 and n % 3 != 0
    ]
    print(resultado)


if __name__ == "__main__":
    demostrar_operadores()
    demostrar_estructuras_control()
    reto_extra()
