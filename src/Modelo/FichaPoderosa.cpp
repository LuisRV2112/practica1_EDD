/**
 * @file FichaPoderosa.cpp
 * @brief Fichas de accion: aplica robo, bloqueo o inversion segun su efecto.
 * Practica1EDD - Laboratorio EDD USAC CUNOC 2026
 */
#include "../../Modelo/FichaPoderosa.h"
#include "../../Modelo/Pantalla.h"
#include "../../Modelo/ContextoPartida.h"
#include "../../Modelo/RuedaTurnos.h"
#include "../../Modelo/Baraja.h"

FichaPoderosa::FichaPoderosa(TonoCarta tono, EfectoCarta efecto, CaraBaraja cara)
    : Ficha(tono, CategoriaCarta::PODEROSA, efecto, cara) {}

void FichaPoderosa::renderizar() const { Pantalla::dibujarFicha(this); }

// Valida si coincide tono, efecto o si la carta en mesa es libre
bool FichaPoderosa::esValida(const Ficha* enMesa) const {
    if (!enMesa) return true;
    return (enMesa->getTono()      == tono_)   ||
           (enMesa->getEfecto()    == efecto_)  ||
           (enMesa->getCategoria() == CategoriaCarta::LIBRE);
}

void FichaPoderosa::ejecutarEfecto(ContextoPartida& ctx) const {
    Contendiente* sig = ctx.rueda->getSiguiente();
    switch (efecto_) {
        case EfectoCarta::ROBO_DOS:
            if (ctx.config.apilar) ctx.acumRobo += 2;
            else { for (int i=0;i<2;++i) sig->recibirFicha(ctx.baraja->tomarFicha()); ctx.rueda->omitirSiguiente(); }
            break;
        case EfectoCarta::ROBO_UNO:
            sig->recibirFicha(ctx.baraja->tomarFicha());
            ctx.rueda->omitirSiguiente();
            break;
        case EfectoCarta::ROBO_TRES:
            if (ctx.config.apilar) ctx.acumRobo += 3;
            else { for (int i=0;i<3;++i) sig->recibirFicha(ctx.baraja->tomarFicha()); ctx.rueda->omitirSiguiente(); }
            break;
        case EfectoCarta::ROBO_SEIS:
            if (ctx.config.apilar) ctx.acumRobo += 6;
            else { for (int i=0;i<6;++i) sig->recibirFicha(ctx.baraja->tomarFicha()); ctx.rueda->omitirSiguiente(); }
            break;
        case EfectoCarta::BLOQUEO:
            ctx.rueda->omitirSiguiente();
            break;
        case EfectoCarta::BLOQUEO_TOTAL:
            ctx.turnoRepetido = true;
            break;
        case EfectoCarta::GIRO:
            ctx.rueda->invertirSentido();
            ctx.giroActivo = !ctx.giroActivo;
            if (ctx.rueda->totalJugadores() == 2) ctx.rueda->omitirSiguiente();
            break;
        default: break;
    }
}

std::string FichaPoderosa::obtenerSimbolo() const {
    switch (efecto_) {
        case EfectoCarta::ROBO_DOS:      return "+2";
        case EfectoCarta::ROBO_UNO:      return "+1";
        case EfectoCarta::ROBO_TRES:     return "+3";
        case EfectoCarta::ROBO_SEIS:     return "+6";
        case EfectoCarta::BLOQUEO:       return "BLQ";
        case EfectoCarta::BLOQUEO_TOTAL: return "BLT";
        case EfectoCarta::GIRO:          return "GIR";
        default:                         return "?";
    }
}
