#pragma once
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

    void push(const T& valor) { apilar(valor); }

    void sacar() {
        if (estaVacia())
            throw std::underflow_error("Pila::sacar() - pila sin elementos");
        Nodo* tmp = tope_;
        tope_     = tope_->inferior;
        delete tmp;
        --cantidad_;
    }


    void pop() { sacar(); }

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

    void volcarEnArreglo(T* arr) {
        Nodo* it = tope_;
        int   i  = 0;
        while (it) { arr[i++] = it->dato; it = it->inferior; }
    }

    void cargarDesdeArreglo(T* arr, int n) {
        while (!estaVacia()) sacar();
        for (int i = 0; i < n; ++i) apilar(arr[i]);
    }
};
