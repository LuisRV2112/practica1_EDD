#pragma once
/**
 * @file Nodo.h
 * @brief Nodo generico con punteros dobles para listas enlazadas
 * Practica1EDD - Laboratorio EDD USAC CUNOC 2026
 */
template <typename T>
class Nodo {
public:
    T dato;
    Nodo<T>* siguiente;
    Nodo<T>* anterior;

    explicit Nodo(T valor)
        : dato(valor), siguiente(nullptr), anterior(nullptr) {}
};
