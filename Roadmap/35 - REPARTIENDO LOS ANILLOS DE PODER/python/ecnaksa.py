"""
#35 - REPARTIENDO LOS ANILLOS DE PODER

Reparte un número total de anillos entre las razas de la Tierra Media según:
  - Elfos:  número IMPAR
  - Enanos: número PRIMO
  - Hombres: número PAR
  - Sauron: siempre 1

=========================== TEORÍA ===========================
Reto de BÚSQUEDA COMBINATORIA con restricciones. Reservamos 1 anillo para
Sauron y buscamos una terna (elfos, enanos, hombres) que sume el resto y
cumpla, cada una, su propiedad numérica. Necesitamos comprobar si un número
es primo.

============================ PRÁCTICA ========================
"""

from __future__ import annotations


def es_primo(n: int) -> bool:
    if n < 2:
        return False
    if n < 4:
        return True
    if n % 2 == 0:
        return False
    i = 3
    while i * i <= n:
        if n % i == 0:
            return False
        i += 2
    return True


def repartir(total: int) -> dict[str, int] | None:
    """Busca una combinación válida o None si no existe."""
    if total < 1:
        return None
    restante = total - 1  # Sauron siempre 1
    # elfos impar, enanos primo, hombres par ; elfos+enanos+hombres = restante
    for elfos in range(1, restante + 1, 2):            # impares
        for enanos in range(2, restante - elfos + 1):
            if not es_primo(enanos):
                continue
            hombres = restante - elfos - enanos
            if hombres >= 0 and hombres % 2 == 0:
                return {"Elfos": elfos, "Enanos": enanos, "Hombres": hombres, "Sauron": 1}
    return None


def mostrar_reparto(total: int) -> None:
    print(f"\n=== Repartir {total} anillos ===")
    reparto = repartir(total)
    if reparto is None:
        print("  ❌ No existe un reparto válido con esas reglas.")
        return
    for raza, cantidad in reparto.items():
        print(f"  {raza:8}: {cantidad}")
    print(f"  Total repartido: {sum(reparto.values())}")


if __name__ == "__main__":
    for total in (20, 15, 3, 2, 1):
        mostrar_reparto(total)
