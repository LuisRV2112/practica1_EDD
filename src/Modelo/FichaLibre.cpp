#include "../../Modelo/FichaLibre.h"
#include "../../Modelo/Pantalla.h"
#include "../../Modelo/ContextoPartida.h"
#include "../../Modelo/RuedaTurnos.h"
#include "../../Modelo/Baraja.h"

FichaLibre::FichaLibre(bool conRoboCuatro, CaraBaraja cara)
    : Ficha(TonoCarta::OBSIDIANA, CategoriaCarta::LIBRE,
            conRoboCuatro ? EfectoCarta::ROBO_CUATRO : EfectoCarta::ELEGIR_TONO,
            cara),
      conRoboCuatro_(conRoboCuatro) {}

void FichaLibre::renderizar() const { Pantalla::dibujarFicha(this); }

bool FichaLibre::esValida(const Ficha* /*enMesa*/) const { return true; }

void FichaLibre::ejecutarEfecto(ContextoPartida& ctx) const {
    if (!conRoboCuatro_) return;
    if (ctx.config.apilar) {
        ctx.acumRobo += 4;
    } else if (ctx.config.retarLibre) {
        ctx.esperaReto = true;
        ctx.fichasReto = 4;
    } else {
        Contendiente* sig = ctx.rueda->getSiguiente();
        for (int i = 0; i < 4; ++i) sig->recibirFicha(ctx.baraja->tomarFicha());
        ctx.rueda->omitirSiguiente();
    }
}

std::string FichaLibre::obtenerSimbolo() const {
    return conRoboCuatro_ ? "+4" : "ELG";
}
