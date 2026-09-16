"""
#00 - SINTAXIS, VARIABLES, TIPOS DE DATOS Y HOLA MUNDO
Web oficial del lenguaje: https://www.python.org

=========================== TEORÍA ===========================
Python es un lenguaje interpretado, de tipado dinámico y fuerte. Esto
significa que:
  - No declaramos el tipo de una variable: se infiere del valor asignado
    (tipado dinámico).
  - Aun así, no se mezclan tipos incompatibles sin conversión explícita
    (tipado fuerte): "2" + 2 lanza error.
  - Constantes: Python no tiene constantes "reales"; por convención se
    escriben en MAYÚSCULAS para indicar que no deben modificarse.

Tipos primitivos principales:
  - int    -> enteros de precisión arbitraria (10, -3, 1_000_000)
  - float  -> números en coma flotante (3.14, 2.0)
  - complex-> números complejos (2 + 3j)
  - bool   -> booleanos (True, False); subtipo de int
  - str    -> cadenas de texto (Unicode)
  - NoneType -> el valor None (ausencia de valor)

============================ PRÁCTICA ========================
Ejecuta:  python ecnaksa.py
"""

# --- Comentarios ---
# Esto es un comentario de una sola línea.

# No existe comentario multilínea nativo, pero se usa una cadena literal
# (docstring) para varias líneas, como el bloque del inicio de este archivo.
"""
Esto también actúa como comentario de varias líneas
al ser una cadena que no se asigna a ninguna variable.
"""


def main() -> None:
    # --- Variables (tipado dinámico) ---
    nombre = "ecnaksa"          # str
    edad = 30                    # int
    altura = 1.80                # float
    numero_complejo = 2 + 3j     # complex
    es_programador = True        # bool
    sin_valor = None             # NoneType

    # --- "Constante" (por convención, en mayúsculas) ---
    PI = 3.14159

    # --- Tipos de datos primitivos y su tipo ---
    print("=== Variables y sus tipos ===")
    for etiqueta, valor in {
        "nombre (str)": nombre,
        "edad (int)": edad,
        "altura (float)": altura,
        "complejo (complex)": numero_complejo,
        "es_programador (bool)": es_programador,
        "sin_valor (NoneType)": sin_valor,
        "PI (constante)": PI,
    }.items():
        print(f"  {etiqueta:22} = {valor!r:20} -> {type(valor).__name__}")

    # --- Impresión final requerida ---
    print()
    print("¡Hola, Python!")


if __name__ == "__main__":
    main()
