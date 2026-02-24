#pragma once
/**
 * @file ListaCircular.h
 * @brief Lista doblemente enlazada circular generica
 * Practica1EDD - Laboratorio EDD USAC CUNOC 2026
 */
#include "Nodo.h"

template <typename T>
class ListaCircular {
private:
    Nodo<T>* actual;
    int tamano;
    bool sentidoHorario;

public:
    ListaCircular() : actual(nullptr), tamano(0), sentidoHorario(true) {}

    /** Inserta al final de la lista circular */
    void insertar(T dato) {
        Nodo<T>* nuevo = new Nodo<T>(dato);
        if (actual == nullptr) {
            actual = nuevo;
            actual->siguiente = actual;
            actual->anterior  = actual;
        } else {
            Nodo<T>* ultimo   = actual->anterior;
            nuevo->siguiente  = actual;
            nuevo->anterior   = ultimo;
            ultimo->siguiente = nuevo;
            actual->anterior  = nuevo;
        }
        tamano++;
    }

    void cambiarSentido() { sentidoHorario = !sentidoHorario; }

    void avanzar() {
        if (actual)
            actual = sentidoHorario ? actual->siguiente : actual->anterior;
    }

    void saltar() { avanzar(); avanzar(); }

    T getActual() { return actual ? actual->dato : nullptr; }
    int getTamano() { return tamano; }
};
