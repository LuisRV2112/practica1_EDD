#pragma once
/**
 * @file ContextoPartida.h
 * @brief Estado mutable de la partida; se pasa por referencia a ejecutarEfecto().
 * Practica1EDD - Laboratorio EDD USAC CUNOC 2026
 */
#include "Dominio.h"
#include "ConfigPartida.h"

class RuedaTurnos;
class Baraja;

struct ContextoPartida {
    RuedaTurnos*  rueda           = nullptr;
    Baraja*       baraja          = nullptr;

    TonoCarta     tonoActivo      = TonoCarta::CARMESI;
    CaraBaraja    caraActiva      = CaraBaraja::LUMINOSA;
    int           acumRobo        = 0;
    bool          giroActivo      = true;
    bool          turnoRepetido   = false;
    bool          partidaFin      = false;
    std::string   campeon         = "";

    bool          esperaReto      = false;
    int           fichasReto      = 0;

    int           numeroTurno     = 0;

    // Flags para cartas personalizadas — se activan en ejecutarEfecto()
    // y se consumen en ejecutarTurno() en main.cpp
    bool          pendienteMostrarMano    = false; // FichaMostrarMano fue jugada
    bool          pendienteIntercambio    = false; // FichaIntercambiarCarta fue jugada

    ConfigPartida config;
};
