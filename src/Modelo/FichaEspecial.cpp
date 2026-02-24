/**
 * @file FichaEspecial.cpp
 * @brief Implementacion de FichaMostrarMano y FichaIntercambiarCarta.
 * Practica1EDD - Laboratorio EDD USAC CUNOC 2026
 */
#include "../../Modelo/FichaEspecial.h"
#include "../../Modelo/Pantalla.h"
#include "../../Modelo/ContextoPartida.h"
#include "../../Modelo/RuedaTurnos.h"
#include "../../Modelo/Paleta.h"
#include <cstdlib>
#include <iostream>

// ═══════════════════════════════════════════════════════════════════════════
// FichaMostrarMano
// ═══════════════════════════════════════════════════════════════════════════

FichaMostrarMano::FichaMostrarMano(TonoCarta tono, CaraBaraja cara)
    : Ficha(tono, CategoriaCarta::MOSTRAR_MANO, EfectoCarta::VER_MANO, cara) {}

void FichaMostrarMano::renderizar() const { Pantalla::dibujarFicha(this); }

// Valida igual que una ficha poderosa: mismo tono, mismo efecto o libre sobre mesa
bool FichaMostrarMano::esValida(const Ficha* enMesa) const {
    if (!enMesa) return true;
    return (enMesa->getTono()      == tono_)  ||
           (enMesa->getEfecto()    == EfectoCarta::VER_MANO) ||
           (enMesa->getCategoria() == CategoriaCarta::LIBRE);
}

// Activa el flag para que main.cpp resuelva la interaccion interactiva
void FichaMostrarMano::ejecutarEfecto(ContextoPartida& ctx) const {
    ctx.pendienteMostrarMano = true;
}

std::string FichaMostrarMano::obtenerSimbolo() const { return "SPY"; }


// ═══════════════════════════════════════════════════════════════════════════
// FichaIntercambiarCarta
// ═══════════════════════════════════════════════════════════════════════════

FichaIntercambiarCarta::FichaIntercambiarCarta(TonoCarta tono, CaraBaraja cara)
    : Ficha(tono, CategoriaCarta::INTERCAMBIAR_CARTA, EfectoCarta::ROBAR_CARTA, cara) {}

void FichaIntercambiarCarta::renderizar() const { Pantalla::dibujarFicha(this); }

// Valida igual que una ficha poderosa
bool FichaIntercambiarCarta::esValida(const Ficha* enMesa) const {
    if (!enMesa) return true;
    return (enMesa->getTono()      == tono_)  ||
           (enMesa->getEfecto()    == EfectoCarta::ROBAR_CARTA) ||
           (enMesa->getCategoria() == CategoriaCarta::LIBRE);
}

// Activa el flag para que main.cpp resuelva la interaccion interactiva
void FichaIntercambiarCarta::ejecutarEfecto(ContextoPartida& ctx) const {
    ctx.pendienteIntercambio = true;
}

std::string FichaIntercambiarCarta::obtenerSimbolo() const { return "SWP"; }
