
#include "../../Modelo/Contendiente.h"

Contendiente::Contendiente(const std::string& alias)
    : alias_(alias), fichas_(new ManoJugador()),
      unoGritado_(false), fuera_(false) {}

Contendiente::~Contendiente() { delete fichas_; }

void Contendiente::recibirFicha(Ficha* f) {
    if (f) fichas_->agregar(f);
    unoGritado_ = false;
}

Ficha* Contendiente::lanzarFicha(int idx)  { return fichas_->extraer(idx); }
Ficha* Contendiente::verFicha(int idx) const { return fichas_->consultar(idx); }
int    Contendiente::fichasEnMano() const  { return fichas_->totalFichas(); }
bool   Contendiente::sinFichas()    const  { return fichas_->sinFichas(); }
