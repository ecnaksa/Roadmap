"""
#36 - EL SOMBRERO SELECCIONADOR

El sombrero hace 10 preguntas para asignar al alumno una de 4 "casas" de
programación: Frontend, Backend, Mobile y Data. Cada respuesta suma puntos a
una casa; los empates se resuelven al azar.

=========================== TEORÍA ===========================
Reto de LÓGICA + estructuras de datos + aleatoriedad. Se modela un sistema de
puntuación (dict casa -> puntos) y se recorre un cuestionario. Al final se
elige el máximo, resolviendo empates de forma aleatoria.

============================ PRÁCTICA ========================
"""

from __future__ import annotations

import random

CASAS = ["Frontend", "Backend", "Mobile", "Data"]

# Cada pregunta tiene 4 respuestas; cada respuesta suma a la casa de su índice.
PREGUNTAS = [
    "1. ¿Qué te atrae más de un proyecto?",
    "2. ¿Con qué disfrutas programando?",
    "3. ¿Qué herramienta prefieres?",
    "4. ¿Qué problema te motiva más?",
    "5. ¿Dónde te ves trabajando?",
    "6. ¿Qué te resulta más satisfactorio?",
    "7. ¿Qué palabra te define mejor?",
    "8. ¿Qué te gusta optimizar?",
    "9. ¿Qué prefieres aprender ahora?",
    "10. ¿Cuál sería tu superpoder?",
]

RESPUESTAS = [
    ["La interfaz bonita", "La lógica del servidor", "La app en el móvil", "Los datos ocultos"],
    ["Animaciones y CSS", "APIs y bases de datos", "Apps nativas", "Modelos y estadística"],
    ["React/Vue", "Node/Django", "Swift/Kotlin", "Pandas/Spark"],
    ["Que se vea perfecto", "Que escale a millones", "Que vaya fluido en el móvil", "Predecir el futuro"],
    ["En diseño y UX", "En infraestructura", "En una startup mobile", "En un laboratorio de IA"],
    ["Un pixel perfect", "Un endpoint rápido", "5 estrellas en la store", "Un buen gráfico"],
    ["Creativo", "Metódico", "Práctico", "Analítico"],
    ["La experiencia de usuario", "El rendimiento del backend", "La batería del dispositivo", "Un algoritmo"],
    ["TypeScript", "Go/Rust", "Flutter", "TensorFlow"],
    ["Leer la mente del usuario", "Estar en todas partes a la vez", "Caber en cualquier bolsillo", "Ver patrones invisibles"],
]


def seleccionar(respuestas: list[int]) -> tuple[str, dict[str, int], bool]:
    """Calcula la casa. Devuelve (casa, puntuaciones, hubo_empate)."""
    puntos = {casa: 0 for casa in CASAS}
    for eleccion in respuestas:
        puntos[CASAS[eleccion]] += 1
    maximo = max(puntos.values())
    empatadas = [casa for casa, p in puntos.items() if p == maximo]
    return random.choice(empatadas), puntos, len(empatadas) > 1


def jugar() -> None:
    """Modo interactivo (usa input)."""
    nombre = input("¿Cómo te llamas? ").strip() or "alumno/a"
    respuestas = []
    for pregunta, opciones in zip(PREGUNTAS, RESPUESTAS):
        print("\n" + pregunta)
        for i, op in enumerate(opciones):
            print(f"  {i + 1}. {op}")
        while True:
            try:
                eleccion = int(input("Respuesta (1-4): ")) - 1
                if 0 <= eleccion <= 3:
                    respuestas.append(eleccion)
                    break
            except ValueError:
                pass
            print("  Introduce un número del 1 al 4.")
    _anunciar(nombre, *seleccionar(respuestas))


def _anunciar(nombre: str, casa: str, puntos: dict[str, int], empate: bool) -> None:
    print(f"\n🎩 El sombrero medita... {'¡Difícil decisión!' if empate else ''}")
    print(f"   {nombre}, tu casa es: ✨ {casa} ✨")
    print(f"   Puntuaciones: {puntos}")


def demo() -> None:
    random.seed(1)
    respuestas = [random.randint(0, 3) for _ in PREGUNTAS]
    print("=== El Sombrero Seleccionador (demo con respuestas aleatorias) ===")
    print(f"Respuestas simuladas: {respuestas}")
    _anunciar("ecnaksa", *seleccionar(respuestas))


if __name__ == "__main__":
    demo()
    # Para hacer el test de verdad, descomenta:
    # jugar()
