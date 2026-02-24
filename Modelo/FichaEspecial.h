#pragma once
#include "Ficha.h"
//Las 2 cartas creadas por yo
class FichaMostrarMano : public Ficha {
public:
    explicit FichaMostrarMano(TonoCarta tono,
                               CaraBaraja cara = CaraBaraja::LUMINOSA);
    void        renderizar()                              const override;
    bool        esValida(const Ficha* fichaEnMesa)        const override;
    void        ejecutarEfecto(ContextoPartida& contexto) const override;
    std::string obtenerSimbolo()                          const override;
};

class FichaIntercambiarCarta : public Ficha {
public:
    explicit FichaIntercambiarCarta(TonoCarta tono,
                                    CaraBaraja cara = CaraBaraja::LUMINOSA);
    void        renderizar()                              const override;
    bool        esValida(const Ficha* fichaEnMesa)        const override;
    void        ejecutarEfecto(ContextoPartida& contexto) const override;
    std::string obtenerSimbolo()                          const override;
};
