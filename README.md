# 🐍 Roadmap de Retos de Programación — Soluciones en Python

Soluciones **completas** al [roadmap de retos de programación de MoureDev](https://github.com/mouredev/roadmap-retos-programacion),
resueltas en **Python** con un enfoque de **teoría + práctica**.

> Este repositorio es un trabajo de estudio personal basado en el proyecto
> original y gratuito de **[MoureDev (Brais Moure)](https://github.com/mouredev)**.
> Todos los enunciados (`ejercicio.md`) pertenecen a su autor. Aquí encontrarás
> mis propias soluciones. Ruta oficial: **[retosdeprogramacion.com/roadmap](https://retosdeprogramacion.com/roadmap)**.

---

## 🎯 ¿Qué es esto?

El roadmap está formado por **51 retos** que cubren desde la sintaxis más básica
hasta principios de arquitectura de software y proyectos completos. Este
repositorio resuelve **todos** ellos siguiendo la convención del proyecto
original (`Roadmap/<reto>/python/ecnaksa.py`), pero enriquecidos:

- **📖 Teoría:** cada solución empieza con un docstring que explica el concepto
  (qué es, para qué sirve, matices del lenguaje).
- **⚙️ Práctica:** código ejecutable, comentado e idiomático, que resuelve tanto
  el ejercicio principal como la **dificultad extra** opcional.
- **✅ Verificado:** todas las soluciones compilan y se ejecutan. Los ejercicios
  interactivos incluyen además una demostración no interactiva (`demo()`) para
  poder probarlos sin intervención.

---

## 🗂️ Estructura

```
Roadmap/
└── NN - NOMBRE DEL RETO/
    ├── ejercicio.md         # enunciado original (de MoureDev)
    └── python/
        └── ecnaksa.py       # solución: teoría (docstring) + práctica
```

## ▶️ Cómo ejecutar

Requiere **Python 3.10+** (probado en 3.11). No hacen falta dependencias
externas: todo usa la librería estándar.

```bash
# Ejecutar cualquier reto
python3 "Roadmap/06 - RECURSIVIDAD/python/ecnaksa.py"

# Ejecutar los tests del reto 13
python3 "Roadmap/13 - PRUEBAS UNITARIAS/python/ecnaksa.py"
```

Los retos marcados con 🌐 hacen peticiones a APIs. La PokéAPI (20) y GitHub (45)
son públicas; Spotify (37) y Twitch (40) necesitan credenciales, que se leen de
**variables de entorno** y **nunca** se suben al repositorio:

```bash
export SPOTIFY_CLIENT_ID=...     export SPOTIFY_CLIENT_SECRET=...
export TWITCH_CLIENT_ID=...      export TWITCH_CLIENT_SECRET=...
export GITHUB_TOKEN=...          # opcional, sube el límite de peticiones
```

---

## 📚 Índice de retos

### Fundamentos (00 – 30)
Conceptos esenciales del lenguaje, estructuras de datos, POO, patrones y SOLID.

| # | Concepto | Solución |
|---|----------|----------|
| 00 | Sintaxis, variables, tipos de datos y «Hola mundo» | [`ecnaksa.py`](Roadmap/00%20-%20SINTAXIS%2C%20VARIABLES%2C%20TIPOS%20DE%20DATOS%20Y%20HOLA%20MUNDO/python/ecnaksa.py) |
| 01 | Operadores y estructuras de control | [`ecnaksa.py`](Roadmap/01%20-%20OPERADORES%20Y%20ESTRUCTURAS%20DE%20CONTROL/python/ecnaksa.py) |
| 02 | Funciones y alcance (scope) | [`ecnaksa.py`](Roadmap/02%20-%20FUNCIONES%20Y%20ALCANCE/python/ecnaksa.py) |
| 03 | Estructuras de datos + agenda de contactos | [`ecnaksa.py`](Roadmap/03%20-%20ESTRUCTURAS%20DE%20DATOS/python/ecnaksa.py) |
| 04 | Cadenas: palíndromos, anagramas e isogramas | [`ecnaksa.py`](Roadmap/04%20-%20CADENAS%20DE%20CARACTERES/python/ecnaksa.py) |
| 05 | Paso por valor y por referencia | [`ecnaksa.py`](Roadmap/05%20-%20VALOR%20Y%20REFERENCIA/python/ecnaksa.py) |
| 06 | Recursividad: cuenta atrás, factorial y Fibonacci | [`ecnaksa.py`](Roadmap/06%20-%20RECURSIVIDAD/python/ecnaksa.py) |
| 07 | Pilas (LIFO) y colas (FIFO): navegador e impresora | [`ecnaksa.py`](Roadmap/07%20-%20PILAS%20Y%20COLAS/python/ecnaksa.py) |
| 08 | Clases: Persona, Pila y Cola | [`ecnaksa.py`](Roadmap/08%20-%20CLASES/python/ecnaksa.py) |
| 09 | Herencia: Animal y jerarquía de empresa | [`ecnaksa.py`](Roadmap/09%20-%20HERENCIA/python/ecnaksa.py) |
| 10 | Excepciones y excepción personalizada | [`ecnaksa.py`](Roadmap/10%20-%20EXCEPCIONES/python/ecnaksa.py) |
| 11 | Manejo de ficheros: gestión de ventas | [`ecnaksa.py`](Roadmap/11%20-%20MANEJO%20DE%20FICHEROS/python/ecnaksa.py) |
| 12 | JSON y XML a una clase común | [`ecnaksa.py`](Roadmap/12%20-%20JSON%20Y%20XML/python/ecnaksa.py) |
| 13 | Pruebas unitarias con unittest | [`ecnaksa.py`](Roadmap/13%20-%20PRUEBAS%20UNITARIAS/python/ecnaksa.py) |
| 14 | Fechas: edad y 10 formatos | [`ecnaksa.py`](Roadmap/14%20-%20FECHAS/python/ecnaksa.py) |
| 15 | Asincronía con asyncio | [`ecnaksa.py`](Roadmap/15%20-%20ASINCRON%C3%8DA/python/ecnaksa.py) |
| 16 | Expresiones regulares: email, teléfono y URL | [`ecnaksa.py`](Roadmap/16%20-%20EXPRESIONES%20REGULARES/python/ecnaksa.py) |
| 17 | Iteraciones: 10 mecanismos | [`ecnaksa.py`](Roadmap/17%20-%20ITERACIONES/python/ecnaksa.py) |
| 18 | Conjuntos y operaciones de sets | [`ecnaksa.py`](Roadmap/18%20-%20CONJUNTOS/python/ecnaksa.py) |
| 19 | Enumeraciones: días y estados de pedido | [`ecnaksa.py`](Roadmap/19%20-%20ENUMERACIONES/python/ecnaksa.py) |
| 20 | Peticiones HTTP: cliente de la PokéAPI 🌐 | [`ecnaksa.py`](Roadmap/20%20-%20PETICIONES%20HTTP/python/ecnaksa.py) |
| 21 | Callbacks: simulador de restaurante | [`ecnaksa.py`](Roadmap/21%20-%20CALLBACKS/python/ecnaksa.py) |
| 22 | Funciones de orden superior: análisis de estudiantes | [`ecnaksa.py`](Roadmap/22%20-%20FUNCIONES%20DE%20ORDEN%20SUPERIOR/python/ecnaksa.py) |
| 23 | Patrón Singleton: sesión de usuario | [`ecnaksa.py`](Roadmap/23%20-%20SINGLETON/python/ecnaksa.py) |
| 24 | Decoradores: cronómetro y contador de llamadas | [`ecnaksa.py`](Roadmap/24%20-%20DECORADORES/python/ecnaksa.py) |
| 25 | Logs con logging: gestor de tareas | [`ecnaksa.py`](Roadmap/25%20-%20LOGS/python/ecnaksa.py) |
| 26 | SOLID · SRP (Responsabilidad Única) | [`ecnaksa.py`](Roadmap/26%20-%20SOLID%20SRP/python/ecnaksa.py) |
| 27 | SOLID · OCP (Abierto/Cerrado) | [`ecnaksa.py`](Roadmap/27%20-%20SOLID%20OCP/python/ecnaksa.py) |
| 28 | SOLID · LSP (Sustitución de Liskov) | [`ecnaksa.py`](Roadmap/28%20-%20SOLID%20LSP/python/ecnaksa.py) |
| 29 | SOLID · ISP (Segregación de Interfaces) | [`ecnaksa.py`](Roadmap/29%20-%20SOLID%20ISP/python/ecnaksa.py) |
| 30 | SOLID · DIP (Inversión de Dependencias) | [`ecnaksa.py`](Roadmap/30%20-%20SOLID%20DIP/python/ecnaksa.py) |

### Proyectos y retos temáticos (31 – 50)
Programas completos que integran lo aprendido.

| # | Proyecto | Solución |
|---|----------|----------|
| 31 | Simulador de Juegos Olímpicos | [`ecnaksa.py`](Roadmap/31%20-%20SIMULADOR%20JUEGOS%20OL%C3%8DMPICOS/python/ecnaksa.py) |
| 32 | Batalla Deadpool y Wolverine | [`ecnaksa.py`](Roadmap/32%20-%20BATALLA%20DEADPOOL%20Y%20WOLVERINE/python/ecnaksa.py) |
| 33 | Rescatando a Mickey (laberinto 6x6) | [`ecnaksa.py`](Roadmap/33%20-%20RESCATANDO%20A%20MICKEY/python/ecnaksa.py) |
| 34 | Árbol genealógico (La Casa del Dragón) | [`ecnaksa.py`](Roadmap/34%20-%20%C3%81RBOL%20GENEAL%C3%93GICO%20LA%20CASA%20DEL%20DRAG%C3%93N/python/ecnaksa.py) |
| 35 | Repartiendo los Anillos de Poder | [`ecnaksa.py`](Roadmap/35%20-%20REPARTIENDO%20LOS%20ANILLOS%20DE%20PODER/python/ecnaksa.py) |
| 36 | El Sombrero Seleccionador | [`ecnaksa.py`](Roadmap/36%20-%20EL%20SOMBRERO%20SELECCIONADOR/python/ecnaksa.py) |
| 37 | Oasis vs Linkin Park (API de Spotify) 🌐 | [`ecnaksa.py`](Roadmap/37%20-%20OASIS%20VS%20LINKIN%20PARK/python/ecnaksa.py) |
| 38 | MoureDev Pro (sorteo desde CSV) | [`ecnaksa.py`](Roadmap/38%20-%20MOUREDEV%20PRO/python/ecnaksa.py) |
| 39 | Batman Day (reto doble) | [`ecnaksa.py`](Roadmap/39%20-%20BATMAN%20DAY/python/ecnaksa.py) |
| 40 | Fortnite Rubius Cup (API de Twitch) 🌐 | [`ecnaksa.py`](Roadmap/40%20-%20FORTNITE%20RUBIUS%20CUP/python/ecnaksa.py) |
| 41 | camiseta.rar (compresión de ficheros) | [`ecnaksa.py`](Roadmap/41%20-%20CAMISETA%20RAR/python/ecnaksa.py) |
| 42 | Torneo Dragon Ball (bracket eliminatorio) | [`ecnaksa.py`](Roadmap/42%20-%20TORNEO%20DRAGON%20BALL/python/ecnaksa.py) |
| 43 | Git / GitHub CLI (subprocess) | [`ecnaksa.py`](Roadmap/43%20-%20GIT%20GITHUB%20CLI/python/ecnaksa.py) |
| 44 | Cuenta atrás MoureDev Pro (hilos + UTC) | [`ecnaksa.py`](Roadmap/44%20-%20CUENTA%20ATR%C3%81S%20MOUREDEV%20PRO/python/ecnaksa.py) |
| 45 | GitHub Octoverse (API de GitHub) 🌐 | [`ecnaksa.py`](Roadmap/45%20-%20GITHUB%20OCTOVERSE/python/ecnaksa.py) |
| 46 | X vs Bluesky (red social) | [`ecnaksa.py`](Roadmap/46%20-%20X%20VS%20BLUESKY/python/ecnaksa.py) |
| 47 | Calendario de adviento (ASCII) | [`ecnaksa.py`](Roadmap/47%20-%20CALENDARIO%20DE%20ADVIENTO/python/ecnaksa.py) |
| 48 | Árbol de Navidad dinámico | [`ecnaksa.py`](Roadmap/48%20-%20%C3%81RBOL%20DE%20NAVIDAD/python/ecnaksa.py) |
| 49 | El almacén de Papá Noel (Mastermind) | [`ecnaksa.py`](Roadmap/49%20-%20EL%20ALMAC%C3%89N%20DE%20PAP%C3%81%20NOEL/python/ecnaksa.py) |
| 50 | Planificador de objetivos de Año Nuevo | [`ecnaksa.py`](Roadmap/50%20-%20PLANIFICADOR%20DE%20OBJETIVOS%20DE%20A%C3%91O%20NUEVO/python/ecnaksa.py) |

> 🌐 = requiere conexión a internet o credenciales de API.

---

## 🧭 Recorrido por bloques

- **00–05 · Bases:** sintaxis, operadores, funciones, estructuras de datos,
  cadenas y el paso por valor/referencia.
- **06–10 · Algoritmos y POO:** recursividad, pilas/colas, clases, herencia y
  excepciones.
- **11–20 · Herramientas del día a día:** ficheros, JSON/XML, tests, fechas,
  asincronía, regex, iteraciones, conjuntos, enums y HTTP.
- **21–25 · Técnicas avanzadas:** callbacks, funciones de orden superior,
  singleton, decoradores y logging.
- **26–30 · SOLID:** los cinco principios con ejemplo correcto e incorrecto.
- **31–50 · Proyectos:** simuladores, juegos, clientes de API, dibujos por
  terminal y utilidades, muchos con temática de cultura pop.

---

## 🙌 Créditos

- Enunciados y roadmap original: **[MoureDev](https://github.com/mouredev/roadmap-retos-programacion)**.
- Soluciones en Python: **[@ecnaksa](https://github.com/ecnaksa)**.
