#pragma once

#include "Nodo.h"

template <typename T>
class ListaDoble {
private:
    Nodo<T>* cabeza;
    int tamano;

public:
    ListaDoble() : cabeza(nullptr), tamano(0) {}

    ~ListaDoble() {
        while (tamano > 0) eliminarEn(0);
    }

    void insertar(T dato) {
        Nodo<T>* nuevo = new Nodo<T>(dato);
        if (cabeza == nullptr) {
            cabeza = nuevo;
        } else {
            Nodo<T>* aux = cabeza;
            while (aux->siguiente != nullptr) aux = aux->siguiente;
            aux->siguiente = nuevo;
            nuevo->anterior = aux;
        }
        tamano++;
    }

    T eliminarEn(int indice) {
        if (indice < 0 || indice >= tamano || cabeza == nullptr) return nullptr;

        Nodo<T>* aux = cabeza;
        for (int i = 0; i < indice; i++) aux = aux->siguiente;

        if (aux->anterior) aux->anterior->siguiente = aux->siguiente;
        if (aux->siguiente) aux->siguiente->anterior = aux->anterior;
        if (aux == cabeza) cabeza = aux->siguiente;

        T dato = aux->dato;
        delete aux;
        tamano--;
        return dato;
    }

    Nodo<T>* getCabeza() { return cabeza; }
    int getTamano()      { return tamano; }
};
