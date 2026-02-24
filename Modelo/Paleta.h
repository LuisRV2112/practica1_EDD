#pragma once
/**
 * @file Paleta.h
 * @brief Codigos ANSI de color para la terminal
 * Practica1EDD - Laboratorio EDD USAC CUNOC 2026
 */
namespace Paleta {
    constexpr const char* RESET    = "\033[0m";
    constexpr const char* NEGRO    = "\033[30m";
    constexpr const char* ROJO     = "\033[31m";
    constexpr const char* VERDE    = "\033[32m";
    constexpr const char* AMARILLO = "\033[33m";
    constexpr const char* AZUL     = "\033[34m";
    constexpr const char* MAGENTA  = "\033[35m";
    constexpr const char* CIAN     = "\033[36m";
    constexpr const char* BLANCO   = "\033[37m";
    constexpr const char* ROSA     = "\033[95m";
    constexpr const char* NARANJA  = "\033[91m";
    constexpr const char* NEGRITA  = "\033[1m";
    constexpr const char* TENUE    = "\033[2m";
    constexpr const char* INVERSO  = "\033[7m";
    // Fondos
    constexpr const char* FND_ROJO     = "\033[41m";
    constexpr const char* FND_VERDE    = "\033[42m";
    constexpr const char* FND_AMARILLO = "\033[43m";
    constexpr const char* FND_AZUL     = "\033[44m";
    constexpr const char* FND_MAGENTA  = "\033[45m";
    constexpr const char* FND_CIAN     = "\033[46m";
    constexpr const char* FND_NEGRO    = "\033[40m";
    constexpr const char* FND_ROSA     = "\033[105m";
    constexpr const char* FND_NARANJA  = "\033[101m";
}
