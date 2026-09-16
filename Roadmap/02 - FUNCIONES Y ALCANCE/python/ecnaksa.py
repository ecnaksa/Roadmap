"""
#02 - FUNCIONES Y ALCANCE

=========================== TEORÍA ===========================
Una FUNCIÓN es un bloque de código reutilizable que se define con `def`.
Puede recibir parámetros y devolver valores con `return` (si no hay return
explícito, devuelve None).

ALCANCE (scope) determina dónde es visible una variable. Python sigue la
regla LEGB para resolver nombres:
  - Local     : dentro de la función actual.
  - Enclosing : funciones que envuelven a la actual (funciones anidadas).
  - Global    : nivel del módulo.
  - Built-in  : nombres integrados (print, len, ...).

Para modificar una variable global desde dentro de una función se usa la
palabra clave `global`; para modificar la de la función que la envuelve,
`nonlocal`.

============================ PRÁCTICA ========================
"""

# Variable GLOBAL
contador_global = 0


def sin_parametros_ni_retorno() -> None:
    print("  Función sin parámetros ni retorno.")


def con_un_parametro(nombre: str) -> None:
    print(f"  Hola, {nombre}.")


def con_varios_parametros_y_retorno(a: int, b: int) -> int:
    return a + b


def con_valores_por_defecto(base: int, exponente: int = 2) -> int:
    return base ** exponente


def con_args_variables(*numeros: int, **opciones) -> int:
    """*args recoge posicionales; **kwargs recoge nombrados."""
    total = sum(numeros)
    if opciones.get("doble"):
        total *= 2
    return total


def demostrar_alcance() -> None:
    global contador_global
    contador_global += 1  # modifica la global
    variable_local = "solo visible aquí"
    print(f"  Local: {variable_local}")
    print(f"  Global tras modificar: {contador_global}")

    # Función dentro de función (closure) + nonlocal
    def externa() -> str:
        mensaje = "original"

        def interna() -> None:
            nonlocal mensaje
            mensaje = "modificado por interna"

        interna()
        return mensaje

    print(f"  nonlocal: {externa()}")


def usar_funciones_integradas() -> None:
    valores = [5, 3, 9, 1]
    print(f"  len={len(valores)} max={max(valores)} min={min(valores)} sum={sum(valores)}")
    print(f"  sorted={sorted(valores)}")


def reto_extra(texto_multiplo_3: str, texto_multiplo_5: str) -> int:
    """
    Imprime del 1 al 100. Reglas:
      - múltiplo de 3            -> texto_multiplo_3
      - múltiplo de 5            -> texto_multiplo_5
      - múltiplo de 3 y de 5     -> ambos textos concatenados
      - resto                    -> el propio número
    Devuelve cuántas veces se imprimió el número (y no un texto).
    """
    veces_numero = 0
    for n in range(1, 101):
        if n % 15 == 0:
            print(texto_multiplo_3 + texto_multiplo_5)
        elif n % 3 == 0:
            print(texto_multiplo_3)
        elif n % 5 == 0:
            print(texto_multiplo_5)
        else:
            print(n)
            veces_numero += 1
    return veces_numero


if __name__ == "__main__":
    print("=== Tipos de funciones ===")
    sin_parametros_ni_retorno()
    con_un_parametro("ecnaksa")
    print(f"  suma(3,4) = {con_varios_parametros_y_retorno(3, 4)}")
    print(f"  potencia(3) = {con_valores_por_defecto(3)}  potencia(3,3) = {con_valores_por_defecto(3, 3)}")
    print(f"  args variables = {con_args_variables(1, 2, 3, doble=True)}")

    print("\n=== Alcance (LEGB) ===")
    demostrar_alcance()

    print("\n=== Funciones integradas ===")
    usar_funciones_integradas()

    print("\n=== Reto extra (FizzBuzz con retorno) ===")
    total = reto_extra("fizz", "buzz")
    print(f"El número se imprimió {total} veces.")
