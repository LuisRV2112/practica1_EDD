#pragma once
#include <string>

// Tono (color) de una carta
enum class TonoCarta {
    CARMESI, ESMERALDA, ZAFIRO, DORADO,       // Cara luminosa
    FUCSIA, AGUAMARINA, CORAL, INDIGO,         // Cara sombria (UNO Flip)
    OBSIDIANA,                                  // Sin color
    INDEFINIDO
};

enum class CategoriaCarta {
    NUMERAL,
    PODEROSA,
    LIBRE,
    VOLTEO,
    DEVORA_TONO,
    BARRERA_ACTIVA,
    MOSTRAR_MANO,
    INTERCAMBIAR_CARTA
};

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
