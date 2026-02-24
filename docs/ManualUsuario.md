# Manual de Usuario – Practica1EDD / UNO Arena 2026

**Universidad San Carlos de Guatemala – CUNOC**  
**Laboratorio de Estructura de Datos 2026**

---

## 1. Introducción

**Practica1EDD** es una implementación del clásico juego de cartas **UNO** (con variante UNO Flip) para consola (CLI). El juego soporta entre 2 y 20 jugadores, configuración de reglas opcionales y el modo flip que activa una cara sombría de la baraja.

---

## 2. Requisitos

- Sistema operativo: Linux, macOS o Windows (con WSL/MinGW)
- Compilador: g++ con soporte C++20 o superior
- CMake 4.1 o superior (para usar CLion o el script CMake)

---

## 3. Instalación y Compilación

### 3.1 Con Makefile

```bash
# Desde la carpeta raíz del proyecto:
make          # Compila el ejecutable principal
make run      # Compila y ejecuta directamente
make test     # Compila y ejecuta las pruebas unitarias
make clean    # Elimina los ejecutables generados
```

### 3.2 Con CLion 2025.3.3

1. Abrir CLion → **File > Open** → seleccionar la carpeta `Practica1EDD/`
2. CLion detecta automáticamente el `CMakeLists.txt`
3. En la barra superior, seleccionar el target **Practica1EDD**
4. Presionar el botón **Run** (▶) o `Shift+F10`

### 3.3 Con el script CMake

```bash
chmod +x CmakeScript.sh
./CmakeScript.sh
./bin/Practica1EDD
```

---

## 4. Menú Principal

Al ejecutar el programa se muestra:

```
>> MENU PRINCIPAL <<

   ( 1 )  Iniciar Partida
   ( 2 )  Ajustar Configuración
   ( 3 )  Ver Demo de Fichas
   ( 4 )  Cargar Config desde Archivo
   ( 0 )  Salir del Arena
```

Ingresa el número de la opción y presiona **ENTER**.

---

## 5. Iniciar una Partida

1. Selecciona opción **1**
2. Ingresa el número de contendientes (mínimo 2, máximo 20)
3. Para cada jugador, escribe su **alias** y presiona ENTER
4. El juego reparte 7 fichas a cada jugador y coloca la primera ficha en la mesa

---

## 6. Acciones Durante tu Turno

Cuando sea tu turno verás la arena con:
- La reserva (fichas boca abajo)
- La ficha actual en mesa
- La lista de contendientes con su cantidad de fichas

### Opciones disponibles:

| Tecla | Acción |
|-------|--------|
| `0` a `N` | Lanzar la ficha con ese índice (ver tu mano con `V` primero) |
| `T` | Tomar una ficha de la reserva |
| `U` | Gritar **UNO!** cuando te quede solo 1 ficha |
| `V` | Ver todas tus fichas con sus índices |
| `Q` | **Dejar el juego** — abandonas la partida inmediatamente |

> **Nota:** Si usas `Q` y solo queda 1 jugador más, ese jugador gana automáticamente.  
> Si quedan más de 2 jugadores, la partida continúa sin ti.

---

## 7. Tipos de Fichas

| Símbolo | Nombre | Efecto |
|---------|--------|--------|
| `0-9` | Numeral | Sin efecto |
| `BLQ` | Bloqueo | Salta el turno del siguiente jugador |
| `GIR` | Giro | Invierte el sentido de los turnos |
| `+2` | Robo Dos | El siguiente jugador roba 2 fichas y pierde su turno |
| `+4` | Robo Cuatro | El siguiente jugador roba 4 fichas; debes elegir el tono |
| `ELG` | Comodín | Elige el tono activo libremente |
| `VLT` | Volteo | Cambia entre cara Luminosa y cara Sombría |
| `DVR` | DevuraTono | El siguiente jugador pierde todas sus fichas del tono activo |
| `BRR` | Barrera | Activa un escudo que anula el próximo robo acumulado |

### Cara Sombría (Modo Flip)

En modo Flip los colores cambian: Carmesí → Fucsia, Esmeralda → Aguamarina, Zafiro → Coral, Dorado → Índigo.

---

## 8. Configuración de Reglas

Desde el menú principal → **opción 2**:

| Regla | Descripción |
|-------|-------------|
| Apilar robos | Permite acumular penalizaciones +2/+4 antes de robar |
| Reto ficha libre | Permite retar al jugador que lanzó un +4 |
| Robo ilimitado | El jugador sigue robando hasta encontrar una ficha válida |
| Grito UNO | El jugador debe gritar UNO al quedar con 1 ficha |
| Ganar con Obsidiana | Permite ganar lanzando una ficha de color Obsidiana |
| Modo Flip | Activa la cara sombría de la baraja |

La configuración puede guardarse en `config_arena.txt` y cargarse después.

---

## 9. Fin de la Partida

La partida termina cuando:
- Un jugador lanza su última ficha → ese jugador es el **campeón**
- Un jugador usa `Q` y solo queda 1 contrincante → ese contrincante gana automáticamente

---

## 10. Pruebas Unitarias

Para verificar que las estructuras de datos funcionan correctamente:

```bash
make test
# o directamente:
./bin/test_pila
```

Las pruebas cubren: `Pila<T>`, `RuedaTurnos` y `Baraja`.
