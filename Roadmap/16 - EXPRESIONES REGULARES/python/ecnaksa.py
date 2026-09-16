"""
#16 - EXPRESIONES REGULARES

=========================== TEORÍA ===========================
Una EXPRESIÓN REGULAR (regex) es un patrón que describe conjuntos de cadenas.
Sirven para buscar, validar y extraer texto. En Python se usa el módulo `re`:
  - re.findall(patron, texto) -> lista de coincidencias.
  - re.fullmatch(patron, texto) -> valida que TODA la cadena encaja.
Metacaracteres comunes: \d dígito, \w alfanumérico, + una o más, * cero o
más, ? opcional, ^ inicio, $ fin, [] conjunto, () grupo.

============================ PRÁCTICA ========================
"""

import re


def extraer_numeros(texto: str) -> list[str]:
    """Encuentra y extrae todos los números (enteros o decimales)."""
    return re.findall(r"\d+(?:\.\d+)?", texto)


# ----------------------- RETO EXTRA -----------------------

EMAIL = re.compile(r"^[\w.+-]+@[\w-]+\.[\w.-]+$")
TELEFONO = re.compile(r"^(?:\+\d{1,3}\s?)?(?:\d{2,3}[\s-]?){2,4}\d{2,3}$")
URL = re.compile(r"^https?://(?:[\w-]+\.)+[\w-]+(?:/[\w./?%&=-]*)?$")


def validar_email(valor: str) -> bool:
    return bool(EMAIL.fullmatch(valor))


def validar_telefono(valor: str) -> bool:
    return bool(TELEFONO.fullmatch(valor))


def validar_url(valor: str) -> bool:
    return bool(URL.fullmatch(valor))


if __name__ == "__main__":
    texto = "El pedido 12 costó 34.50 euros y llegó en 7 días, código 007."
    print("=== Extraer números ===")
    print(f"  {texto}")
    print(f"  -> {extraer_numeros(texto)}")

    print("\n=== Reto extra: validaciones ===")
    print("  Emails:")
    for e in ("hola@dominio.com", "ecnaksa.dev@correo.es", "malo@@x", "sin-arroba.com"):
        print(f"    {e:28} -> {validar_email(e)}")

    print("  Teléfonos:")
    for t in ("+34 600 123 456", "600123456", "91 123 45 67", "abc123"):
        print(f"    {t:28} -> {validar_telefono(t)}")

    print("  URLs:")
    for u in ("https://mouredev.com", "http://a.b/c?d=1", "ftp://x.com", "sin-protocolo.com"):
        print(f"    {u:28} -> {validar_url(u)}")
