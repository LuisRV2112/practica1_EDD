#include "../../Modelo/FichaNumeral.h"
#include "../../Modelo/Pantalla.h"
#include "../../Modelo/ContextoPartida.h"

FichaNumeral::FichaNumeral(TonoCarta tono, int digito, CaraBaraja cara)
    : Ficha(tono, CategoriaCarta::NUMERAL, EfectoCarta::NINGUNO, cara),
      digito_(digito) {}

void FichaNumeral::renderizar() const { Pantalla::dibujarFicha(this); }

bool FichaNumeral::esValida(const Ficha* enMesa) const {
    if (!enMesa) return true;
    if (enMesa->getTono() == tono_) return true;
    if (enMesa->getCategoria() == CategoriaCarta::NUMERAL) {
        const FichaNumeral* otra = static_cast<const FichaNumeral*>(enMesa);
        if (otra->getDigito() == digito_) return true;
    }
    return enMesa->getCategoria() == CategoriaCarta::LIBRE;
}

void FichaNumeral::ejecutarEfecto(ContextoPartida& /*ctx*/) const {}

std::string FichaNumeral::obtenerSimbolo() const { return std::to_string(digito_); }
