"""
#29 - SOLID: ISP (Interface Segregation Principle)

=========================== TEORÍA ===========================
ISP — Principio de Segregación de Interfaces:
  "Ningún cliente debería verse obligado a depender de métodos que no usa."
Es preferible tener muchas interfaces pequeñas y específicas que una única
interfaz "gorda". Así, una clase solo implementa lo que realmente necesita.

En Python las "interfaces" se modelan con clases base abstractas (ABC) o con
Protocol. Aquí usamos ABC para dejar clara la segregación.

============================ PRÁCTICA ========================
"""

from abc import ABC, abstractmethod


# ---------- INCORRECTO: interfaz "gorda" ----------
class MultifuncionMal(ABC):
    @abstractmethod
    def imprimir(self, doc: str): ...
    @abstractmethod
    def escanear(self, doc: str): ...
    @abstractmethod
    def enviar_fax(self, doc: str): ...


# Una impresora sencilla se vería OBLIGADA a implementar escanear/fax
# aunque no pueda hacerlo (violaría ISP y probablemente el LSP).


# ---------- CORRECTO: interfaces pequeñas y segregadas ----------
class Impresora(ABC):
    @abstractmethod
    def imprimir(self, doc: str) -> str: ...


class Escaner(ABC):
    @abstractmethod
    def escanear(self, doc: str) -> str: ...


class Fax(ABC):
    @abstractmethod
    def enviar_fax(self, doc: str) -> str: ...


class ImpresoraBN(Impresora):
    def imprimir(self, doc): return f"🖨️  (B/N) imprimiendo '{doc}'"


class ImpresoraColor(Impresora):
    def imprimir(self, doc): return f"🖨️  (color) imprimiendo '{doc}'"


class Multifuncion(Impresora, Escaner, Fax):
    def imprimir(self, doc): return f"🖨️  imprimiendo '{doc}'"
    def escanear(self, doc): return f"📠 escaneando '{doc}'"
    def enviar_fax(self, doc): return f"✉️  enviando fax '{doc}'"


if __name__ == "__main__":
    print("=== ISP: cada clase implementa solo lo que necesita ===")
    bn = ImpresoraBN()
    color = ImpresoraColor()
    multi = Multifuncion()

    print(f"  {bn.imprimir('carta.txt')}")
    print(f"  {color.imprimir('foto.png')}")
    print(f"  {multi.imprimir('informe.pdf')}")
    print(f"  {multi.escanear('dni.jpg')}")
    print(f"  {multi.enviar_fax('contrato.pdf')}")

    print("\n=== Comprobación del principio ===")
    print(f"  ¿ImpresoraBN es Escaner? {isinstance(bn, Escaner)}  (correcto: no arrastra métodos que no usa)")
    print(f"  ¿Multifuncion es Escaner? {isinstance(multi, Escaner)}")
