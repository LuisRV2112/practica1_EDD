#pragma once
#include "ManoJugador.h"
#include <string>

class Contendiente {
private:
    std::string  alias_;
    ManoJugador* fichas_;
    bool         unoGritado_;
    bool         barreraActiva_;
    bool         fuera_;

public:
    explicit Contendiente(const std::string& alias);
    ~Contendiente();

    Contendiente(const Contendiente&)            = delete;
    Contendiente& operator=(const Contendiente&) = delete;

    void    recibirFicha(Ficha* f);
    Ficha*  lanzarFicha(int idx);
    Ficha*  verFicha(int idx)  const;
    int     fichasEnMano()     const;
    bool    sinFichas()        const;

    const std::string& getAlias()        const { return alias_; }
    ManoJugador*       getMano()         const { return fichas_; }
    bool               gritado()         const { return unoGritado_; }
    bool               tieneBarrera()    const { return barreraActiva_; }
    bool               eliminado()       const { return fuera_; }

    void marcarUNO(bool v)      { unoGritado_    = v; }
    void activarBarrera(bool v) { barreraActiva_ = v; }
    void retirar()              { fuera_         = true; }
};
