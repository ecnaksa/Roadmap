"""
#44 - CUENTA ATRÁS MOUREDEV PRO

Cuenta atrás hasta una fecha/hora objetivo: convierte la fecha local a UTC,
muestra días/horas/minutos/segundos restantes y se actualiza cada segundo en
un hilo independiente.

=========================== TEORÍA ===========================
Reto de FECHAS + CONCURRENCIA. Se usa `datetime` con zona horaria (timezone)
para convertir de hora local a UTC, y el módulo `threading` para ejecutar la
cuenta atrás sin bloquear el hilo principal. os.system limpia la terminal.

============================ PRÁCTICA ========================
"""

from __future__ import annotations

import os
import threading
import time
from datetime import datetime, timezone


def a_utc(local: datetime) -> datetime:
    """Convierte una fecha local (naive) a UTC."""
    return local.astimezone().astimezone(timezone.utc)


def _formatear(restante: float) -> str:
    restante = max(0, int(restante))
    dias, resto = divmod(restante, 86400)
    horas, resto = divmod(resto, 3600)
    minutos, segundos = divmod(resto, 60)
    return f"{dias}d {horas:02d}h {minutos:02d}m {segundos:02d}s"


def cuenta_atras(objetivo_utc: datetime, limpiar: bool = True) -> None:
    while True:
        restante = (objetivo_utc - datetime.now(timezone.utc)).total_seconds()
        if limpiar:
            os.system("cls" if os.name == "nt" else "clear")
        if restante <= 0:
            print("🚀 ¡Es la hora! mouredev pro ya está disponible: https://mouredev.pro")
            break
        print(f"⏳ Cuenta atrás: {_formatear(restante)}")
        time.sleep(1)


def iniciar_en_hilo(objetivo_local: datetime, limpiar: bool = True) -> threading.Thread:
    objetivo_utc = a_utc(objetivo_local)
    hilo = threading.Thread(target=cuenta_atras, args=(objetivo_utc, limpiar), daemon=True)
    hilo.start()
    return hilo


def demo() -> None:
    from datetime import timedelta

    print("=== Cuenta atrás (demo de 3 segundos, sin limpiar terminal) ===")
    objetivo = datetime.now() + timedelta(seconds=3)
    hilo = iniciar_en_hilo(objetivo, limpiar=False)
    hilo.join(timeout=6)  # esperamos a que el hilo termine


if __name__ == "__main__":
    demo()
    # Uso real (pedir fecha por terminal y limpiar pantalla):
    # objetivo = datetime(2024, 11, 12, 18, 0, 0)   # día, mes, año, hora, min, seg
    # iniciar_en_hilo(objetivo).join()
