"""
#41 - CAMISETA.RAR (compresión de archivos)

Comprime un archivo (o varios) en un .zip usando la librería estándar.

=========================== TEORÍA ===========================
Reto de COMPRESIÓN de ficheros. El módulo estándar `zipfile` crea archivos
.zip con distintos algoritmos (ZIP_DEFLATED comprime de verdad). Se puede
comprimir uno o varios ficheros y consultar el ratio de compresión.

NOTA: ni el archivo original ni el .zip se suben al repositorio; en la demo se
generan y borran al vuelo.

============================ PRÁCTICA ========================
"""

from __future__ import annotations

import os
import zipfile


def comprimir(archivos: list[str], destino_zip: str) -> None:
    with zipfile.ZipFile(destino_zip, "w", zipfile.ZIP_DEFLATED) as z:
        for archivo in archivos:
            z.write(archivo, arcname=os.path.basename(archivo))


def descomprimir(origen_zip: str, carpeta_destino: str) -> list[str]:
    with zipfile.ZipFile(origen_zip, "r") as z:
        z.extractall(carpeta_destino)
        return z.namelist()


def demo() -> None:
    print("=== camiseta.rar (usamos .zip) ===")
    origen = "camiseta.txt"
    destino = "camiseta.zip"
    # Creamos un fichero de ejemplo con contenido repetitivo (comprime bien)
    with open(origen, "w", encoding="utf-8") as f:
        f.write("MoureDev roadmap de retos de programación\n" * 500)

    tam_original = os.path.getsize(origen)
    comprimir([origen], destino)
    tam_comprimido = os.path.getsize(destino)

    print(f"  Original:   {tam_original:>7} bytes")
    print(f"  Comprimido: {tam_comprimido:>7} bytes")
    print(f"  Ratio:      {tam_comprimido / tam_original:.1%} del tamaño original")
    print(f"  Contenido del zip: {descomprimir(destino, '_extraido')}")

    # Limpieza (no se suben ficheros)
    for ruta in (origen, destino):
        os.remove(ruta)
    for ruta in os.listdir("_extraido"):
        os.remove(os.path.join("_extraido", ruta))
    os.rmdir("_extraido")
    print("  Ficheros temporales borrados.")


if __name__ == "__main__":
    demo()
