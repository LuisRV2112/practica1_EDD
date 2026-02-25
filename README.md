# Practica1EDD – UNO 2026

**Universidad San Carlos de Guatemala – Centro Universitario de Occidente**  
**Laboratorio de Estructura de Datos – Ingeniería en Ciencias y Sistemas**  
**Docente: Mario Moises Ramirez Tobar | Semestre 1 – 2026**

**Alumno: Luis Regalado | 202131920**

---

## Descripción

Implementación del juego de cartas **UNO** con variante **UNO Flip** en C++ para consola (CLI).  
El proyecto unifica dos bases de código y usa estructuras de datos implementadas desde cero, sin STL.

| Estructura | Clase | Uso |
|-----------|-------|-----|
| Pila | `Pila<T>` | Baraja de reserva y pila de descarte |
| Lista circular doble | `RuedaTurnos` | Orden de turnos |
| Lista enlazada simple | `ManoJugador` | Fichas en mano |
| Lista doble | `ListaDoble<T>` | TAD generico |
| Lista circular | `ListaCircular<T>` | TAD generico |

---

## Estructura del Proyecto

```
Practica1EDD/
├── bin/               <- Ejecutables generados
├── build/             <- Archivos de CMake
├── include/
│   └── TADs/
│       ├── Nodo.h
│       ├── Pila.h
│       ├── ListaDoble.h
│       └── ListaCircular.h
├── Modelo/
│   ├── Dominio.h         <- Enumeraciones globales
│   ├── Paleta.h          <- Codigos ANSI de color
│   ├── Ficha.h           <- Clase abstracta base
│   ├── FichaNumeral.h
│   ├── FichaPoderosa.h
│   ├── FichaLibre.h
│   ├── FichaVolteo.h   
│   ├── ManoJugador.h     <- Lista enlazada simple
│   ├── RuedaTurnos.h     <- Lista circular doble
│   ├── Contendiente.h
│   ├── Baraja.h
│   ├── ConfigPartida.h
│   ├── ContextoPartida.h
│   └── Pantalla.h
├── src/
│   ├── main.cpp
│   └── Modelo/
│       ├── Baraja.cpp
│       ├── ConfigPartida.cpp
│       ├── Contendiente.cpp
│       ├── FichaLibre.cpp
│       ├── FichaNumeral.cpp
│       ├── FichaPoderosa.cpp
│       ├── FichaVolteo.cpp
│       ├── Pantalla.cpp
│       └── RuedaTurnos.cpp
├── tests/
│   └── test_pila.cpp
├── docs/
│   ├── ManualUsuario.md
│   └── NivelComplejidad.md
├── CMakeLists.txt
├── CmakeScript.sh
├── Makefile
└── README.md
```

---

## Compilación y Ejecución

### Makefile (recomendado)

```bash
make          #  escribir en la terminar para compilar
make run      # compilar y ejecutar
make test     # pruebas unitarias
```

### Script CMake

```bash
chmod +x CmakeScript.sh
./CmakeScript.sh
./bin/Practica1EDD
```

### CLion 2025.3.3

1. Abrir la carpeta `Practica1EDD/` como proyecto en CLion
2. CLion detecta `CMakeLists.txt` automáticamente
3. Seleccionar target `Practica1EDD` y presionar **Run**

### g++ directo

```bash
g++ -std=c++20 -Wall \
    -I include -I include/TADs -I Modelo \
    src/main.cpp src/Modelo/Baraja.cpp src/Modelo/ConfigPartida.cpp \
    src/Modelo/Contendiente.cpp src/Modelo/FichaLibre.cpp \
    src/Modelo/FichaNumeral.cpp src/Modelo/FichaPoderosa.cpp \
    src/Modelo/FichaVolteo.cpp src/Modelo/Pantalla.cpp \
    src/Modelo/RuedaTurnos.cpp \
    -o bin/Practica1EDD

./bin/Practica1EDD
```

---

## Fichas Personalizadas

| Ficha              | Símbolo | Efecto                                                            |
|--------------------|---------|-------------------------------------------------------------------|
| **Ficha especial** | SWP     | El siguiente contendiente pierde todas sus fichas del tono activo |
| **Ficha especial** | SPY     | Puedes ver las cartas del otro jugador por 3 segundos             |

---

## Reglas Configurables

| Flag | Descripción |
|------|-------------|
| `apilar` | Acumulación de +2/+4 |
| `retarLibre` | Reto al +4 |
| `roboIlimitado` | Robar hasta poder jugar |
| `obligarUNO` | Gritar UNO al quedar con 1 ficha |
| `permitirObs` | Ganar con ficha Obsidiana |
| `modoFlip` | Activar cara sombría |

---

## Acciones en Partida

| Tecla | Acción |
|-------|--------|
| `0..N` | Lanzar ficha por índice |
| `T` | Tomar ficha de la reserva |
| `U` | Gritar UNO! |
| `V` | Ver mis fichas completas |
| `Q` | **Dejar el juego** (el jugador abandona; si queda 1, ese gana) |
