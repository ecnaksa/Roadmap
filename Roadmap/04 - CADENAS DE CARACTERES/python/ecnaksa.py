"""
#04 - CADENAS DE CARACTERES

=========================== TEORÍA ===========================
Una cadena (str) es una secuencia INMUTABLE de caracteres Unicode. Al ser
inmutable, cualquier "modificación" crea en realidad una cadena nueva.
Se puede indexar (s[0]), rebanar (s[1:4]), recorrer, concatenar (+),
repetir (*) y consultar su longitud (len). Ofrece decenas de métodos:
upper, lower, replace, split, join, strip, find, startswith, etc.

============================ PRÁCTICA ========================
"""


def demostrar_operaciones() -> None:
    s = "Hola, Python"
    print(f"Cadena original:      {s!r}")
    print(f"Acceso s[0]:          {s[0]}")
    print(f"Último s[-1]:         {s[-1]}")
    print(f"Subcadena s[6:12]:    {s[6:12]}")
    print(f"Longitud len(s):      {len(s)}")
    print(f"Concatenación:        {s + '!'}")
    print(f"Repetición:           {'ab' * 3}")
    print(f"Mayúsculas:           {s.upper()}")
    print(f"Minúsculas:           {s.lower()}")
    print(f"Reemplazo:            {s.replace('Python', 'Mundo')}")
    print(f"División (split):     {s.split(', ')}")
    print(f"Unión (join):         {'-'.join(['a', 'b', 'c'])}")
    print(f"Interpolación:        {f'{2 + 2} es la suma'}")
    print(f"¿Empieza por 'Hola'?  {s.startswith('Hola')}")
    print(f"¿Contiene 'thon'?     {'thon' in s}")
    print("Recorrido carácter a carácter:", end=" ")
    for c in "abc":
        print(c, end=" ")
    print()


# ----------------------- RETO EXTRA -----------------------


def _normalizar(palabra: str) -> str:
    """Minúsculas y solo letras/dígitos, para comparaciones justas."""
    return "".join(c.lower() for c in palabra if c.isalnum())


def es_palindromo(palabra: str) -> bool:
    limpia = _normalizar(palabra)
    return limpia == limpia[::-1]


def son_anagramas(a: str, b: str) -> bool:
    return sorted(_normalizar(a)) == sorted(_normalizar(b))


def es_isograma(palabra: str) -> bool:
    """Isograma: no repite ninguna letra."""
    limpia = _normalizar(palabra)
    return len(limpia) == len(set(limpia))


def analizar(a: str, b: str) -> None:
    print(f"\n=== Análisis de '{a}' y '{b}' ===")
    print(f"  ¿'{a}' es palíndromo?  {es_palindromo(a)}")
    print(f"  ¿'{b}' es palíndromo?  {es_palindromo(b)}")
    print(f"  ¿Son anagramas?        {son_anagramas(a, b)}")
    print(f"  ¿'{a}' es isograma?    {es_isograma(a)}")
    print(f"  ¿'{b}' es isograma?    {es_isograma(b)}")


if __name__ == "__main__":
    demostrar_operaciones()
    analizar("Roma", "Amor")
    analizar("Anita lava la tina", "casa")
