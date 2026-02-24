#pragma once
/**
 * @file Dominio.h
 * @brief Enumeraciones globales: tonos, categorias, efectos y cara del mazo.
 * Practica1EDD - Laboratorio EDD USAC CUNOC 2026
 */
#include <string>

// Tono (color) de una ficha — cara luminosa, sombria u obsidiana (wildcard)
enum class TonoCarta {
    CARMESI, ESMERALDA, ZAFIRO, DORADO,       // Cara luminosa
    FUCSIA, AGUAMARINA, CORAL, INDIGO,         // Cara sombria (UNO Flip)
    OBSIDIANA,                                  // Sin color
    INDEFINIDO
};

// Categoria que identifica el tipo de ficha dentro de la jerarquia
enum class CategoriaCarta {
    NUMERAL,
    PODEROSA,
    LIBRE,
    VOLTEO,
    DEVORA_TONO,
    BARRERA_ACTIVA,
    MOSTRAR_MANO,       // Carta personalizada: fuerza a un rival a mostrar su mano
    INTERCAMBIAR_CARTA  // Carta personalizada: intercambia una carta con un rival
};

// Efecto que se aplica al contexto cuando la ficha es jugada
enum class EfectoCarta {
    NINGUNO,
    ROBO_UNO,
    ROBO_DOS,
    ROBO_TRES,
    ROBO_CUATRO,
    ROBO_SEIS,
    BLOQUEO,
    BLOQUEO_TOTAL,
    GIRO,
    ELEGIR_TONO,
    LANZAR_VOLTEO,
    TONO_ETERNO,
    DEVORA_COLOR,
    ESCUDO_ACTIVO,
    VER_MANO,           // Efecto de FichaMostrarMano
    ROBAR_CARTA         // Efecto de FichaIntercambiarCarta
};

// Cara activa del mazo para el modo UNO Flip
enum class CaraBaraja { LUMINOSA, SOMBRIA };

// Convierte TonoCarta a su nombre legible
inline std::string nombreTono(TonoCarta t) {
    switch (t) {
        case TonoCarta::CARMESI:    return "Carmesi";
        case TonoCarta::ESMERALDA:  return "Esmeralda";
        case TonoCarta::ZAFIRO:     return "Zafiro";
        case TonoCarta::DORADO:     return "Dorado";
        case TonoCarta::FUCSIA:     return "Fucsia";
        case TonoCarta::AGUAMARINA: return "Aguamarina";
        case TonoCarta::CORAL:      return "Coral";
        case TonoCarta::INDIGO:     return "Indigo";
        case TonoCarta::OBSIDIANA:  return "Obsidiana";
        default:                    return "?";
    }
}

// Devuelve la inicial del tono para dibujar la ficha en consola
inline char inicialTono(TonoCarta t) {
    switch (t) {
        case TonoCarta::CARMESI:    return 'C';
        case TonoCarta::ESMERALDA:  return 'E';
        case TonoCarta::ZAFIRO:     return 'Z';
        case TonoCarta::DORADO:     return 'D';
        case TonoCarta::FUCSIA:     return 'F';
        case TonoCarta::AGUAMARINA: return 'A';
        case TonoCarta::CORAL:      return 'O';
        case TonoCarta::INDIGO:     return 'I';
        case TonoCarta::OBSIDIANA:  return '*';
        default:                    return '?';
    }
}
