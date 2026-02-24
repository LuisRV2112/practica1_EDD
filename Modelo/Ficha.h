#pragma once
/**
 * @file Ficha.h
 * @brief Clase abstracta base; toda ficha tiene tono, categoria, efecto y cara.
 * Practica1EDD - Laboratorio EDD USAC CUNOC 2026
 */
#include "Dominio.h"

struct ContextoPartida;

class Ficha {
protected:
    TonoCarta      tono_;
    CategoriaCarta categoria_;
    EfectoCarta    efecto_;
    CaraBaraja     cara_;

public:
    Ficha(TonoCarta tono, CategoriaCarta categoria,
          EfectoCarta efecto, CaraBaraja cara = CaraBaraja::LUMINOSA)
        : tono_(tono), categoria_(categoria), efecto_(efecto), cara_(cara) {}

    virtual ~Ficha() = default;

    virtual void        renderizar()                               const = 0;
    virtual bool        esValida(const Ficha* fichaEnMesa)         const = 0;
    virtual void        ejecutarEfecto(ContextoPartida& contexto)  const = 0;
    virtual std::string obtenerSimbolo()                           const = 0;

    TonoCarta      getTono()      const { return tono_; }
    CategoriaCarta getCategoria() const { return categoria_; }
    EfectoCarta    getEfecto()    const { return efecto_; }
    CaraBaraja     getCara()      const { return cara_; }
    void           asignarTono(TonoCarta t) { tono_ = t; }
};
