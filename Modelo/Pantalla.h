#pragma once
/**
 * @file Pantalla.h
 * @brief Sistema de visualizacion en consola: arena, fichas, menus y alertas.
 * Practica1EDD - Laboratorio EDD USAC CUNOC 2026
 */
#include "Ficha.h"
#include "ManoJugador.h"
#include "Contendiente.h"
#include "ConfigPartida.h"
#include "ContextoPartida.h"
#include <string>

class Pantalla {
private:
    static const char* fondoTono(TonoCarta t);
    static const char* textoTono(TonoCarta t);
    static std::string centrarTexto(const std::string& s, int ancho);

public:
    // ── Utilidades ───────────────────────────────────────────────────────────
    static void limpiar();
    static void esperarEnter();
    static void separador(char relleno = '-', int largo = 64);
    static void encabezado(const std::string& texto);

    // ── Pantallas principales ─────────────────────────────────────────────
    static void mostrarPortada();
    static void mostrarMenuPrincipal();
    static void mostrarMenuConfig(const ConfigPartida& cfg);
    static void mostrarMenuAccion(const Contendiente* c, int turno);

    // ── Dibujo de fichas ──────────────────────────────────────────────────
    static void dibujarFicha(const Ficha* f);
    static void dibujarFichasDesdeMano(const ManoJugador* mano, int desde, int hasta);
    static void mostrarManoCompleta(const ManoJugador* mano,
                                    const std::string& alias);

    // ── Mano revelada temporalmente (FichaMostrarMano) ────────────────────
    // Muestra la mano completa del rival por segundos segundos y la borra.
    static void mostrarManoTemporal(const ManoJugador* mano,
                                    const std::string& alias,
                                    int segundos = 3);

    // ── Seleccion de rival en pantalla ─────────────────────────────────────
    // Permite al jugador activo elegir un oponente de la lista; retorna su indice.
    static int elegirRival(const Contendiente* lista[], int total, int idxActivo);

    // ── Arena de juego ────────────────────────────────────────────────────
    static void mostrarArena(const ContextoPartida& ctx,
                              const Contendiente*    lista[],
                              int                    total,
                              int                    idxActivo,
                              int                    reserva,
                              const Ficha*           enMesa);

    // ── Alertas y mensajes ────────────────────────────────────────────────
    static void alertaUNO(const std::string& alias);
    static void alertaCampeon(const std::string& alias);
    static void alertaAbandono(const std::string& aliasAbandona,
                                const std::string& aliasCampeon);
    static void alertaPenalizacion(const std::string& alias, int cantidad);
    static void alertaVolteo(CaraBaraja nuevaCara);
    static void alertaError(const std::string& mensaje);
    static void mostrarTurno(const std::string& alias, int turno);

    // ── Demo visual ─────────────────────────────────────────────────────
    static void demoFichas();
};
