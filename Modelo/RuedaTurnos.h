#pragma once

#include "Contendiente.h"

class RuedaTurnos {
public:
    struct Ranura {
        Contendiente* contendiente;
        Ranura*       adelante;
        Ranura*       atras;
        explicit Ranura(Contendiente* c)
            : contendiente(c), adelante(nullptr), atras(nullptr) {}
    };

private:
    Ranura* enTurno_;
    int     cantidad_;
    bool    horario_;

public:
    RuedaTurnos()  : enTurno_(nullptr), cantidad_(0), horario_(true) {}
    ~RuedaTurnos() { limpiar(); }

    RuedaTurnos(const RuedaTurnos&)            = delete;
    RuedaTurnos& operator=(const RuedaTurnos&) = delete;

    /** Inserta contendiente al final del ciclo  O(1) */
    void inscribir(Contendiente* c) {
        Ranura* nueva = new Ranura(c);
        if (!enTurno_) {
            enTurno_          = nueva;
            nueva->adelante   = nueva;
            nueva->atras      = nueva;
        } else {
            Ranura* ultimo  = enTurno_->atras;
            ultimo->adelante  = nueva;
            nueva->atras      = ultimo;
            nueva->adelante   = enTurno_;
            enTurno_->atras   = nueva;
        }
        ++cantidad_;
    }

    void avanzar() {
        if (!enTurno_) return;
        enTurno_ = horario_ ? enTurno_->adelante : enTurno_->atras;
    }

    /** Salta un turno (Bloqueo)  O(1) */
    void omitirSiguiente() { avanzar(); avanzar(); }

    /** Invierte el sentido de la rueda  O(1) */
    void invertirSentido() { horario_ = !horario_; }

    /**
     * Elimina la ranura del turno actual y avanza  O(1)
     * Se usa para "Dejar el juego" - el jugador abandona la partida
     */
    void retirarActual() {
        if (!enTurno_ || cantidad_ == 0) return;
        Ranura* sig = enTurno_->adelante;
        if (cantidad_ == 1) {
            delete enTurno_;
            enTurno_  = nullptr;
            cantidad_ = 0;
            return;
        }
        Ranura* ant      = enTurno_->atras;
        ant->adelante    = sig;
        sig->atras       = ant;
        delete enTurno_;
        enTurno_  = sig;
        --cantidad_;
    }

    Contendiente* getActual()    const {
        return enTurno_ ? enTurno_->contendiente : nullptr;
    }
    Contendiente* getSiguiente() const {
        if (!enTurno_) return nullptr;
        return (horario_ ? enTurno_->adelante : enTurno_->atras)->contendiente;
    }

    Ranura* getRanuraActual() const { return enTurno_; }
    int     totalJugadores()  const { return cantidad_; }
    bool    vacia()           const { return cantidad_ == 0; }
    bool    esHorario()       const { return horario_; }

    void limpiar() {
        if (!enTurno_) return;
        Ranura* it = enTurno_;
        for (int i = 0; i < cantidad_; ++i) {
            Ranura* tmp = it;
            it = it->adelante;
            delete tmp;
        }
        enTurno_  = nullptr;
        cantidad_ = 0;
    }
};
