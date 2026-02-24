#include "../include/TADs/Pila.h"
#include "../Modelo/RuedaTurnos.h"
#include "../Modelo/Baraja.h"
#include "../Modelo/ConfigPartida.h"
#include "../Modelo/Contendiente.h"
#include <iostream>
#include <cassert>
#include <string>

#define APRUEBA "\033[32m[OK]\033[0m "
#define FALLA   "\033[31m[FALLA]\033[0m "
#define INFO    "\033[33m[>>]\033[0m "

static int ok_count   = 0;
static int fail_count = 0;

#define VERIFICAR(cond, msg) \
    if (!(cond)) { \
        std::cerr << FALLA << msg << "  (linea " << __LINE__ << ")\n"; \
        ++fail_count; \
    } else { \
        std::cout << APRUEBA << msg << "\n"; \
        ++ok_count; \
    }

// ── Pila<int> ─────────────────────────────────────────────────────────────────
void test_pila_apilar_sacar() {
    std::cout << INFO << "--- Pila<int>: apilar / sacar / verTope ---\n";
    Pila<int> p;
    VERIFICAR(p.estaVacia(),         "Pila vacia al crear");
    VERIFICAR(p.totalElementos()==0, "Total 0 al inicio");
    p.apilar(5); p.apilar(10); p.apilar(15);
    VERIFICAR(p.totalElementos()==3, "Total 3 tras apilar 3");
    VERIFICAR(p.verTope()==15,       "Tope == 15");
    p.sacar();
    VERIFICAR(p.verTope()==10,       "Tope == 10 tras sacar");
    VERIFICAR(p.totalElementos()==2, "Total 2 tras sacar");
    p.sacar(); p.sacar();
    VERIFICAR(p.estaVacia(),         "Vacia tras vaciar");
}

void test_pila_excepcion() {
    std::cout << INFO << "--- Pila<int>: excepcion en vacia ---\n";
    Pila<int> p;
    bool lanzada = false;
    try { p.sacar(); } catch (const std::underflow_error&) { lanzada = true; }
    VERIFICAR(lanzada, "sacar() en vacia lanza underflow_error");

    bool lanzada2 = false;
    try { p.verTope(); } catch (const std::underflow_error&) { lanzada2 = true; }
    VERIFICAR(lanzada2, "verTope() en vacia lanza underflow_error");
}

void test_pila_volcar_cargar() {
    std::cout << INFO << "--- Pila<int>: volcarEnArreglo / cargarDesdeArreglo ---\n";
    Pila<int> p;
    for (int i = 0; i < 5; ++i) p.apilar(i * 3); // 0,3,6,9,12
    int arr[5];
    p.volcarEnArreglo(arr);
    VERIFICAR(arr[0]==12, "arr[0]==12 (tope)");
    VERIFICAR(arr[4]==0,  "arr[4]==0 (fondo)");
    p.cargarDesdeArreglo(arr, 5);
    VERIFICAR(p.totalElementos()==5, "cargarDesdeArreglo restaura total");
}

//  Rueda de  Turnos
void test_rueda_inscribir_avanzar() {
    std::cout << INFO << "--- RuedaTurnos: inscribir / avanzar ---\n";
    Contendiente a("Alfa"), b("Beta"), c("Gamma");
    RuedaTurnos  rueda;
    VERIFICAR(rueda.vacia(),             "Rueda vacia al inicio");
    rueda.inscribir(&a); rueda.inscribir(&b); rueda.inscribir(&c);
    VERIFICAR(rueda.totalJugadores()==3, "Total 3 tras inscribir");
    VERIFICAR(rueda.getActual()==&a,     "Actual es Alfa");
    rueda.avanzar();
    VERIFICAR(rueda.getActual()==&b,     "Siguiente es Beta");
    rueda.avanzar();
    VERIFICAR(rueda.getActual()==&c,     "Siguiente es Gamma");
    rueda.avanzar();
    VERIFICAR(rueda.getActual()==&a,     "Circular: vuelve a Alfa");
}

void test_rueda_invertir() {
    std::cout << INFO << "--- RuedaTurnos: invertir sentido ---\n";
    Contendiente a("A"), b("B"), c("C");
    RuedaTurnos rueda;
    rueda.inscribir(&a); rueda.inscribir(&b); rueda.inscribir(&c);
    rueda.invertirSentido();
    rueda.avanzar();
    VERIFICAR(rueda.getActual()==&c, "Invertido: A -> C");
    rueda.avanzar();
    VERIFICAR(rueda.getActual()==&b, "Invertido: C -> B");
}

void test_rueda_omitir() {
    std::cout << INFO << "--- RuedaTurnos: omitirSiguiente ---\n";
    Contendiente a("A"), b("B"), c("C"), d("D");
    RuedaTurnos rueda;
    rueda.inscribir(&a); rueda.inscribir(&b);
    rueda.inscribir(&c); rueda.inscribir(&d);
    rueda.omitirSiguiente(); // salta B -> queda en C
    VERIFICAR(rueda.getActual()==&c, "Omitir: A salta B, queda en C");
}

void test_rueda_retirar() {
    std::cout << INFO << "--- RuedaTurnos: retirarActual ---\n";
    Contendiente a("A"), b("B"), c("C");
    RuedaTurnos rueda;
    rueda.inscribir(&a); rueda.inscribir(&b); rueda.inscribir(&c);
    rueda.avanzar();           // actual = B
    rueda.retirarActual();     // elimina B, actual = C
    VERIFICAR(rueda.totalJugadores()==2, "Total 2 tras retirar");
    VERIFICAR(rueda.getActual()==&c,     "Actual es C tras eliminar B");
    rueda.avanzar();
    VERIFICAR(rueda.getActual()==&a,     "Circular: C -> A");
}

// Baraja
void test_baraja_conteo() {
    std::cout << INFO << "--- Baraja: conteo y escalamiento ---\n";
    ConfigPartida cfg;
    cfg.modoFlip = false;
    Baraja b1;
    b1.preparar(1, cfg);
    int base = b1.fichasDisponibles();
    VERIFICAR(base > 100, "1 deck tiene > 100 fichas");
    std::cout << "    Fichas con 1 deck: " << base << "\n";

    Baraja b2;
    b2.preparar(7, cfg); // 2 decks
    VERIFICAR(b2.fichasDisponibles() == base * 2,
              "7 contendientes = 2 decks");
    std::cout << "    Fichas con 2 decks: " << b2.fichasDisponibles() << "\n";
}

void test_baraja_tomar_descartar() {
    std::cout << INFO << "--- Baraja: tomarFicha / descartarFicha ---\n";
    ConfigPartida cfg;
    Baraja b;
    b.preparar(2, cfg);
    int antes = b.fichasDisponibles();
    Ficha* f = b.tomarFicha();
    VERIFICAR(f != nullptr,                       "tomarFicha() != null");
    VERIFICAR(b.fichasDisponibles() == antes - 1, "Disponibles bajan en 1");
    b.descartarFicha(f);
    VERIFICAR(b.fichasDescartadas() == 1,         "Descartadas == 1");
    VERIFICAR(b.fichaEnMesa() == f,               "fichaEnMesa() correcto");
}

void test_baraja_mezcla_conteo() {
    std::cout << INFO << "--- Baraja: mezclar mantiene conteo ---\n";
    ConfigPartida cfg;
    Baraja b;
    b.preparar(3, cfg);
    int antes = b.fichasDisponibles();
    b.mezclar();
    VERIFICAR(b.fichasDisponibles() == antes,
              "mezclar() no altera cantidad de fichas");
}

int main() {
    std::cout << "\033[1m\033[36m";
    std::cout << "+==========================================+\n";
    std::cout << "|  Pruebas Unitaria para la practica       |\n";
    std::cout << "+==========================================+\n\033[0m\n";

    test_pila_apilar_sacar();
    test_pila_excepcion();
    test_pila_volcar_cargar();
    test_rueda_inscribir_avanzar();
    test_rueda_invertir();
    test_rueda_omitir();
    test_rueda_retirar();
    test_baraja_conteo();
    test_baraja_tomar_descartar();
    test_baraja_mezcla_conteo();

    std::cout << "\n\033[1m";
    std::cout << "==========================================\n";
    std::cout << "  Resultados: " << "\033[32m" << ok_count
              << " OK\033[0m\033[1m  "
              << "\033[31m" << fail_count << " FALLA\033[0m\n";
    std::cout << "==========================================\n\033[0m\n";
    return fail_count > 0 ? 1 : 0;
}
