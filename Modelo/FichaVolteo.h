#pragma once
/**
 * @file FichaVolteo.h
 * @brief VLT cambia cara; DVR devora fichas del rival; BRR activa escudo.
 * Practica1EDD - Laboratorio EDD USAC CUNOC 2026
 */
#include "Ficha.h"

class FichaVolteo : public Ficha {
public:
    explicit FichaVolteo(TonoCarta tono, CaraBaraja cara = CaraBaraja::LUMINOSA);
    void        renderizar()                              const override;
    bool        esValida(const Ficha* fichaEnMesa)        const override;
    void        ejecutarEfecto(ContextoPartida& contexto) const override;
    std::string obtenerSimbolo()                          const override;
};

class FichaDevuraTono : public Ficha {
public:
    explicit FichaDevuraTono(TonoCarta tono, CaraBaraja cara = CaraBaraja::LUMINOSA);
    void        renderizar()                              const override;
    bool        esValida(const Ficha* fichaEnMesa)        const override;
    void        ejecutarEfecto(ContextoPartida& contexto) const override;
    std::string obtenerSimbolo()                          const override;
};

class FichaBarreraActiva : public Ficha {
public:
    explicit FichaBarreraActiva(TonoCarta tono, CaraBaraja cara = CaraBaraja::LUMINOSA);
    void        renderizar()                              const override;
    bool        esValida(const Ficha* fichaEnMesa)        const override;
    void        ejecutarEfecto(ContextoPartida& contexto) const override;
    std::string obtenerSimbolo()                          const override;
};
