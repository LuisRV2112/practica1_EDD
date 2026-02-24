# Nivel de Complejidad – Practica1EDD 2026

**Universidad San Carlos de Guatemala – CUNOC**  
**Laboratorio de Estructura de Datos 2026**

---

## 1. TAD Pila (`Pila<T>`)

| Operación | Complejidad Temporal | Complejidad Espacial |
|-----------|---------------------|---------------------|
| `apilar(valor)` | O(1) | O(1) por nodo |
| `sacar()` | O(1) | O(1) |
| `verTope()` | O(1) | O(1) |
| `estaVacia()` | O(1) | O(1) |
| `totalElementos()` | O(1) | O(1) |
| `volcarEnArreglo(arr)` | O(n) | O(n) arreglo auxiliar |
| `cargarDesdeArreglo(arr, n)` | O(n) | O(n) |
| **Destructor** | O(n) | O(1) |

**Espacio total:** O(n) donde n = número de elementos apilados.

---

## 2. TAD Lista Doble (`ListaDoble<T>`)

| Operación | Complejidad Temporal | Complejidad Espacial |
|-----------|---------------------|---------------------|
| `insertar(dato)` | O(n) — recorre hasta el final | O(1) por nodo |
| `eliminarEn(indice)` | O(n) — recorre hasta índice | O(1) |
| `getCabeza()` | O(1) | O(1) |
| `getTamano()` | O(1) | O(1) |
| **Destructor** | O(n) | O(1) |

---

## 3. TAD Lista Circular (`ListaCircular<T>`)

| Operación | Complejidad Temporal | Complejidad Espacial |
|-----------|---------------------|---------------------|
| `insertar(dato)` | O(1) — inserta antes del actual | O(1) por nodo |
| `avanzar()` | O(1) | O(1) |
| `saltar()` | O(1) — dos avanzar() | O(1) |
| `cambiarSentido()` | O(1) | O(1) |
| `getActual()` | O(1) | O(1) |

---

## 4. Lista Enlazada Simple (`ManoJugador`)

| Operación | Complejidad Temporal | Complejidad Espacial |
|-----------|---------------------|---------------------|
| `agregar(ficha)` | O(n) — recorre hasta el final | O(1) |
| `extraer(idx)` | O(n) | O(1) |
| `consultar(idx)` | O(n) | O(1) |
| `totalFichas()` | O(1) | O(1) |
| `vaciar()` | O(n) | O(1) |

---

## 5. Lista Circular Doble (`RuedaTurnos`)

| Operación | Complejidad Temporal | Complejidad Espacial |
|-----------|---------------------|---------------------|
| `inscribir(c)` | O(1) — inserta antes del primero | O(1) |
| `avanzar()` | O(1) | O(1) |
| `omitirSiguiente()` | O(1) — dos avanzar() | O(1) |
| `invertirSentido()` | O(1) | O(1) |
| `retirarActual()` | O(1) | O(1) |
| `getActual()` | O(1) | O(1) |
| `getSiguiente()` | O(1) | O(1) |
| `limpiar()` | O(n) | O(1) |

---

## 6. Baraja

| Operación | Complejidad Temporal | Complejidad Espacial |
|-----------|---------------------|---------------------|
| `armarCaraLuminosa()` | O(k) k=fichas por cara (~108) | O(k) |
| `armarCaraSombria()` | O(k) | O(k) |
| `preparar(n, cfg)` | O(m·k) m=mazos, k=fichas/mazo | O(m·k) |
| `mezclar()` — Fisher-Yates | O(n) | O(n) arreglo auxiliar |
| `tomarFicha()` | O(1) amortizado | O(1) |
| `descartarFicha(f)` | O(1) | O(1) |
| `fichaEnMesa()` | O(1) | O(1) |
| `reciclarUsadas()` | O(n) | O(n) — Fisher-Yates interno |
| **Destructor** | O(n) | O(1) |

---

## 7. Jerarquía de Fichas

Todas las fichas heredan de `Ficha` (clase abstracta). Los métodos virtuales tienen despacho O(1) gracias a la vtable. Los efectos específicos:

| Ficha | `ejecutarEfecto` | Complejidad |
|-------|-----------------|-------------|
| FichaNumeral | Sin efecto | O(1) |
| FichaPoderosa | Roba/bloquea/invierte | O(k) donde k = fichas robadas |
| FichaLibre | Roba cuatro / elige tono | O(k) |
| FichaVolteo | Cambia cara activa | O(1) |
| FichaDevuraTono | Elimina fichas del tono | O(m) m = fichas del tono en mano del rival |
| FichaBarreraActiva | Activa escudo | O(1) |

---

## 8. Bucle Principal del Juego

| Operación | Complejidad |
|-----------|-------------|
| `ejecutarTurno()` — construir lista de arena | O(J) J = jugadores activos |
| `mostrarArena()` | O(J) |
| `primerFichaValida()` | O(m) m = fichas en mano |
| Lanzar ficha | O(m) — extraer de la lista |
| Verificar campeón | O(1) |
| **Un turno completo** | O(J + m) |
| **Partida completa** | O(T·(J + m)) T = turnos totales |

---

## 9. Resumen General

| Componente | Tiempo | Espacio |
|-----------|--------|---------|
| Pila<T> | O(1) por op | O(n) |
| ListaDoble<T> | O(n) insertar/eliminar | O(n) |
| ListaCircular<T> | O(1) por op | O(n) |
| ManoJugador | O(n) agregar/extraer | O(n) |
| RuedaTurnos | O(1) por op | O(J) |
| Baraja (mezcla) | O(n) Fisher-Yates | O(n) |
| Baraja (op básica) | O(1) amortizado | — |
| Turno de juego | O(J + m) | O(J) |
