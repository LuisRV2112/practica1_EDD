#pragma once

#include "Ficha.h"

class FichaPoderosa : public Ficha {
public:
    FichaPoderosa(TonoCarta tono, EfectoCarta efecto,
                  CaraBaraja cara = CaraBaraja::LUMINOSA);
    void        renderizar()                              const override;
    bool        esValida(const Ficha* fichaEnMesa)        const override;
    void        ejecutarEfecto(ContextoPartida& contexto) const override;
    std::string obtenerSimbolo()                          const override;
};
