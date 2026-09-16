"""
#07 - PILAS Y COLAS

=========================== TEORÍA ===========================
PILA (stack) -> LIFO (Last In, First Out): el último en entrar es el primero
en salir, como una pila de platos. Operaciones: push (apilar) y pop (sacar).

COLA (queue) -> FIFO (First In, First Out): el primero en entrar es el primero
en salir, como una fila del supermercado. Operaciones: enqueue y dequeue.

En Python:
  - Una list sirve como pila eficiente (append / pop al final, O(1)).
  - Para una cola eficiente se usa collections.deque (popleft O(1)); usar
    list.pop(0) sería O(n).

============================ PRÁCTICA ========================
"""

from collections import deque


def demostrar_pila() -> None:
    print("=== PILA (LIFO) con list ===")
    pila: list[str] = []
    for item in ("A", "B", "C"):
        pila.append(item)
        print(f"  push {item} -> {pila}")
    while pila:
        print(f"  pop {pila.pop()} -> {pila}")


def demostrar_cola() -> None:
    print("\n=== COLA (FIFO) con deque ===")
    cola: deque[str] = deque()
    for item in ("A", "B", "C"):
        cola.append(item)
        print(f"  enqueue {item} -> {list(cola)}")
    while cola:
        print(f"  dequeue {cola.popleft()} -> {list(cola)}")


# ----------------------- RETO EXTRA -----------------------


def navegador(comandos: list[str]) -> None:
    """
    Simula adelante/atrás de un navegador con dos pilas.
    'atras'/'adelante' navegan; cualquier otra palabra es una web nueva.
    """
    print("\n=== Reto extra: navegador (pilas) ===")
    atras: list[str] = []
    adelante: list[str] = []
    actual: str | None = None
    for comando in comandos:
        if comando == "atras":
            if atras:
                adelante.append(actual)
                actual = atras.pop()
                print(f"  ← atrás -> {actual}")
            else:
                print("  ← no hay páginas anteriores")
        elif comando == "adelante":
            if adelante:
                atras.append(actual)
                actual = adelante.pop()
                print(f"  → adelante -> {actual}")
            else:
                print("  → no hay páginas siguientes")
        else:
            if actual is not None:
                atras.append(actual)
            actual = comando
            adelante.clear()
            print(f"  visitar '{comando}' -> {actual}")


def impresora(comandos: list[str]) -> None:
    """
    Simula una impresora compartida con una cola.
    'imprimir' saca e imprime un documento; el resto son documentos nuevos.
    """
    print("\n=== Reto extra: impresora (cola) ===")
    cola: deque[str] = deque()
    for comando in comandos:
        if comando == "imprimir":
            if cola:
                print(f"  🖨️  imprimiendo '{cola.popleft()}' (pendientes: {list(cola)})")
            else:
                print("  🖨️  no hay documentos en cola")
        else:
            cola.append(comando)
            print(f"  + en cola '{comando}' -> {list(cola)}")


if __name__ == "__main__":
    demostrar_pila()
    demostrar_cola()
    navegador(["mouredev.com", "python.org", "atras", "atras", "github.com", "adelante"])
    impresora(["informe.pdf", "foto.png", "imprimir", "nomina.docx", "imprimir", "imprimir", "imprimir"])
