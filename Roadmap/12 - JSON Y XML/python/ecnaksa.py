"""
#12 - JSON Y XML

=========================== TEORÍA ===========================
JSON (JavaScript Object Notation) y XML (eXtensible Markup Language) son
formatos de intercambio de datos.
  - JSON: ligero, basado en pares clave:valor y listas. En Python se maneja
    con el módulo `json` (json.dump / json.load).
  - XML: basado en etiquetas jerárquicas. En Python se maneja con el módulo
    `xml.etree.ElementTree`.

============================ PRÁCTICA ========================
"""

import json
import os
import xml.etree.ElementTree as ET
from dataclasses import dataclass, field

RUTA_JSON = "datos.json"
RUTA_XML = "datos.xml"

DATOS = {
    "nombre": "ecnaksa",
    "edad": 30,
    "fecha_nacimiento": "1994-05-12",
    "lenguajes": ["Python", "JavaScript", "Rust"],
}


def crear_json() -> None:
    with open(RUTA_JSON, "w", encoding="utf-8") as f:
        json.dump(DATOS, f, indent=2, ensure_ascii=False)


def crear_xml() -> None:
    raiz = ET.Element("persona")
    ET.SubElement(raiz, "nombre").text = DATOS["nombre"]
    ET.SubElement(raiz, "edad").text = str(DATOS["edad"])
    ET.SubElement(raiz, "fecha_nacimiento").text = DATOS["fecha_nacimiento"]
    lenguajes = ET.SubElement(raiz, "lenguajes")
    for lang in DATOS["lenguajes"]:
        ET.SubElement(lenguajes, "lenguaje").text = lang
    ET.ElementTree(raiz).write(RUTA_XML, encoding="utf-8", xml_declaration=True)


# ----------------------- RETO EXTRA -----------------------


@dataclass
class Persona:
    nombre: str
    edad: int
    fecha_nacimiento: str
    lenguajes: list[str] = field(default_factory=list)


def leer_desde_json() -> Persona:
    with open(RUTA_JSON, "r", encoding="utf-8") as f:
        d = json.load(f)
    return Persona(d["nombre"], d["edad"], d["fecha_nacimiento"], d["lenguajes"])


def leer_desde_xml() -> Persona:
    raiz = ET.parse(RUTA_XML).getroot()
    return Persona(
        nombre=raiz.findtext("nombre"),
        edad=int(raiz.findtext("edad")),
        fecha_nacimiento=raiz.findtext("fecha_nacimiento"),
        lenguajes=[e.text for e in raiz.find("lenguajes")],
    )


if __name__ == "__main__":
    print("=== Crear y mostrar JSON y XML ===")
    crear_json()
    crear_xml()
    print("--- JSON ---")
    print(open(RUTA_JSON, encoding="utf-8").read())
    print("--- XML ---")
    print(open(RUTA_XML, encoding="utf-8").read())

    print("\n=== Reto extra: cargar ambos en una clase común ===")
    print(f"  desde JSON -> {leer_desde_json()}")
    print(f"  desde XML  -> {leer_desde_xml()}")

    for ruta in (RUTA_JSON, RUTA_XML):
        os.remove(ruta)
    print(f"\n  Ficheros borrados: {not os.path.exists(RUTA_JSON) and not os.path.exists(RUTA_XML)}")
