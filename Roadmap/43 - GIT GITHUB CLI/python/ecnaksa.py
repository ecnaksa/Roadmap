"""
#43 - GIT / GITHUB CLI

Interfaz de línea de comandos que ejecuta operaciones reales de Git desde el
terminal: init, ramas, estado, commit, historial, remoto, pull y push.

=========================== TEORÍA ===========================
Reto de INTEGRACIÓN CON EL SISTEMA. Se usa el módulo estándar `subprocess`
para invocar el binario `git` y capturar su salida. Cada opción del menú
corresponde a uno o varios comandos de Git.

============================ PRÁCTICA ========================
"""

from __future__ import annotations

import os
import subprocess


def git(*args: str, cwd: str | None = None) -> str:
    """Ejecuta un comando git y devuelve su salida (o el error controlado)."""
    try:
        resultado = subprocess.run(
            ["git", *args],
            cwd=cwd,
            capture_output=True,
            text=True,
            check=True,
        )
        return (resultado.stdout + resultado.stderr).strip()
    except FileNotFoundError:
        return "❌ Git no está instalado."
    except subprocess.CalledProcessError as e:
        return f"❌ Error: {(e.stderr or e.stdout).strip()}"


def menu() -> None:
    """Menú interactivo real (usa input)."""
    directorio = os.getcwd()
    opciones = """
--- GIT CLI ---
1. Establecer directorio de trabajo
2. Crear repositorio (git init)
3. Crear rama
4. Cambiar de rama
5. Ficheros pendientes (git status)
6. Commit (add . + commit)
7. Historial de commits
8. Eliminar rama
9. Establecer remoto
10. Pull
11. Push
12. Salir
Opción: """
    while True:
        opcion = input(opciones).strip()
        if opcion == "1":
            directorio = input("Ruta: ").strip() or directorio
            print(f"Directorio: {directorio}")
        elif opcion == "2":
            print(git("init", cwd=directorio))
        elif opcion == "3":
            print(git("branch", input("Nombre de la rama: ").strip(), cwd=directorio))
        elif opcion == "4":
            print(git("switch", input("Rama destino: ").strip(), cwd=directorio))
        elif opcion == "5":
            print(git("status", "--short", cwd=directorio) or "Sin cambios")
        elif opcion == "6":
            git("add", ".", cwd=directorio)
            print(git("commit", "-m", input("Mensaje: ").strip(), cwd=directorio))
        elif opcion == "7":
            print(git("log", "--oneline", "-10", cwd=directorio))
        elif opcion == "8":
            print(git("branch", "-d", input("Rama a eliminar: ").strip(), cwd=directorio))
        elif opcion == "9":
            print(git("remote", "add", "origin", input("URL del remoto: ").strip(), cwd=directorio))
        elif opcion == "10":
            print(git("pull", cwd=directorio))
        elif opcion == "11":
            print(git("push", cwd=directorio))
        elif opcion == "12":
            print("¡Hasta luego!")
            break
        else:
            print("Opción no válida.")


def demo() -> None:
    """Demostración no interactiva sobre un repo temporal."""
    import shutil
    import tempfile

    print("=== Git CLI (demo sobre un repositorio temporal) ===")
    tmp = tempfile.mkdtemp()
    try:
        print("2) init ->", git("init", "-b", "main", cwd=tmp).splitlines()[0])
        git("config", "user.email", "demo@demo.com", cwd=tmp)
        git("config", "user.name", "demo", cwd=tmp)
        with open(os.path.join(tmp, "hola.txt"), "w") as f:
            f.write("hola roadmap")
        print("5) status ->", git("status", "--short", cwd=tmp))
        git("add", ".", cwd=tmp)
        print("6) commit ->", git("commit", "-m", "primer commit", cwd=tmp).splitlines()[0])
        print("3) branch ->", git("branch", "feature", cwd=tmp) or "rama 'feature' creada")
        print("7) log ->", git("log", "--oneline", cwd=tmp))
    finally:
        shutil.rmtree(tmp)
        print("(repositorio temporal eliminado)")


if __name__ == "__main__":
    demo()
    # Para el CLI interactivo real, descomenta:
    # menu()
