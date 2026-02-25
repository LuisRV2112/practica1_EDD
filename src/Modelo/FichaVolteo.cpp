#include "../../Modelo/FichaVolteo.h"
#include "../../Modelo/Pantalla.h"
#include "../../Modelo/ContextoPartida.h"
#include "../../Modelo/RuedaTurnos.h"
#include "../../Modelo/Baraja.h"

FichaVolteo::FichaVolteo(TonoCarta tono, CaraBaraja cara)
    : Ficha(tono, CategoriaCarta::VOLTEO, EfectoCarta::LANZAR_VOLTEO, cara) {}

void FichaVolteo::renderizar() const { Pantalla::dibujarFicha(this); }

bool FichaVolteo::esValida(const Ficha* enMesa) const {
    if (!enMesa) return true;
    return (enMesa->getTono()   == tono_) ||
           (enMesa->getEfecto() == EfectoCarta::LANZAR_VOLTEO) ||
           (enMesa->getCategoria() == CategoriaCarta::LIBRE);
}

// Invierte la cara activa de lsa cartas
void FichaVolteo::ejecutarEfecto(ContextoPartida& ctx) const {
    ctx.caraActiva = (ctx.caraActiva == CaraBaraja::LUMINOSA)
                     ? CaraBaraja::SOMBRIA : CaraBaraja::LUMINOSA;
    Pantalla::alertaVolteo(ctx.caraActiva);
}

std::string FichaVolteo::obtenerSimbolo() const { return "VLT"; }
