"""
#20 - PETICIONES HTTP

=========================== TEORÍA ===========================
Una PETICIÓN HTTP solicita datos a un servidor. Los métodos más comunes son
GET (obtener) y POST (enviar). El servidor responde con un código de estado
(200 = OK, 404 = no encontrado, 500 = error del servidor...) y un cuerpo.

Se usa la librería estándar `urllib.request` (sin dependencias externas).
En proyectos reales suele preferirse la librería `requests` por comodidad.

============================ PRÁCTICA ========================
NOTA: requiere conexión a internet. Se controla el fallo con try/except.
"""

import json
import urllib.error
import urllib.request

TIMEOUT = 10


def obtener(url: str) -> tuple[int, str]:
    """Realiza un GET y devuelve (código de estado, cuerpo)."""
    peticion = urllib.request.Request(url, headers={"User-Agent": "roadmap-ecnaksa"})
    with urllib.request.urlopen(peticion, timeout=TIMEOUT) as respuesta:
        return respuesta.status, respuesta.read().decode("utf-8", "replace")


def peticion_basica() -> None:
    print("=== Petición HTTP básica ===")
    url = "https://example.com"
    try:
        estado, cuerpo = obtener(url)
        print(f"  GET {url} -> {estado} ({'OK' if estado == 200 else 'error'})")
        print(f"  Primeros 120 caracteres:\n  {cuerpo[:120].strip()}...")
    except urllib.error.URLError as e:
        print(f"  No se pudo conectar: {e}")


# ----------------------- RETO EXTRA -----------------------
# Cliente de la PokéAPI (https://pokeapi.co)


def _get_json(url: str) -> dict:
    _, cuerpo = obtener(url)
    return json.loads(cuerpo)


def info_pokemon(nombre_o_id: str) -> None:
    try:
        p = _get_json(f"https://pokeapi.co/api/v2/pokemon/{str(nombre_o_id).lower()}")
    except urllib.error.HTTPError as e:
        if e.code == 404:
            print(f"  ✗ Pokémon '{nombre_o_id}' no encontrado.")
        else:
            print(f"  ✗ Error HTTP {e.code}")
        return
    except urllib.error.URLError as e:
        print(f"  ✗ Sin conexión: {e}")
        return

    tipos = ", ".join(t["type"]["name"] for t in p["types"])
    print(f"  Nombre: {p['name'].capitalize()} (id {p['id']})")
    print(f"  Peso:   {p['weight'] / 10} kg   Altura: {p['height'] / 10} m")
    print(f"  Tipos:  {tipos}")

    # Cadena de evoluciones
    try:
        especie = _get_json(p["species"]["url"])
        cadena = _get_json(especie["evolution_chain"]["url"])["chain"]
        evoluciones = []
        nodo = cadena
        while nodo:
            evoluciones.append(nodo["species"]["name"].capitalize())
            nodo = nodo["evolves_to"][0] if nodo["evolves_to"] else None
        print(f"  Evoluciones: {' -> '.join(evoluciones)}")
    except (urllib.error.URLError, KeyError, IndexError):
        print("  Evoluciones: (no disponibles)")

    juegos = ", ".join(g["version"]["name"] for g in p["game_indices"][:8])
    print(f"  Juegos: {juegos or '(desconocidos)'}...")


if __name__ == "__main__":
    peticion_basica()
    print("\n=== Reto extra: PokéAPI ===")
    info_pokemon("pikachu")
    print()
    info_pokemon("charizard")
