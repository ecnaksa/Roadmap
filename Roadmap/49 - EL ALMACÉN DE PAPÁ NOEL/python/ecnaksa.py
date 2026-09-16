"""
#49 - EL ALMACÉN DE PAPÁ NOEL

Juego tipo Mastermind: adivinar un código secreto de 4 caracteres (letras A-C
y números 1-3, sin repetidos) en un máximo de 10 intentos. Para cada carácter
se indica: Correcto, Presente o Incorrecto.

=========================== TEORÍA ===========================
Reto de LÓGICA de comparación posición a posición. Se genera un código
aleatorio sin repetidos y se evalúa cada intento comparando cada carácter con
su posición y con el conjunto del código.

============================ PRÁCTICA ========================
"""

from __future__ import annotations

import random

CARACTERES = ["A", "B", "C", "1", "2", "3"]
LONGITUD = 4
INTENTOS_MAX = 10


def generar_codigo() -> list[str]:
    return random.sample(CARACTERES, LONGITUD)  # sin repetidos


def validar(intento: str) -> str | None:
    """Devuelve un mensaje de error, o None si el intento es válido."""
    if len(intento) != LONGITUD:
        return f"El código debe tener {LONGITUD} caracteres"
    for c in intento:
        if c not in CARACTERES:
            return f"Carácter no soportado: '{c}' (usa {', '.join(CARACTERES)})"
    return None


def evaluar(secreto: list[str], intento: str) -> list[str]:
    resultado = []
    for i, c in enumerate(intento):
        if c == secreto[i]:
            resultado.append("Correcto")
        elif c in secreto:
            resultado.append("Presente")
        else:
            resultado.append("Incorrecto")
    return resultado


def _formatear(intento: str, pistas: list[str]) -> str:
    return "  ".join(f"{c}:{p}" for c, p in zip(intento, pistas))


def jugar() -> None:
    """Modo interactivo real (usa input)."""
    secreto = generar_codigo()
    print(f"🎅 Adivina el código de {LONGITUD} caracteres ({', '.join(CARACTERES)}).")
    for intento_num in range(1, INTENTOS_MAX + 1):
        intento = input(f"Intento {intento_num}/{INTENTOS_MAX}: ").strip().upper()
        error = validar(intento)
        if error:
            print(f"  [!] {error}")
            continue
        pistas = evaluar(secreto, intento)
        print("  " + _formatear(intento, pistas))
        if all(p == "Correcto" for p in pistas):
            print("🎉 ¡Código correcto! Papá Noel puede repartir los regalos.")
            return
    print(f"❌ Sin intentos. El código era: {''.join(secreto)}")


def demo() -> None:
    random.seed(49)
    secreto = generar_codigo()
    print("=== El almacén de Papá Noel (demo) ===")
    print(f"(código secreto para la demo: {''.join(secreto)})")
    intentos = ["AB12", "XY99", "".join(secreto)]  # incluye uno inválido y el acierto
    for i, intento in enumerate(intentos, 1):
        error = validar(intento)
        if error:
            print(f"  Intento {i} '{intento}': [!] {error}")
            continue
        pistas = evaluar(secreto, intento)
        print(f"  Intento {i} '{intento}': {_formatear(intento, pistas)}")
        if all(p == "Correcto" for p in pistas):
            print("  🎉 ¡Código descifrado!")
            break


if __name__ == "__main__":
    demo()
    # Para jugar de verdad, descomenta:
    # jugar()
