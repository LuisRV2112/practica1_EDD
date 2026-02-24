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

FichaDevuraTono::FichaDevuraTono(TonoCarta tono, CaraBaraja cara)
    : Ficha(tono, CategoriaCarta::DEVORA_TONO, EfectoCarta::DEVORA_COLOR, cara) {}

void FichaDevuraTono::renderizar() const { Pantalla::dibujarFicha(this); }

bool FichaDevuraTono::esValida(const Ficha* enMesa) const {
    if (!enMesa) return true;
    return (enMesa->getTono()   == tono_) ||
           (enMesa->getEfecto() == EfectoCarta::DEVORA_COLOR);
}

void FichaDevuraTono::ejecutarEfecto(ContextoPartida& ctx) const {
    Contendiente* sig  = ctx.rueda->getSiguiente();
    ManoJugador*  mano = sig->getMano();
    int i = 0;
    while (i < mano->totalFichas()) {
        Ficha* f = mano->consultar(i);
        if (f && f->getTono() == ctx.tonoActivo) {
            ctx.baraja->descartarFicha(mano->extraer(i));
        } else { ++i; }
    }
}

std::string FichaDevuraTono::obtenerSimbolo() const { return "DVR"; }

FichaBarreraActiva::FichaBarreraActiva(TonoCarta tono, CaraBaraja cara)
    : Ficha(tono, CategoriaCarta::BARRERA_ACTIVA, EfectoCarta::ESCUDO_ACTIVO, cara) {}

void FichaBarreraActiva::renderizar() const { Pantalla::dibujarFicha(this); }

bool FichaBarreraActiva::esValida(const Ficha* enMesa) const {
    if (!enMesa) return true;
    return (enMesa->getTono()   == tono_) ||
           (enMesa->getEfecto() == EfectoCarta::ESCUDO_ACTIVO);
}

void FichaBarreraActiva::ejecutarEfecto(ContextoPartida& ctx) const {
    Contendiente* actual = ctx.rueda->getActual();
    if (actual) actual->activarBarrera(true);
}

std::string FichaBarreraActiva::obtenerSimbolo() const { return "cd"; }
