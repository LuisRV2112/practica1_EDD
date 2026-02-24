#pragma once

#include "Ficha.h"

class FichaLibre : public Ficha {
private:
    bool conRoboCuatro_;
public:
    explicit FichaLibre(bool conRoboCuatro, CaraBaraja cara = CaraBaraja::LUMINOSA);
    void        renderizar()                              const override;
    bool        esValida(const Ficha* fichaEnMesa)        const override;
    void        ejecutarEfecto(ContextoPartida& contexto) const override;
    std::string obtenerSimbolo()                          const override;
    bool        tieneRoboCuatro() const { return conRoboCuatro_; }
};
