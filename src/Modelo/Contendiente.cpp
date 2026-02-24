/**
 * @file Contendiente.cpp
 * @brief Gestiona la mano del jugador: recibir, lanzar y consultar fichas.
 * Practica1EDD - Laboratorio EDD USAC CUNOC 2026
 */
#include "../../Modelo/Contendiente.h"

Contendiente::Contendiente(const std::string& alias)
    : alias_(alias), fichas_(new ManoJugador()),
      unoGritado_(false), barreraActiva_(false), fuera_(false) {}

Contendiente::~Contendiente() { delete fichas_; }

// Agrega la ficha a la mano y resetea el flag UNO
void Contendiente::recibirFicha(Ficha* f) {
    if (f) fichas_->agregar(f);
    unoGritado_ = false;
}

Ficha* Contendiente::lanzarFicha(int idx)  { return fichas_->extraer(idx); }
Ficha* Contendiente::verFicha(int idx) const { return fichas_->consultar(idx); }
int    Contendiente::fichasEnMano() const  { return fichas_->totalFichas(); }
bool   Contendiente::sinFichas()    const  { return fichas_->sinFichas(); }
