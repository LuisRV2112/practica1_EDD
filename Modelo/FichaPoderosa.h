#pragma once
/**
 * @file FichaPoderosa.h
 * @brief Ficha de accion: robo, bloqueo o giro segun su EfectoCarta.
 * Practica1EDD - Laboratorio EDD USAC CUNOC 2026
 */
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
