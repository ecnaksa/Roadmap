"""
#45 - GITHUB OCTOVERSE (informe de usuario)

Genera un informe de un usuario de GitHub con 5 métricas usando su API
pública (no requiere autenticación, aunque el límite de peticiones es menor).

=========================== TEORÍA ===========================
Reto de CONSUMO DE API REST. La API de GitHub devuelve JSON. Con dos
endpoints (/users/{login} y /users/{login}/repos) se pueden calcular métricas
como el lenguaje más usado, número de repos, seguidores, stars y forks.

Con un token personal (variable GITHUB_TOKEN) el límite de peticiones sube;
aquí es opcional.

============================ PRÁCTICA ========================
"""

from __future__ import annotations

import json
import os
import urllib.error
import urllib.request
from collections import Counter

API = "https://api.github.com"


def _get(url: str) -> object:
    headers = {"User-Agent": "roadmap-ecnaksa", "Accept": "application/vnd.github+json"}
    token = os.getenv("GITHUB_TOKEN")
    if token:
        headers["Authorization"] = f"Bearer {token}"
    with urllib.request.urlopen(urllib.request.Request(url, headers=headers), timeout=10) as r:
        return json.load(r)


def informe(login: str) -> None:
    try:
        usuario = _get(f"{API}/users/{login}")
        repos = _get(f"{API}/users/{login}/repos?per_page=100&sort=updated")
    except urllib.error.HTTPError as e:
        print(f"  ❌ Error {e.code}: usuario '{login}' no encontrado o límite excedido.")
        return
    except urllib.error.URLError as e:
        print(f"  ❌ Sin conexión: {e}")
        return

    lenguajes = Counter(r["language"] for r in repos if r["language"])
    total_stars = sum(r["stargazers_count"] for r in repos)
    total_forks = sum(r["forks_count"] for r in repos)
    lenguaje_top = lenguajes.most_common(1)[0][0] if lenguajes else "—"

    print(f"\n===== INFORME OCTOVERSE: {usuario.get('name') or login} (@{login}) =====")
    print(f"  1. Lenguaje más usado:   {lenguaje_top}")
    print(f"  2. Repositorios públicos: {usuario['public_repos']}")
    print(f"  3. Seguidores / Seguidos: {usuario['followers']} / {usuario['following']}")
    print(f"  4. Stars totales:         {total_stars}")
    print(f"  5. Forks totales:         {total_forks}")
    if lenguajes:
        top3 = ", ".join(f"{lang} ({n})" for lang, n in lenguajes.most_common(3))
        print(f"  ⭐ Top lenguajes:         {top3}")


if __name__ == "__main__":
    print("=== Informe de usuario de GitHub ===")
    informe("mouredev")
