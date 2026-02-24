#pragma once
/**
 * @file Pila.h
 * @brief TAD Pila generica implementada con nodos dinamicos
 * Sin uso de contenedores STL
 * Practica1EDD - Laboratorio EDD USAC CUNOC 2026
 */
#include <stdexcept>

template<typename T>
class Pila {
private:
    struct Nodo {
        T     dato;
        Nodo* inferior;
        explicit Nodo(const T& d) : dato(d), inferior(nullptr) {}
    };

    Nodo* tope_;
    int   cantidad_;

public:
    Pila()  : tope_(nullptr), cantidad_(0) {}

    ~Pila() {
        while (!estaVacia()) sacar();
    }

    Pila(const Pila&)            = delete;
    Pila& operator=(const Pila&) = delete;

    /** Apila un elemento en el tope  O(1) */
    void apilar(const T& valor) {
        Nodo* nuevo     = new Nodo(valor);
        nuevo->inferior = tope_;
        tope_           = nuevo;
        ++cantidad_;
    }

    /** Alias push para compatibilidad con codigo antiguo */
    void push(const T& valor) { apilar(valor); }

    /** Desapila el elemento del tope  O(1) */
    void sacar() {
        if (estaVacia())
            throw std::underflow_error("Pila::sacar() - pila sin elementos");
        Nodo* tmp = tope_;
        tope_     = tope_->inferior;
        delete tmp;
        --cantidad_;
    }

    /** Alias pop para compatibilidad con codigo antiguo */
    void pop() { sacar(); }

    /** Devuelve referencia al tope sin extraer  O(1) */
    T& verTope() {
        if (estaVacia())
            throw std::underflow_error("Pila::verTope() - pila sin elementos");
        return tope_->dato;
    }

    const T& verTope() const {
        if (estaVacia())
            throw std::underflow_error("Pila::verTope() - pila sin elementos");
        return tope_->dato;
    }

    int  totalElementos() const { return cantidad_; }
    int  size()           const { return cantidad_; }
    bool estaVacia()      const { return cantidad_ == 0; }

    /** Vuelca la pila en un arreglo (tope => indice 0)  O(n) */
    void volcarEnArreglo(T* arr) {
        Nodo* it = tope_;
        int   i  = 0;
        while (it) { arr[i++] = it->dato; it = it->inferior; }
    }

    /** Reconstruye la pila desde un arreglo (indice 0 queda al fondo)  O(n) */
    void cargarDesdeArreglo(T* arr, int n) {
        while (!estaVacia()) sacar();
        for (int i = 0; i < n; ++i) apilar(arr[i]);
    }
};
