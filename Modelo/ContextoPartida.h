#pragma once
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

    bool          pendienteMostrarMano    = false;
    bool          pendienteIntercambio    = false;

    ConfigPartida config;
};
