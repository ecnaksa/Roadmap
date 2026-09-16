"""
#25 - LOGS

=========================== TEORÍA ===========================
El LOGGING registra eventos de un programa para diagnóstico y auditoría.
Es superior a usar print() porque permite niveles de severidad, formato,
destinos (consola, fichero...) y activar/desactivar por configuración.

Niveles del módulo estándar `logging` (de menor a mayor severidad):
  DEBUG < INFO < WARNING < ERROR < CRITICAL
El "nivel" configurado filtra: solo se emiten mensajes de igual o mayor nivel.

============================ PRÁCTICA ========================
"""

import logging
import time

logging.basicConfig(
    level=logging.DEBUG,
    format="%(asctime)s [%(levelname)s] %(message)s",
    datefmt="%H:%M:%S",
)
log = logging.getLogger("roadmap")


def demostrar_niveles() -> None:
    print("=== Niveles de severidad ===")
    log.debug("Mensaje DEBUG: detalle para desarrolladores")
    log.info("Mensaje INFO: todo va según lo esperado")
    log.warning("Mensaje WARNING: algo inusual, pero no es un error")
    log.error("Mensaje ERROR: ha fallado una operación")
    log.critical("Mensaje CRITICAL: fallo grave, el programa peligra")


# ----------------------- RETO EXTRA -----------------------


class GestorTareas:
    def __init__(self) -> None:
        self.tareas: dict[str, str] = {}

    def anadir(self, nombre: str, descripcion: str) -> None:
        inicio = time.perf_counter()
        if nombre in self.tareas:
            log.warning("La tarea '%s' ya existe; se sobrescribe", nombre)
        self.tareas[nombre] = descripcion
        log.info("Tarea añadida: '%s' (%.6fs)", nombre, time.perf_counter() - inicio)

    def eliminar(self, nombre: str) -> None:
        inicio = time.perf_counter()
        if self.tareas.pop(nombre, None) is None:
            log.error("No se puede eliminar: '%s' no existe", nombre)
        else:
            log.info("Tarea eliminada: '%s' (%.6fs)", nombre, time.perf_counter() - inicio)

    def listar(self) -> None:
        log.debug("Listando %d tarea(s)", len(self.tareas))
        for nombre, desc in self.tareas.items():
            print(f"  - {nombre}: {desc}")


if __name__ == "__main__":
    demostrar_niveles()

    print("\n=== Reto extra: gestor de tareas con logs ===")
    gestor = GestorTareas()
    gestor.anadir("Estudiar", "Repasar decoradores")
    gestor.anadir("Comprar", "Leche y pan")
    gestor.eliminar("Inexistente")   # provoca un ERROR de log
    gestor.eliminar("Comprar")
    gestor.listar()
