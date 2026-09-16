"""
#37 - OASIS VS LINKIN PARK (API de Spotify)

Compara la popularidad de Oasis y Linkin Park usando la Web API de Spotify.

=========================== TEORÍA ===========================
Reto de CONSUMO DE API con autenticación OAuth 2.0 (flujo Client
Credentials). Pasos:
  1. Crear una app en https://developer.spotify.com y obtener CLIENT_ID/SECRET.
  2. Pedir un token con esas credenciales (POST a /api/token).
  3. Usar el token (cabecera Authorization: Bearer ...) para consultar
     endpoints (search de artistas, top-tracks, etc.).

Las credenciales NO se suben al repositorio: se leen de variables de entorno.
  export SPOTIFY_CLIENT_ID="..."
  export SPOTIFY_CLIENT_SECRET="..."

============================ PRÁCTICA ========================
"""

from __future__ import annotations

import base64
import json
import os
import urllib.parse
import urllib.request

API = "https://api.spotify.com/v1"
TOKEN_URL = "https://accounts.spotify.com/api/token"


def obtener_token(client_id: str, client_secret: str) -> str:
    credenciales = base64.b64encode(f"{client_id}:{client_secret}".encode()).decode()
    datos = urllib.parse.urlencode({"grant_type": "client_credentials"}).encode()
    req = urllib.request.Request(
        TOKEN_URL,
        data=datos,
        headers={"Authorization": f"Basic {credenciales}"},
    )
    with urllib.request.urlopen(req, timeout=10) as r:
        return json.load(r)["access_token"]


def _get(url: str, token: str) -> dict:
    req = urllib.request.Request(url, headers={"Authorization": f"Bearer {token}"})
    with urllib.request.urlopen(req, timeout=10) as r:
        return json.load(r)


def datos_banda(nombre: str, token: str) -> dict:
    query = urllib.parse.urlencode({"q": nombre, "type": "artist", "limit": 1})
    resultado = _get(f"{API}/search?{query}", token)
    artista = resultado["artists"]["items"][0]
    top = _get(f"{API}/artists/{artista['id']}/top-tracks?market=ES", token)
    cancion = max(top["tracks"], key=lambda t: t["popularity"], default=None)
    return {
        "nombre": artista["name"],
        "seguidores": artista["followers"]["total"],
        "popularidad": artista["popularity"],
        "top_cancion": cancion["name"] if cancion else "—",
    }


def comparar() -> None:
    client_id = os.getenv("SPOTIFY_CLIENT_ID")
    client_secret = os.getenv("SPOTIFY_CLIENT_SECRET")
    if not client_id or not client_secret:
        print("⚠️  Faltan credenciales. Configura las variables de entorno:")
        print("    export SPOTIFY_CLIENT_ID=...   export SPOTIFY_CLIENT_SECRET=...")
        print("    (Regístrate en https://developer.spotify.com)")
        return

    try:
        token = obtener_token(client_id, client_secret)
        oasis = datos_banda("Oasis", token)
        linkin = datos_banda("Linkin Park", token)
    except Exception as e:  # noqa: BLE001 - la API puede fallar de muchas formas
        print(f"❌ Error consultando Spotify: {e}")
        return

    print(f"{'Métrica':15} | {'Oasis':>15} | {'Linkin Park':>15}")
    print("-" * 51)
    for etiqueta, clave in [("Seguidores", "seguidores"), ("Popularidad", "popularidad")]:
        print(f"{etiqueta:15} | {oasis[clave]:>15} | {linkin[clave]:>15}")
    print(f"{'Top canción':15} | {oasis['top_cancion']:>15} | {linkin['top_cancion']:>15}")

    ganador = max((oasis, linkin), key=lambda b: (b["seguidores"], b["popularidad"]))["nombre"]
    print(f"\n🏆 Banda más popular (por seguidores/popularidad): {ganador}")


if __name__ == "__main__":
    print("=== Oasis vs Linkin Park (Spotify API) ===")
    comparar()
