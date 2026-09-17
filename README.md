# 🧠 Roadmap de Retos de Programación — Python · C · C++

Soluciones **completas** al [roadmap de retos de programación de MoureDev](https://github.com/mouredev/roadmap-retos-programacion),
resueltas en **tres lenguajes** (Python, C y C++) con un enfoque de **teoría + práctica**.

> Trabajo de estudio personal basado en el proyecto original y gratuito de
> **[MoureDev (Brais Moure)](https://github.com/mouredev)**. Los enunciados
> (`ejercicio.md`) pertenecen a su autor; aquí encontrarás mis propias
> soluciones. Ruta oficial: **[retosdeprogramacion.com/roadmap](https://retosdeprogramacion.com/roadmap)**.

---

## 🎯 ¿Qué es esto?

El roadmap son **51 retos** que van desde la sintaxis básica hasta principios
de arquitectura (SOLID) y proyectos completos. Este repositorio los resuelve
**todos, en Python, C y C++** (153 soluciones en total), siguiendo la
convención del proyecto original (`Roadmap/<reto>/<lenguaje>/ecnaksa.<ext>`) y
enriquecidos:

- **📖 Teoría:** cada solución empieza con una explicación del concepto,
  adaptada a las particularidades de cada lenguaje (p. ej. cómo se emula la
  herencia o las excepciones en C).
- **⚙️ Práctica:** código ejecutable, comentado e idiomático, que resuelve el
  ejercicio principal **y la dificultad extra** opcional.
- **✅ Verificado:** las 153 soluciones compilan y se ejecutan sin errores.

### Un mismo reto, tres enfoques
Comparar el mismo problema en tres lenguajes es muy didáctico:
- **Python** — conciso y expresivo; ideal para centrarse en el concepto.
- **C++** — POO, plantillas y STL (clases, `std::vector`, `std::function`...).
- **C** — bajo nivel; se ven los mecanismos «por debajo»: punteros, gestión
  manual de memoria, `struct` + punteros a función para emular clases,
  interfaces y polimorfismo, `setjmp/longjmp` para emular excepciones, etc.

---

## 🗂️ Estructura

```
Roadmap/
└── NN - NOMBRE DEL RETO/
    ├── ejercicio.md          # enunciado original (de MoureDev)
    ├── python/ecnaksa.py     # solución en Python
    ├── c/ecnaksa.c           # solución en C
    └── c++/ecnaksa.cpp       # solución en C++
```

## ▶️ Cómo ejecutar

```bash
# Python (3.10+)
python3 "Roadmap/06 - RECURSIVIDAD/python/ecnaksa.py"

# C (C11)
gcc -std=c11 "Roadmap/06 - RECURSIVIDAD/c/ecnaksa.c" -o prog -lm -lpthread && ./prog

# C++ (C++20)
g++ -std=c++20 "Roadmap/06 - RECURSIVIDAD/c++/ecnaksa.cpp" -o prog && ./prog
```

Flags útiles según el reto: `-lpthread` (asincronía, cuenta atrás),
`-lz` (compresión del reto 41), `-lm` (matemáticas en C).

Los retos marcados con 🌐 hacen peticiones a APIs. La PokéAPI (20) y GitHub (45)
son públicas; Spotify (37) y Twitch (40) requieren credenciales. En C/C++ las
peticiones HTTP se hacen invocando `curl`. Las credenciales se leen de
**variables de entorno** y **nunca** se suben:

```bash
export SPOTIFY_CLIENT_ID=...   export SPOTIFY_CLIENT_SECRET=...
export TWITCH_CLIENT_ID=...    export TWITCH_CLIENT_SECRET=...
export GITHUB_TOKEN=...        # opcional, sube el límite de peticiones
```

---

## 📚 Índice de retos

Cada fila enlaza a la solución en los tres lenguajes.

### Fundamentos (00 – 30)

| # | Concepto | Soluciones |
|---|----------|------------|
| 00 | Sintaxis, variables, tipos y «Hola mundo» | [Py](Roadmap/00%20-%20SINTAXIS%2C%20VARIABLES%2C%20TIPOS%20DE%20DATOS%20Y%20HOLA%20MUNDO/python/ecnaksa.py) · [C](Roadmap/00%20-%20SINTAXIS%2C%20VARIABLES%2C%20TIPOS%20DE%20DATOS%20Y%20HOLA%20MUNDO/c/ecnaksa.c) · [C++](Roadmap/00%20-%20SINTAXIS%2C%20VARIABLES%2C%20TIPOS%20DE%20DATOS%20Y%20HOLA%20MUNDO/c%2B%2B/ecnaksa.cpp) |
| 01 | Operadores y estructuras de control | [Py](Roadmap/01%20-%20OPERADORES%20Y%20ESTRUCTURAS%20DE%20CONTROL/python/ecnaksa.py) · [C](Roadmap/01%20-%20OPERADORES%20Y%20ESTRUCTURAS%20DE%20CONTROL/c/ecnaksa.c) · [C++](Roadmap/01%20-%20OPERADORES%20Y%20ESTRUCTURAS%20DE%20CONTROL/c%2B%2B/ecnaksa.cpp) |
| 02 | Funciones y alcance | [Py](Roadmap/02%20-%20FUNCIONES%20Y%20ALCANCE/python/ecnaksa.py) · [C](Roadmap/02%20-%20FUNCIONES%20Y%20ALCANCE/c/ecnaksa.c) · [C++](Roadmap/02%20-%20FUNCIONES%20Y%20ALCANCE/c%2B%2B/ecnaksa.cpp) |
| 03 | Estructuras de datos + agenda | [Py](Roadmap/03%20-%20ESTRUCTURAS%20DE%20DATOS/python/ecnaksa.py) · [C](Roadmap/03%20-%20ESTRUCTURAS%20DE%20DATOS/c/ecnaksa.c) · [C++](Roadmap/03%20-%20ESTRUCTURAS%20DE%20DATOS/c%2B%2B/ecnaksa.cpp) |
| 04 | Cadenas: palíndromo, anagrama, isograma | [Py](Roadmap/04%20-%20CADENAS%20DE%20CARACTERES/python/ecnaksa.py) · [C](Roadmap/04%20-%20CADENAS%20DE%20CARACTERES/c/ecnaksa.c) · [C++](Roadmap/04%20-%20CADENAS%20DE%20CARACTERES/c%2B%2B/ecnaksa.cpp) |
| 05 | Paso por valor y por referencia | [Py](Roadmap/05%20-%20VALOR%20Y%20REFERENCIA/python/ecnaksa.py) · [C](Roadmap/05%20-%20VALOR%20Y%20REFERENCIA/c/ecnaksa.c) · [C++](Roadmap/05%20-%20VALOR%20Y%20REFERENCIA/c%2B%2B/ecnaksa.cpp) |
| 06 | Recursividad: factorial y Fibonacci | [Py](Roadmap/06%20-%20RECURSIVIDAD/python/ecnaksa.py) · [C](Roadmap/06%20-%20RECURSIVIDAD/c/ecnaksa.c) · [C++](Roadmap/06%20-%20RECURSIVIDAD/c%2B%2B/ecnaksa.cpp) |
| 07 | Pilas (LIFO) y colas (FIFO) | [Py](Roadmap/07%20-%20PILAS%20Y%20COLAS/python/ecnaksa.py) · [C](Roadmap/07%20-%20PILAS%20Y%20COLAS/c/ecnaksa.c) · [C++](Roadmap/07%20-%20PILAS%20Y%20COLAS/c%2B%2B/ecnaksa.cpp) |
| 08 | Clases | [Py](Roadmap/08%20-%20CLASES/python/ecnaksa.py) · [C](Roadmap/08%20-%20CLASES/c/ecnaksa.c) · [C++](Roadmap/08%20-%20CLASES/c%2B%2B/ecnaksa.cpp) |
| 09 | Herencia y polimorfismo | [Py](Roadmap/09%20-%20HERENCIA/python/ecnaksa.py) · [C](Roadmap/09%20-%20HERENCIA/c/ecnaksa.c) · [C++](Roadmap/09%20-%20HERENCIA/c%2B%2B/ecnaksa.cpp) |
| 10 | Excepciones | [Py](Roadmap/10%20-%20EXCEPCIONES/python/ecnaksa.py) · [C](Roadmap/10%20-%20EXCEPCIONES/c/ecnaksa.c) · [C++](Roadmap/10%20-%20EXCEPCIONES/c%2B%2B/ecnaksa.cpp) |
| 11 | Manejo de ficheros | [Py](Roadmap/11%20-%20MANEJO%20DE%20FICHEROS/python/ecnaksa.py) · [C](Roadmap/11%20-%20MANEJO%20DE%20FICHEROS/c/ecnaksa.c) · [C++](Roadmap/11%20-%20MANEJO%20DE%20FICHEROS/c%2B%2B/ecnaksa.cpp) |
| 12 | JSON y XML | [Py](Roadmap/12%20-%20JSON%20Y%20XML/python/ecnaksa.py) · [C](Roadmap/12%20-%20JSON%20Y%20XML/c/ecnaksa.c) · [C++](Roadmap/12%20-%20JSON%20Y%20XML/c%2B%2B/ecnaksa.cpp) |
| 13 | Pruebas unitarias | [Py](Roadmap/13%20-%20PRUEBAS%20UNITARIAS/python/ecnaksa.py) · [C](Roadmap/13%20-%20PRUEBAS%20UNITARIAS/c/ecnaksa.c) · [C++](Roadmap/13%20-%20PRUEBAS%20UNITARIAS/c%2B%2B/ecnaksa.cpp) |
| 14 | Fechas | [Py](Roadmap/14%20-%20FECHAS/python/ecnaksa.py) · [C](Roadmap/14%20-%20FECHAS/c/ecnaksa.c) · [C++](Roadmap/14%20-%20FECHAS/c%2B%2B/ecnaksa.cpp) |
| 15 | Asincronía / concurrencia | [Py](Roadmap/15%20-%20ASINCRON%C3%8DA/python/ecnaksa.py) · [C](Roadmap/15%20-%20ASINCRON%C3%8DA/c/ecnaksa.c) · [C++](Roadmap/15%20-%20ASINCRON%C3%8DA/c%2B%2B/ecnaksa.cpp) |
| 16 | Expresiones regulares | [Py](Roadmap/16%20-%20EXPRESIONES%20REGULARES/python/ecnaksa.py) · [C](Roadmap/16%20-%20EXPRESIONES%20REGULARES/c/ecnaksa.c) · [C++](Roadmap/16%20-%20EXPRESIONES%20REGULARES/c%2B%2B/ecnaksa.cpp) |
| 17 | Iteraciones | [Py](Roadmap/17%20-%20ITERACIONES/python/ecnaksa.py) · [C](Roadmap/17%20-%20ITERACIONES/c/ecnaksa.c) · [C++](Roadmap/17%20-%20ITERACIONES/c%2B%2B/ecnaksa.cpp) |
| 18 | Conjuntos | [Py](Roadmap/18%20-%20CONJUNTOS/python/ecnaksa.py) · [C](Roadmap/18%20-%20CONJUNTOS/c/ecnaksa.c) · [C++](Roadmap/18%20-%20CONJUNTOS/c%2B%2B/ecnaksa.cpp) |
| 19 | Enumeraciones | [Py](Roadmap/19%20-%20ENUMERACIONES/python/ecnaksa.py) · [C](Roadmap/19%20-%20ENUMERACIONES/c/ecnaksa.c) · [C++](Roadmap/19%20-%20ENUMERACIONES/c%2B%2B/ecnaksa.cpp) |
| 20 | Peticiones HTTP (PokéAPI) 🌐 | [Py](Roadmap/20%20-%20PETICIONES%20HTTP/python/ecnaksa.py) · [C](Roadmap/20%20-%20PETICIONES%20HTTP/c/ecnaksa.c) · [C++](Roadmap/20%20-%20PETICIONES%20HTTP/c%2B%2B/ecnaksa.cpp) |
| 21 | Callbacks | [Py](Roadmap/21%20-%20CALLBACKS/python/ecnaksa.py) · [C](Roadmap/21%20-%20CALLBACKS/c/ecnaksa.c) · [C++](Roadmap/21%20-%20CALLBACKS/c%2B%2B/ecnaksa.cpp) |
| 22 | Funciones de orden superior | [Py](Roadmap/22%20-%20FUNCIONES%20DE%20ORDEN%20SUPERIOR/python/ecnaksa.py) · [C](Roadmap/22%20-%20FUNCIONES%20DE%20ORDEN%20SUPERIOR/c/ecnaksa.c) · [C++](Roadmap/22%20-%20FUNCIONES%20DE%20ORDEN%20SUPERIOR/c%2B%2B/ecnaksa.cpp) |
| 23 | Singleton | [Py](Roadmap/23%20-%20SINGLETON/python/ecnaksa.py) · [C](Roadmap/23%20-%20SINGLETON/c/ecnaksa.c) · [C++](Roadmap/23%20-%20SINGLETON/c%2B%2B/ecnaksa.cpp) |
| 24 | Decoradores | [Py](Roadmap/24%20-%20DECORADORES/python/ecnaksa.py) · [C](Roadmap/24%20-%20DECORADORES/c/ecnaksa.c) · [C++](Roadmap/24%20-%20DECORADORES/c%2B%2B/ecnaksa.cpp) |
| 25 | Logs | [Py](Roadmap/25%20-%20LOGS/python/ecnaksa.py) · [C](Roadmap/25%20-%20LOGS/c/ecnaksa.c) · [C++](Roadmap/25%20-%20LOGS/c%2B%2B/ecnaksa.cpp) |
| 26 | SOLID · SRP | [Py](Roadmap/26%20-%20SOLID%20SRP/python/ecnaksa.py) · [C](Roadmap/26%20-%20SOLID%20SRP/c/ecnaksa.c) · [C++](Roadmap/26%20-%20SOLID%20SRP/c%2B%2B/ecnaksa.cpp) |
| 27 | SOLID · OCP | [Py](Roadmap/27%20-%20SOLID%20OCP/python/ecnaksa.py) · [C](Roadmap/27%20-%20SOLID%20OCP/c/ecnaksa.c) · [C++](Roadmap/27%20-%20SOLID%20OCP/c%2B%2B/ecnaksa.cpp) |
| 28 | SOLID · LSP | [Py](Roadmap/28%20-%20SOLID%20LSP/python/ecnaksa.py) · [C](Roadmap/28%20-%20SOLID%20LSP/c/ecnaksa.c) · [C++](Roadmap/28%20-%20SOLID%20LSP/c%2B%2B/ecnaksa.cpp) |
| 29 | SOLID · ISP | [Py](Roadmap/29%20-%20SOLID%20ISP/python/ecnaksa.py) · [C](Roadmap/29%20-%20SOLID%20ISP/c/ecnaksa.c) · [C++](Roadmap/29%20-%20SOLID%20ISP/c%2B%2B/ecnaksa.cpp) |
| 30 | SOLID · DIP | [Py](Roadmap/30%20-%20SOLID%20DIP/python/ecnaksa.py) · [C](Roadmap/30%20-%20SOLID%20DIP/c/ecnaksa.c) · [C++](Roadmap/30%20-%20SOLID%20DIP/c%2B%2B/ecnaksa.cpp) |

### Proyectos y retos temáticos (31 – 50)

| # | Proyecto | Soluciones |
|---|----------|------------|
| 31 | Simulador de Juegos Olímpicos | [Py](Roadmap/31%20-%20SIMULADOR%20JUEGOS%20OL%C3%8DMPICOS/python/ecnaksa.py) · [C](Roadmap/31%20-%20SIMULADOR%20JUEGOS%20OL%C3%8DMPICOS/c/ecnaksa.c) · [C++](Roadmap/31%20-%20SIMULADOR%20JUEGOS%20OL%C3%8DMPICOS/c%2B%2B/ecnaksa.cpp) |
| 32 | Batalla Deadpool y Wolverine | [Py](Roadmap/32%20-%20BATALLA%20DEADPOOL%20Y%20WOLVERINE/python/ecnaksa.py) · [C](Roadmap/32%20-%20BATALLA%20DEADPOOL%20Y%20WOLVERINE/c/ecnaksa.c) · [C++](Roadmap/32%20-%20BATALLA%20DEADPOOL%20Y%20WOLVERINE/c%2B%2B/ecnaksa.cpp) |
| 33 | Rescatando a Mickey (laberinto) | [Py](Roadmap/33%20-%20RESCATANDO%20A%20MICKEY/python/ecnaksa.py) · [C](Roadmap/33%20-%20RESCATANDO%20A%20MICKEY/c/ecnaksa.c) · [C++](Roadmap/33%20-%20RESCATANDO%20A%20MICKEY/c%2B%2B/ecnaksa.cpp) |
| 34 | Árbol genealógico (Casa del Dragón) | [Py](Roadmap/34%20-%20%C3%81RBOL%20GENEAL%C3%93GICO%20LA%20CASA%20DEL%20DRAG%C3%93N/python/ecnaksa.py) · [C](Roadmap/34%20-%20%C3%81RBOL%20GENEAL%C3%93GICO%20LA%20CASA%20DEL%20DRAG%C3%93N/c/ecnaksa.c) · [C++](Roadmap/34%20-%20%C3%81RBOL%20GENEAL%C3%93GICO%20LA%20CASA%20DEL%20DRAG%C3%93N/c%2B%2B/ecnaksa.cpp) |
| 35 | Repartiendo los Anillos de Poder | [Py](Roadmap/35%20-%20REPARTIENDO%20LOS%20ANILLOS%20DE%20PODER/python/ecnaksa.py) · [C](Roadmap/35%20-%20REPARTIENDO%20LOS%20ANILLOS%20DE%20PODER/c/ecnaksa.c) · [C++](Roadmap/35%20-%20REPARTIENDO%20LOS%20ANILLOS%20DE%20PODER/c%2B%2B/ecnaksa.cpp) |
| 36 | El Sombrero Seleccionador | [Py](Roadmap/36%20-%20EL%20SOMBRERO%20SELECCIONADOR/python/ecnaksa.py) · [C](Roadmap/36%20-%20EL%20SOMBRERO%20SELECCIONADOR/c/ecnaksa.c) · [C++](Roadmap/36%20-%20EL%20SOMBRERO%20SELECCIONADOR/c%2B%2B/ecnaksa.cpp) |
| 37 | Oasis vs Linkin Park (API Spotify) 🌐 | [Py](Roadmap/37%20-%20OASIS%20VS%20LINKIN%20PARK/python/ecnaksa.py) · [C](Roadmap/37%20-%20OASIS%20VS%20LINKIN%20PARK/c/ecnaksa.c) · [C++](Roadmap/37%20-%20OASIS%20VS%20LINKIN%20PARK/c%2B%2B/ecnaksa.cpp) |
| 38 | MoureDev Pro (sorteo CSV) | [Py](Roadmap/38%20-%20MOUREDEV%20PRO/python/ecnaksa.py) · [C](Roadmap/38%20-%20MOUREDEV%20PRO/c/ecnaksa.c) · [C++](Roadmap/38%20-%20MOUREDEV%20PRO/c%2B%2B/ecnaksa.cpp) |
| 39 | Batman Day (reto doble) | [Py](Roadmap/39%20-%20BATMAN%20DAY/python/ecnaksa.py) · [C](Roadmap/39%20-%20BATMAN%20DAY/c/ecnaksa.c) · [C++](Roadmap/39%20-%20BATMAN%20DAY/c%2B%2B/ecnaksa.cpp) |
| 40 | Fortnite Rubius Cup (API Twitch) 🌐 | [Py](Roadmap/40%20-%20FORTNITE%20RUBIUS%20CUP/python/ecnaksa.py) · [C](Roadmap/40%20-%20FORTNITE%20RUBIUS%20CUP/c/ecnaksa.c) · [C++](Roadmap/40%20-%20FORTNITE%20RUBIUS%20CUP/c%2B%2B/ecnaksa.cpp) |
| 41 | camiseta.rar (compresión) | [Py](Roadmap/41%20-%20CAMISETA%20RAR/python/ecnaksa.py) · [C](Roadmap/41%20-%20CAMISETA%20RAR/c/ecnaksa.c) · [C++](Roadmap/41%20-%20CAMISETA%20RAR/c%2B%2B/ecnaksa.cpp) |
| 42 | Torneo Dragon Ball | [Py](Roadmap/42%20-%20TORNEO%20DRAGON%20BALL/python/ecnaksa.py) · [C](Roadmap/42%20-%20TORNEO%20DRAGON%20BALL/c/ecnaksa.c) · [C++](Roadmap/42%20-%20TORNEO%20DRAGON%20BALL/c%2B%2B/ecnaksa.cpp) |
| 43 | Git / GitHub CLI | [Py](Roadmap/43%20-%20GIT%20GITHUB%20CLI/python/ecnaksa.py) · [C](Roadmap/43%20-%20GIT%20GITHUB%20CLI/c/ecnaksa.c) · [C++](Roadmap/43%20-%20GIT%20GITHUB%20CLI/c%2B%2B/ecnaksa.cpp) |
| 44 | Cuenta atrás (hilos + UTC) | [Py](Roadmap/44%20-%20CUENTA%20ATR%C3%81S%20MOUREDEV%20PRO/python/ecnaksa.py) · [C](Roadmap/44%20-%20CUENTA%20ATR%C3%81S%20MOUREDEV%20PRO/c/ecnaksa.c) · [C++](Roadmap/44%20-%20CUENTA%20ATR%C3%81S%20MOUREDEV%20PRO/c%2B%2B/ecnaksa.cpp) |
| 45 | GitHub Octoverse (API GitHub) 🌐 | [Py](Roadmap/45%20-%20GITHUB%20OCTOVERSE/python/ecnaksa.py) · [C](Roadmap/45%20-%20GITHUB%20OCTOVERSE/c/ecnaksa.c) · [C++](Roadmap/45%20-%20GITHUB%20OCTOVERSE/c%2B%2B/ecnaksa.cpp) |
| 46 | X vs Bluesky (red social) | [Py](Roadmap/46%20-%20X%20VS%20BLUESKY/python/ecnaksa.py) · [C](Roadmap/46%20-%20X%20VS%20BLUESKY/c/ecnaksa.c) · [C++](Roadmap/46%20-%20X%20VS%20BLUESKY/c%2B%2B/ecnaksa.cpp) |
| 47 | Calendario de adviento | [Py](Roadmap/47%20-%20CALENDARIO%20DE%20ADVIENTO/python/ecnaksa.py) · [C](Roadmap/47%20-%20CALENDARIO%20DE%20ADVIENTO/c/ecnaksa.c) · [C++](Roadmap/47%20-%20CALENDARIO%20DE%20ADVIENTO/c%2B%2B/ecnaksa.cpp) |
| 48 | Árbol de Navidad | [Py](Roadmap/48%20-%20%C3%81RBOL%20DE%20NAVIDAD/python/ecnaksa.py) · [C](Roadmap/48%20-%20%C3%81RBOL%20DE%20NAVIDAD/c/ecnaksa.c) · [C++](Roadmap/48%20-%20%C3%81RBOL%20DE%20NAVIDAD/c%2B%2B/ecnaksa.cpp) |
| 49 | El almacén de Papá Noel (Mastermind) | [Py](Roadmap/49%20-%20EL%20ALMAC%C3%89N%20DE%20PAP%C3%81%20NOEL/python/ecnaksa.py) · [C](Roadmap/49%20-%20EL%20ALMAC%C3%89N%20DE%20PAP%C3%81%20NOEL/c/ecnaksa.c) · [C++](Roadmap/49%20-%20EL%20ALMAC%C3%89N%20DE%20PAP%C3%81%20NOEL/c%2B%2B/ecnaksa.cpp) |
| 50 | Planificador de objetivos de Año Nuevo | [Py](Roadmap/50%20-%20PLANIFICADOR%20DE%20OBJETIVOS%20DE%20A%C3%91O%20NUEVO/python/ecnaksa.py) · [C](Roadmap/50%20-%20PLANIFICADOR%20DE%20OBJETIVOS%20DE%20A%C3%91O%20NUEVO/c/ecnaksa.c) · [C++](Roadmap/50%20-%20PLANIFICADOR%20DE%20OBJETIVOS%20DE%20A%C3%91O%20NUEVO/c%2B%2B/ecnaksa.cpp) |

> 🌐 = requiere conexión a internet o credenciales de API.

---

## 🙌 Créditos

- Enunciados y roadmap original: **[MoureDev](https://github.com/mouredev/roadmap-retos-programacion)**.
- Soluciones en Python, C y C++: **[@ecnaksa](https://github.com/ecnaksa)**.
