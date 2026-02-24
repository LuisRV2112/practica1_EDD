#include "../../Modelo/Pantalla.h"
#include "../../Modelo/Paleta.h"
#include "../../Modelo/FichaNumeral.h"
#include "../../Modelo/FichaPoderosa.h"
#include "../../Modelo/FichaLibre.h"
#include "../../Modelo/FichaVolteo.h"
#include "../../Modelo/FichaEspecial.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <thread>
#include <chrono>

const char* Pantalla::fondoTono(TonoCarta t) {
    switch (t) {
        case TonoCarta::CARMESI:    return Paleta::FND_ROJO;
        case TonoCarta::ESMERALDA:  return Paleta::FND_VERDE;
        case TonoCarta::ZAFIRO:     return Paleta::FND_AZUL;
        case TonoCarta::DORADO:     return Paleta::FND_AMARILLO;
        case TonoCarta::FUCSIA:     return Paleta::FND_ROSA;
        case TonoCarta::AGUAMARINA: return Paleta::FND_CIAN;
        case TonoCarta::CORAL:      return Paleta::FND_NARANJA;
        case TonoCarta::INDIGO:     return Paleta::FND_MAGENTA;
        case TonoCarta::OBSIDIANA:  return Paleta::FND_NEGRO;
        default:                    return Paleta::FND_NEGRO;
    }
}

const char* Pantalla::textoTono(TonoCarta t) {
    switch (t) {
        case TonoCarta::ZAFIRO:
        case TonoCarta::OBSIDIANA:
        case TonoCarta::INDIGO:
        case TonoCarta::FUCSIA:    return Paleta::BLANCO;
        default:                   return Paleta::NEGRO;
    }
}

std::string Pantalla::centrarTexto(const std::string& s, int ancho) {
    int pad = (ancho - static_cast<int>(s.size())) / 2;
    std::string r(pad, ' ');
    r += s;
    while (static_cast<int>(r.size()) < ancho) r += ' ';
    return r;
}


void Pantalla::limpiar() { std::cout << "\033[2J\033[H"; }

void Pantalla::esperarEnter() {
    std::cout << Paleta::TENUE
              << "\n  [ Presiona ENTER para continuar ]"
              << Paleta::RESET;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Pantalla::separador(char relleno, int largo) {
    std::cout << Paleta::TENUE;
    for (int i = 0; i < largo; ++i) std::cout << relleno;
    std::cout << Paleta::RESET << "\n";
}

void Pantalla::encabezado(const std::string& texto) {
    std::cout << "\n";
    separador('=', 64);
    int pad = (62 - static_cast<int>(texto.size())) / 2;
    std::cout << Paleta::NEGRITA << Paleta::AMARILLO << " ";
    for (int i = 0; i < pad; ++i) std::cout << " ";
    std::cout << texto << "\n" << Paleta::RESET;
    separador('=', 64);
    std::cout << "\n";
}


void Pantalla::mostrarPortada() {
    limpiar();
    std::cout << "\n\n";
    std::cout << Paleta::ROJO  << Paleta::NEGRITA;
    std::cout << "   BIENVENIDO A UNO \n";
    std::cout << Paleta::RESET;
    std::cout << Paleta::VERDE << Paleta::NEGRITA;
    std::cout << "  ~~~~~~~~~~~~~~~~~~~~\n";
    std::cout << Paleta::RESET;
    std::cout << Paleta::AMARILLO << Paleta::NEGRITA;
    std::cout << "      CLASICO Y FLIP\n";
    std::cout << Paleta::RESET;
    std::cout << Paleta::AZUL;
    std::cout << "  PRACTICA 1\n\n";
    std::cout << Paleta::RESET;
    separador('~', 40);
}



void Pantalla::mostrarMenuPrincipal() {
    mostrarPortada();
    std::cout << "\n";
    std::cout << "  " << Paleta::NEGRITA << Paleta::CIAN
              << ">> MENU PRINCIPAL <<" << Paleta::RESET << "\n\n";
    std::cout << "   ( 1 )  Iniciar Partida\n";
    std::cout << "   ( 2 )  Ajustar Configuracion\n";
    std::cout << "   ( 3 )  Ver Demo de Fichas\n";
    std::cout << "   ( 4 )  Cargar Configuracion desde Archivo\n";
    std::cout << "   ( 0 )  Salir del juiego\n\n";
    separador('-', 40);
    std::cout << "  Elige >> ";
}

// Menu Configuracion

void Pantalla::mostrarMenuConfig(const ConfigPartida& cfg) {
    limpiar();
    encabezado("AJUSTES DE PARTIDA");
    cfg.mostrar();
    std::cout << "\n";
    std::cout << "   ( 1 ) Alternar: Apilar robos\n";
    std::cout << "   ( 2 ) Alternar: Reto ficha libre\n";
    std::cout << "   ( 3 ) Alternar: Robo ilimitado\n";
    std::cout << "   ( 4 ) Alternar: Grito UNO (no desactivar)\n";
    std::cout << "   ( 5 ) Alternar: Ganar con Obsidiana\n";
    std::cout << "   ( 6 ) Alternar: Modo Flip\n";
    std::cout << "   ( 7 ) Guardar configuracion\n";
    std::cout << "   ( 0 ) Volver\n\n";
    std::cout << "  Opcion >> ";
}

// Menu Accion durante turno

void Pantalla::mostrarMenuAccion(const Contendiente* c, int turno) {
    std::cout << "\n";
    separador('-', 56);
    std::cout << Paleta::NEGRITA << Paleta::VERDE
              << "  TURNO #" << turno
              << "  |  " << c->getAlias()
              << "  |  Fichas: " << c->fichasEnMano()
              << Paleta::RESET << "\n";
    separador('-', 56);
    std::cout << "  ( 0..N )  Lanzar ficha por indice\n";
    std::cout << "  (  T  )  Tomar ficha de la reserva\n";
    std::cout << "  (  U  )  Gritar UNO!\n";
    std::cout << "  (  V  )  Ver mis fichas\n";
    std::cout << Paleta::ROJO << Paleta::NEGRITA
              << "  (  Q  )  Dejar el juego\n"
              << Paleta::RESET;
    if (c->fichasEnMano() == 1)
        std::cout << Paleta::ROJO << Paleta::NEGRITA
                  << "  *** ATENCION: te queda 1 ficha. Grita UNO! ***\n"
                  << Paleta::RESET;
    std::cout << "  Accion >> ";
}

//Dibujo de una ficha individual
/*
  +=========+
  | X     X |   <- inicial del tono
  |  [  |   <- simbolo centrado
  |         |
  |  []  |
  | X     X |
  +=========+
*/
void Pantalla::dibujarFicha(const Ficha* f) {
    if (!f) {

        std::cout << Paleta::FND_AZUL << Paleta::BLANCO << Paleta::NEGRITA;
        std::cout << "+=========+\n";
        std::cout << "|  # # #  |\n";
        std::cout << "|  UNO    |\n";
        std::cout << "|  # # #  |\n";
        std::cout << "|  # # #  |\n";
        std::cout << "|  # # #  |\n";
        std::cout << "+=========+" << Paleta::RESET << "\n";
        return;
    }

    const char* fondo = fondoTono(f->getTono());
    const char* texto = textoTono(f->getTono());
    char ini          = inicialTono(f->getTono());
    std::string sim   = "[" + f->obtenerSimbolo() + "]";
    std::string simC  = centrarTexto(sim, 7);

    std::cout << fondo << texto << Paleta::NEGRITA;
    std::cout << "+=========+\n";
    std::cout << "| " << ini << "     " << ini << " |\n";
    std::cout << "| " << simC << " |\n";
    std::cout << "|         |\n";
    std::cout << "| " << simC << " |\n";
    std::cout << "| " << ini << "     " << ini << " |\n";
    std::cout << "+=========+" << Paleta::RESET << "\n";
}



void Pantalla::dibujarFichasDesdeMano(const ManoJugador* mano,
                                       int desde, int hasta) {
    if (!mano) return;
    int n = hasta - desde;
    if (n <= 0) return;

    const int FILAS = 7;
    struct LineaFicha { std::string fila[7]; };
    LineaFicha* buf = new LineaFicha[n];

    for (int ci = 0; ci < n; ++ci) {
        const Ficha* f = mano->consultar(desde + ci);
        if (!f) {
            for (int fi = 0; fi < FILAS; ++fi) buf[ci].fila[fi] = "            ";
            continue;
        }
        const char* fnd = fondoTono(f->getTono());
        const char* txt = textoTono(f->getTono());
        char ini        = inicialTono(f->getTono());
        std::string sim = "[" + f->obtenerSimbolo() + "]";
        std::string sc  = centrarTexto(sim, 7);
        std::string B   = std::string(fnd) + txt + Paleta::NEGRITA;
        std::string R   = Paleta::RESET;

        buf[ci].fila[0] = B + "+=========+" + R;
        buf[ci].fila[1] = B + "| " + ini + "     " + ini + " |" + R;
        buf[ci].fila[2] = B + "| " + sc  + " |" + R;
        buf[ci].fila[3] = B + "|         |" + R;
        buf[ci].fila[4] = B + "| " + sc  + " |" + R;
        buf[ci].fila[5] = B + "| " + ini + "     " + ini + " |" + R;
        buf[ci].fila[6] = B + "+=========+" + R;
    }

    for (int fi = 0; fi < FILAS; ++fi) {
        std::cout << "  ";
        for (int ci = 0; ci < n; ++ci)
            std::cout << buf[ci].fila[fi] << " ";
        std::cout << "\n";
    }
    delete[] buf;
}

void Pantalla::mostrarManoCompleta(const ManoJugador* mano,
                                    const std::string& alias) {
    if (!mano) return;
    std::cout << "\n" << Paleta::NEGRITA << Paleta::AMARILLO
              << "  === Fichas de " << alias
              << " [" << mano->totalFichas() << "] ===\n"
              << Paleta::RESET;
    separador('-', 64);

    const int GRUPO = 6;
    int total = mano->totalFichas();
    for (int i = 0; i < total; i += GRUPO) {
        int fin = (i + GRUPO < total) ? i + GRUPO : total;
        std::cout << "  ";
        for (int j = i; j < fin; ++j)
            std::cout << std::setw(12) << std::left
                      << ("(" + std::to_string(j) + ")") << " ";
        std::cout << "\n";
        dibujarFichasDesdeMano(mano, i, fin);
    }
}


void Pantalla::mostrarManoTemporal(const ManoJugador* mano,
                                    const std::string& alias,
                                    int segundos) {
    limpiar();
    std::cout << Paleta::AMARILLO << Paleta::NEGRITA;
    std::cout << "  *** ESPIONAJE: mano de " << alias << " ***\n";
    std::cout << "  (visible durante " << segundos << " segundos)\n";
    std::cout << Paleta::RESET;
    separador('=', 64);
    mostrarManoCompleta(mano, alias);
    separador('=', 64);

    // Cuenta regresiva visible en consola
    for (int s = segundos; s > 0; --s) {
        std::cout << "\r  Ocultando en " << s << " seg...   " << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "\r                              \n";
    limpiar();
}

// Seleccion de rival
// Muestra la lista de contendientes (excluyendo al activo) y devuelve el indice de la ranura elegida por el jugador activo.
int Pantalla::elegirRival(const Contendiente* lista[], int total, int idxActivo) {
    std::cout << "\n" << Paleta::CIAN << Paleta::NEGRITA
              << "  Elige al rival objetivo:\n" << Paleta::RESET;

    int validos[20];
    int nValidos = 0;
    for (int i = 0; i < total; ++i) {
        if (i == idxActivo) continue;
        if (!lista[i] || lista[i]->eliminado()) continue;
        std::cout << "  (" << (i + 1) << ") " << lista[i]->getAlias()
                  << "  [" << lista[i]->fichasEnMano() << " fichas]\n";
        validos[nValidos++] = i;
    }

    if (nValidos == 0) return -1; // detecta que no hay rivales disponibles

    int eleccion = -1;
    while (true) {
        std::cout << "  Numero >> ";
        int v;
        if (!(std::cin >> v)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        for (int k = 0; k < nValidos; ++k) {
            if (validos[k] + 1 == v) { eleccion = validos[k]; break; }
        }
        if (eleccion >= 0) break;
        std::cout << "  Seleccion invalida. Intenta de nuevo.\n";
    }
    return eleccion;
}


void Pantalla::mostrarArena(const ContextoPartida& ctx,
                              const Contendiente*    lista[],
                              int                    total,
                              int                    idxActivo,
                              int                    reserva,
                              const Ficha*           enMesa) {
    limpiar();

    std::cout << Paleta::NEGRITA << Paleta::CIAN;
    separador('=', 64);
    std::cout << "  UNO  |  Turno #" << ctx.numeroTurno
              << "  |  Cara: "
              << (ctx.caraActiva == CaraBaraja::LUMINOSA ? "LUMINOSA" : "SOMBRIA")
              << "  |  Sentido: "
              << (ctx.giroActivo ? ">>>" : "<<<")
              << "\n";
    separador('=', 64);
    std::cout << Paleta::RESET << "\n";

    // Columna izquierda: reserva — columna derecha: ficha en mesa
    auto linReserva = [&](int fi) -> std::string {
        std::string B = std::string(Paleta::FND_AZUL) + Paleta::BLANCO + Paleta::NEGRITA;
        std::string R = Paleta::RESET;
        std::string cnt = "  " + std::to_string(reserva) + " fichas";
        switch (fi) {
            case 0: return B + "+=========+" + R;
            case 1: return B + "|  # # #  |" + R;
            case 2: return B + "|  UNO    |" + R;
            case 3: return B + "|  # # #  |" + R;
            case 4: return B + "|  # # #  |" + R;
            case 5: return B + "|  # # #  |" + R;
            case 6: return B + "+=========+" + R;
            case 7: return Paleta::CIAN + cnt + Paleta::RESET;
            default: return "";
        }
    };

    auto linMesa = [&](int fi) -> std::string {
        if (!enMesa) return "           ";
        const char* fnd = fondoTono(enMesa->getTono());
        const char* txt = textoTono(enMesa->getTono());
        char ini        = inicialTono(enMesa->getTono());
        std::string sim = "[" + enMesa->obtenerSimbolo() + "]";
        std::string sc  = centrarTexto(sim, 7);
        std::string B   = std::string(fnd) + txt + Paleta::NEGRITA;
        std::string R   = Paleta::RESET;
        switch (fi) {
            case 0: return B + "+=========+" + R;
            case 1: return B + "| " + ini + "     " + ini + " |" + R;
            case 2: return B + "| " + sc  + " |" + R;
            case 3: return B + "|         |" + R;
            case 4: return B + "| " + sc  + " |" + R;
            case 5: return B + "| " + ini + "     " + ini + " |" + R;
            case 6: return B + "+=========+" + R;
            case 7: return std::string(Paleta::AMARILLO) + "  Ultimo descarte" + Paleta::RESET;
            default: return "";
        }
    };

    std::cout << " PILA CARTAS                EN LA MESA\n";
    for (int fi = 0; fi <= 7; ++fi)
        std::cout << "  " << linReserva(fi) << "    " << linMesa(fi) << "\n";

    std::cout << "\n  " << Paleta::NEGRITA
              << "Tono activo: "
              << fondoTono(ctx.tonoActivo) << textoTono(ctx.tonoActivo)
              << "  " << nombreTono(ctx.tonoActivo) << "  "
              << Paleta::RESET;
    if (ctx.acumRobo > 0)
        std::cout << Paleta::ROJO << Paleta::NEGRITA
                  << "  << Robo acumulado: +" << ctx.acumRobo << " >>"
                  << Paleta::RESET;
    std::cout << "\n\n";

    separador('-', 64);
    std::cout << Paleta::NEGRITA << "  CONTENDIENTES Y/O JUGADORES:\n" << Paleta::RESET;
    for (int i = 0; i < total; ++i) {
        if (!lista[i] || lista[i]->eliminado()) continue;
        bool activo = (i == idxActivo);
        std::cout << (activo ? Paleta::VERDE : Paleta::TENUE)
                  << Paleta::NEGRITA
                  << "  " << (activo ? "--> " : "    ")
                  << lista[i]->getAlias()
                  << "   [" << lista[i]->fichasEnMano() << " fichas]"
                  << (lista[i]->gritado()      ? "  *UNO*"      : "")
                  << (lista[i]->tieneBarrera() ? "  [BARRERA]" : "")
                  << Paleta::RESET << "\n";
    }
    separador('-', 64);
}


void Pantalla::alertaUNO(const std::string& alias) {
    std::cout << "\n" << Paleta::AMARILLO << Paleta::NEGRITA
              << "  *** " << alias << " GRITO UNO! ***\n"
              << Paleta::RESET;
}

void Pantalla::alertaCampeon(const std::string& alias) {
    limpiar();
    encabezado("PARTIDA TERMINADA");
    std::cout << Paleta::AMARILLO << Paleta::NEGRITA
              << "\n  CAMPEON DEL ARENA: " << alias << "\n\n"
              << Paleta::RESET;
}

void Pantalla::alertaAbandono(const std::string& aliasAbandona,
                               const std::string& aliasCampeon) {
    limpiar();
    encabezado("JUGADOR ABANDONA LA PARTIDA");
    std::cout << Paleta::ROJO << Paleta::NEGRITA
              << "\n  " << aliasAbandona << " ha abandonado la partida.\n"
              << Paleta::RESET;
    std::cout << Paleta::AMARILLO << Paleta::NEGRITA
              << "  GANADOR: " << aliasCampeon << "\n\n"
              << Paleta::RESET;
}

void Pantalla::alertaPenalizacion(const std::string& alias, int cantidad) {
    std::cout << Paleta::ROJO
              << "  [!] " << alias << " recibe "
              << cantidad << " ficha(s) de penalizacion.\n"
              << Paleta::RESET;
}

void Pantalla::alertaVolteo(CaraBaraja nuevaCara) {
    if (nuevaCara == CaraBaraja::SOMBRIA)
        std::cout << Paleta::MAGENTA << Paleta::NEGRITA
                  << "\n  *** VOLTEO! Cara SOMBRIA activada ***\n"
                  << Paleta::RESET;
    else
        std::cout << Paleta::AMARILLO << Paleta::NEGRITA
                  << "\n  *** VOLTEO! Cara LUMINOSA restaurada ***\n"
                  << Paleta::RESET;
}

void Pantalla::alertaError(const std::string& mensaje) {
    std::cout << Paleta::ROJO << "  [!] " << mensaje
              << Paleta::RESET << "\n";
}

void Pantalla::mostrarTurno(const std::string& alias, int turno) {
    std::cout << Paleta::VERDE
              << "\n  -- Turno #" << turno << ": " << alias << " --\n"
              << Paleta::RESET;
}

// Demo visual

void Pantalla::demoFichas() {
    limpiar();
    encabezado("DEMO DE FICHAS - UNO ARENA");

    FichaNumeral       n1(TonoCarta::CARMESI,   7);
    FichaNumeral       n2(TonoCarta::ESMERALDA, 3);
    FichaNumeral       n3(TonoCarta::ZAFIRO,    0);
    FichaNumeral       n4(TonoCarta::DORADO,    9);
    FichaPoderosa      p1(TonoCarta::CARMESI,   EfectoCarta::BLOQUEO);
    FichaPoderosa      p2(TonoCarta::ESMERALDA, EfectoCarta::GIRO);
    FichaPoderosa      p3(TonoCarta::ZAFIRO,    EfectoCarta::ROBO_DOS);
    FichaLibre         l1(false);
    FichaLibre         l2(true);
    FichaVolteo        v1(TonoCarta::CARMESI);
    FichaDevuraTono    d1(TonoCarta::DORADO);
    FichaBarreraActiva ba1(TonoCarta::INDIGO);
    FichaMostrarMano   spy(TonoCarta::CARMESI);
    FichaIntercambiarCarta swp(TonoCarta::ESMERALDA);

    ManoJugador m1, m2, m3, m4;
    m1.agregar(&n1); m1.agregar(&n2); m1.agregar(&n3); m1.agregar(&n4);
    m2.agregar(&p1); m2.agregar(&p2); m2.agregar(&p3); m2.agregar(&l1); m2.agregar(&l2);
    m3.agregar(&v1); m3.agregar(&d1); m3.agregar(&ba1);
    m4.agregar(&spy); m4.agregar(&swp);

    std::cout << Paleta::NEGRITA << "  -- Fichas Numerales --\n" << Paleta::RESET;
    std::cout << "  (0)         (1)         (2)         (3)\n";
    dibujarFichasDesdeMano(&m1, 0, 4);

    std::cout << "\n" << Paleta::NEGRITA << "  -- Fichas Poderosas y Libres --\n" << Paleta::RESET;
    std::cout << "  (BLQ)       (GIR)       (+2)        (ELG)       (+4)\n";
    dibujarFichasDesdeMano(&m2, 0, 5);

    std::cout << "\n" << Paleta::NEGRITA << "  -- Especiales clasicas --\n" << Paleta::RESET;
    std::cout << "  (VLT)       (DVR)       (BRR)\n";
    dibujarFichasDesdeMano(&m3, 0, 3);

    std::cout << "\n" << Paleta::NEGRITA << "  -- Cartas Personalizadas --\n" << Paleta::RESET;
    std::cout << "  (SPY)       (SWP)\n";
    dibujarFichasDesdeMano(&m4, 0, 2);
    std::cout << Paleta::TENUE
              << "  SPY = Mostrar Mano del rival\n"
              << "  SWP = Intercambiar una carta con un rival\n"
              << Paleta::RESET;

    std::cout << "\n";
    separador('~', 64);

    m1.vaciar(); m2.vaciar(); m3.vaciar(); m4.vaciar();
    esperarEnter();
}
