"""
#40 - FORTNITE RUBIUS CUP (API de Twitch)

Obtiene el número de seguidores en Twitch y la fecha de creación de cada
participante de la copa, y genera dos rankings: por seguidores y por
antigüedad. Si un participante no existe en Twitch, se refleja.

=========================== TEORÍA ===========================
Reto de CONSUMO DE API con OAuth (Client Credentials de Twitch):
  1. Registrar una app en https://dev.twitch.tv/console y obtener
     CLIENT_ID / CLIENT_SECRET.
  2. Pedir un app access token (POST a /oauth2/token).
  3. Consultar /helix/users (datos del canal) y /helix/channels/followers
     (número de seguidores) con las cabeceras Client-Id y Authorization.

Credenciales por variables de entorno (NO se suben):
  export TWITCH_CLIENT_ID=...   export TWITCH_CLIENT_SECRET=...

============================ PRÁCTICA ========================
"""

from __future__ import annotations

import json
import os
import urllib.parse
import urllib.request

TOKEN_URL = "https://id.twitch.tv/oauth2/token"
HELIX = "https://api.twitch.tv/helix"

PARTICIPANTES = ["rubius", "auronplay", "ibai", "thegrefg", "uncanalquenoexiste_xyz"]


def obtener_token(client_id: str, client_secret: str) -> str:
    datos = urllib.parse.urlencode({
        "client_id": client_id,
        "client_secret": client_secret,
        "grant_type": "client_credentials",
    }).encode()
    with urllib.request.urlopen(urllib.request.Request(TOKEN_URL, data=datos), timeout=10) as r:
        return json.load(r)["access_token"]


def _get(url: str, headers: dict) -> dict:
    with urllib.request.urlopen(urllib.request.Request(url, headers=headers), timeout=10) as r:
        return json.load(r)


def datos_participante(login: str, headers: dict) -> dict | None:
    usuarios = _get(f"{HELIX}/users?login={login}", headers)["data"]
    if not usuarios:
        return None
    u = usuarios[0]
    seguidores = _get(f"{HELIX}/channels/followers?broadcaster_id={u['id']}", headers)
    return {
        "login": u["login"],
        "seguidores": seguidores.get("total", 0),
        "creacion": u["created_at"][:10],
    }


def generar_rankings() -> None:
    client_id = os.getenv("TWITCH_CLIENT_ID")
    client_secret = os.getenv("TWITCH_CLIENT_SECRET")
    if not client_id or not client_secret:
        print("⚠️  Faltan credenciales de Twitch. Configura:")
        print("    export TWITCH_CLIENT_ID=...   export TWITCH_CLIENT_SECRET=...")
        print("    (Regístrate en https://dev.twitch.tv/console)")
        return

    try:
        token = obtener_token(client_id, client_secret)
    except Exception as e:  # noqa: BLE001
        print(f"❌ No se pudo autenticar en Twitch: {e}")
        return

    headers = {"Client-Id": client_id, "Authorization": f"Bearer {token}"}
    encontrados, no_encontrados = [], []
    for login in PARTICIPANTES:
        try:
            datos = datos_participante(login, headers)
        except Exception as e:  # noqa: BLE001
            print(f"  Error con '{login}': {e}")
            continue
        (encontrados if datos else no_encontrados).append(datos or login)

    print("\n🏆 Ranking por SEGUIDORES:")
    for i, p in enumerate(sorted(encontrados, key=lambda d: d["seguidores"], reverse=True), 1):
        print(f"  {i}. {p['login']:15} {p['seguidores']:>12,} seguidores")

    print("\n📅 Ranking por ANTIGÜEDAD (cuenta más antigua primero):")
    for i, p in enumerate(sorted(encontrados, key=lambda d: d["creacion"]), 1):
        print(f"  {i}. {p['login']:15} desde {p['creacion']}")

    if no_encontrados:
        print("\n❔ Sin cuenta de Twitch:", ", ".join(no_encontrados))


if __name__ == "__main__":
    print("=== Fortnite Rubius Cup — estadísticas de Twitch ===")
    generar_rankings()
