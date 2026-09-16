"""
#38 - MOUREDEV PRO (sorteo desde CSV)

Lee registros de un .csv (id, email, status) y selecciona al azar tres
ganadores distintos (suscripción, descuento y libro) solo entre los "activo".

=========================== TEORÍA ===========================
Reto de LECTURA DE CSV + aleatoriedad. Se usa el módulo estándar `csv`, se
salta la fila de cabecera, se filtran los registros activos y se eligen
ganadores sin repetición con random.sample.

NOTA: el .csv de datos NO debe subirse al repositorio; aquí lo generamos al
vuelo para la demostración y lo borramos al terminar.

============================ PRÁCTICA ========================
"""

from __future__ import annotations

import csv
import os
import random

PREMIOS = ["Suscripción", "Descuento", "Libro"]


def seleccionar_ganadores(ruta_csv: str) -> dict[str, dict] | None:
    with open(ruta_csv, newline="", encoding="utf-8") as f:
        lector = csv.reader(f)
        next(lector, None)  # saltar cabecera
        activos = [
            {"id": fila[0], "email": fila[1]}
            for fila in lector
            if len(fila) >= 3 and fila[2].strip().lower() == "activo"
        ]
    if len(activos) < len(PREMIOS):
        return None
    ganadores = random.sample(activos, len(PREMIOS))  # sin repetición
    return dict(zip(PREMIOS, ganadores))


def _crear_csv_demo(ruta: str) -> None:
    with open(ruta, "w", newline="", encoding="utf-8") as f:
        escritor = csv.writer(f)
        escritor.writerow(["id", "email", "status"])
        for i in range(1, 11):
            estado = "activo" if i % 3 != 0 else "inactivo"
            escritor.writerow([i, f"user{i}@test.com", estado])


def demo() -> None:
    random.seed(38)
    ruta = "suscriptores.csv"
    _crear_csv_demo(ruta)
    print("=== Sorteo mouredev pro ===")
    ganadores = seleccionar_ganadores(ruta)
    if ganadores is None:
        print("  No hay suficientes suscriptores activos para el sorteo.")
    else:
        for premio, datos in ganadores.items():
            print(f"  🎁 {premio:12} -> id {datos['id']:>2}  {datos['email']}")
    os.remove(ruta)  # no se sube el fichero de datos


if __name__ == "__main__":
    demo()
