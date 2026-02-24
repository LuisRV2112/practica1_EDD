
#include "../../Modelo/FichaEspecial.h"
#include "../../Modelo/Pantalla.h"
#include "../../Modelo/ContextoPartida.h"
#include "../../Modelo/RuedaTurnos.h"
#include "../../Modelo/Paleta.h"
#include <cstdlib>
#include <iostream>


FichaMostrarMano::FichaMostrarMano(TonoCarta tono, CaraBaraja cara)
    : Ficha(tono, CategoriaCarta::MOSTRAR_MANO, EfectoCarta::VER_MANO, cara) {}

void FichaMostrarMano::renderizar() const { Pantalla::dibujarFicha(this); }

// Valida igual que la carta sea lo mismo
bool FichaMostrarMano::esValida(const Ficha* enMesa) const {
    if (!enMesa) return true;
    return (enMesa->getTono()      == tono_)  ||
           (enMesa->getEfecto()    == EfectoCarta::VER_MANO) ||
           (enMesa->getCategoria() == CategoriaCarta::LIBRE);
}


void FichaMostrarMano::ejecutarEfecto(ContextoPartida& ctx) const {
    ctx.pendienteMostrarMano = true;
}

std::string FichaMostrarMano::obtenerSimbolo() const { return "SPY"; }



// Carta IntercambiarCarta
FichaIntercambiarCarta::FichaIntercambiarCarta(TonoCarta tono, CaraBaraja cara)
    : Ficha(tono, CategoriaCarta::INTERCAMBIAR_CARTA, EfectoCarta::ROBAR_CARTA, cara) {}

void FichaIntercambiarCarta::renderizar() const { Pantalla::dibujarFicha(this); }

bool FichaIntercambiarCarta::esValida(const Ficha* enMesa) const {
    if (!enMesa) return true;
    return (enMesa->getTono()      == tono_)  ||
           (enMesa->getEfecto()    == EfectoCarta::ROBAR_CARTA) ||
           (enMesa->getCategoria() == CategoriaCarta::LIBRE);
}

void FichaIntercambiarCarta::ejecutarEfecto(ContextoPartida& ctx) const {
    ctx.pendienteIntercambio = true;
}

std::string FichaIntercambiarCarta::obtenerSimbolo() const { return "SWP"; }
