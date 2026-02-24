#pragma once
/**
 * @file FichaEspecial.h
 * @brief Dos cartas personalizadas del equipo:
 *   - FichaMostrarMano : fuerza a un rival a revelar su mano por 3 segundos.
 *   - FichaIntercambiarCarta : roba una carta (aleatoria o elegida) de un rival.
 * Practica1EDD - Laboratorio EDD USAC CUNOC 2026
 */
#include "Ficha.h"

// ── FichaMostrarMano ──────────────────────────────────────────────────────────
// Con 2 jugadores: el unico rival muestra su mano automaticamente.
// Con 3+ jugadores: quien la juega elige el rival objetivo.
// La mano se muestra durante 3 segundos y luego la pantalla se limpia.
class FichaMostrarMano : public Ficha {
public:
    explicit FichaMostrarMano(TonoCarta tono,
                               CaraBaraja cara = CaraBaraja::LUMINOSA);
    void        renderizar()                              const override;
    bool        esValida(const Ficha* fichaEnMesa)        const override;
    void        ejecutarEfecto(ContextoPartida& contexto) const override;
    std::string obtenerSimbolo()                          const override;
};

// ── FichaIntercambiarCarta ────────────────────────────────────────────────────
// Con 2 jugadores: el rival cede una carta (aleatoria o a su eleccion).
// Con 3+ jugadores: quien la juega elige el rival y luego este cede la carta.
class FichaIntercambiarCarta : public Ficha {
public:
    explicit FichaIntercambiarCarta(TonoCarta tono,
                                    CaraBaraja cara = CaraBaraja::LUMINOSA);
    void        renderizar()                              const override;
    bool        esValida(const Ficha* fichaEnMesa)        const override;
    void        ejecutarEfecto(ContextoPartida& contexto) const override;
    std::string obtenerSimbolo()                          const override;
};
