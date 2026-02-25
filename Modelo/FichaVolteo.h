#pragma once

#include "Ficha.h"

class FichaVolteo : public Ficha {
public:
    explicit FichaVolteo(TonoCarta tono, CaraBaraja cara = CaraBaraja::LUMINOSA);
    void        renderizar()                              const override;
    bool        esValida(const Ficha* fichaEnMesa)        const override;
    void        ejecutarEfecto(ContextoPartida& contexto) const override;
    std::string obtenerSimbolo()                          const override;
};
