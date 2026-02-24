#pragma once
#include "../include/TADs/Pila.h"
#include "Ficha.h"
#include "ConfigPartida.h"

class Baraja {
private:
    Pila<Ficha*> pilaReserva_;
    Pila<Ficha*> pilaUsadas_;

    void armarCaraLuminosa();
    void armarCaraSombria();

public:
    Baraja()  = default;
    ~Baraja();

    Baraja(const Baraja&)            = delete;
    Baraja& operator=(const Baraja&) = delete;

    void   preparar(int nContendientes, const ConfigPartida& cfg);
    Ficha* tomarFicha();
    void   descartarFicha(Ficha* f);
    Ficha* fichaEnMesa()  const;
    void   reciclarUsadas();
    void   mezclar();

    int  fichasDisponibles() const { return pilaReserva_.totalElementos(); }
    int  fichasDescartadas() const { return pilaUsadas_.totalElementos(); }
    bool reservaVacia()      const { return pilaReserva_.estaVacia(); }

    Pila<Ficha*>& getPilaUsadas() { return pilaUsadas_; }
};
