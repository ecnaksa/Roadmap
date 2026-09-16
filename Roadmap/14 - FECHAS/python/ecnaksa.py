"""
#14 - FECHAS

=========================== TEORÍA ===========================
El módulo `datetime` maneja fechas y horas:
  - datetime.now()            -> fecha y hora actual.
  - datetime(año, mes, día...) -> una fecha concreta.
  - La resta de dos datetime devuelve un timedelta (diferencia).
  - strftime(formato) formatea una fecha a texto según códigos: %d día,
    %m mes, %Y año, %H hora, %M minuto, %S segundo, %A día de la semana,
    %B nombre del mes, %j día del año...

============================ PRÁCTICA ========================
"""

from datetime import datetime


def calcular_edad(nacimiento: datetime, ahora: datetime) -> int:
    """Años transcurridos entre dos fechas (teniendo en cuenta el día/mes)."""
    anios = ahora.year - nacimiento.year
    if (ahora.month, ahora.day) < (nacimiento.month, nacimiento.day):
        anios -= 1
    return anios


def demostrar() -> None:
    ahora = datetime.now()
    nacimiento = datetime(1994, 5, 12, 8, 30, 0)

    print("=== Fechas ===")
    print(f"  Ahora:      {ahora}")
    print(f"  Nacimiento: {nacimiento}")
    print(f"  Años transcurridos: {calcular_edad(nacimiento, ahora)}")

    # ----------------------- RETO EXTRA -----------------------
    print("\n=== Reto extra: 10 formatos de la fecha de nacimiento ===")
    formatos = {
        "Día/Mes/Año": "%d/%m/%Y",
        "Año-Mes-Día (ISO)": "%Y-%m-%d",
        "Hora:Minuto:Segundo": "%H:%M:%S",
        "Día del año": "%j",
        "Día de la semana": "%A",
        "Nombre del mes": "%B",
        "Semana del año": "%U",
        "Fecha completa": "%c",
        "AM/PM 12h": "%I:%M %p",
        "Formato largo": "%A, %d de %B de %Y a las %H:%M",
    }
    for descripcion, patron in formatos.items():
        print(f"  {descripcion:22}: {nacimiento.strftime(patron)}")


if __name__ == "__main__":
    demostrar()
