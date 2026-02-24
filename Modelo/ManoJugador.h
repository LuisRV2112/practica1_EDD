#pragma once

#include "Ficha.h"

class ManoJugador {
private:
    struct Enlace {
        Ficha*  ficha;
        Enlace* proximo;
        explicit Enlace(Ficha* f) : ficha(f), proximo(nullptr) {}
    };
    Enlace* inicio_;
    int     cantidad_;

public:
    ManoJugador()  : inicio_(nullptr), cantidad_(0) {}
    ~ManoJugador() { vaciar(); }

    ManoJugador(const ManoJugador&)            = delete;
    ManoJugador& operator=(const ManoJugador&) = delete;

    void agregar(Ficha* f) {
        Enlace* nuevo = new Enlace(f);
        if (!inicio_) { inicio_ = nuevo; }
        else { Enlace* it = inicio_; while (it->proximo) it = it->proximo; it->proximo = nuevo; }
        ++cantidad_;
    }


    Ficha* extraer(int idx) {
        if (idx < 0 || idx >= cantidad_) return nullptr;
        Enlace* prev = nullptr; Enlace* curr = inicio_;
        for (int i = 0; i < idx; ++i) { prev = curr; curr = curr->proximo; }
        if (prev) prev->proximo = curr->proximo;
        else      inicio_       = curr->proximo;
        Ficha* f = curr->ficha; delete curr; --cantidad_; return f;
    }

    Ficha* consultar(int idx) const {
        if (idx < 0 || idx >= cantidad_) return nullptr;
        Enlace* it = inicio_;
        for (int i = 0; i < idx; ++i) it = it->proximo;
        return it->ficha;
    }

    int  totalFichas() const { return cantidad_; }
    bool sinFichas()   const { return cantidad_ == 0; }

    void vaciar() {
        while (inicio_) { Enlace* tmp = inicio_; inicio_ = inicio_->proximo; delete tmp; }
        cantidad_ = 0;
    }
};
