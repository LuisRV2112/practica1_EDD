#pragma once
/**
 * @file FichaNumeral.h
 * @brief Ficha con digito 0-9; valida por tono igual o digito igual.
 * Practica1EDD - Laboratorio EDD USAC CUNOC 2026
 */
#include "Ficha.h"

class FichaNumeral : public Ficha {
private:
    int digito_;
public:
    FichaNumeral(TonoCarta tono, int digito, CaraBaraja cara = CaraBaraja::LUMINOSA);
    void        renderizar()                              const override;
    bool        esValida(const Ficha* fichaEnMesa)        const override;
    void        ejecutarEfecto(ContextoPartida& contexto) const override;
    std::string obtenerSimbolo()                          const override;
    int         getDigito() const { return digito_; }
};
