
#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include "Pantalla.h"
#include "Baraja.h"
#include "Contendiente.h"
#include "RuedaTurnos.h"
#include "ConfigPartida.h"
#include "ContextoPartida.h"
#include "FichaLibre.h"
#include "FichaNumeral.h"
#include "Paleta.h"

// Lee un entero en [minVal, maxVal] y rechaza entradas invalidas
static int pedirEntero(int minVal, int maxVal) {
    int v;
    while (!(std::cin >> v) || v < minVal || v > maxVal) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "  Valor fuera de rango (" << minVal
                  << "-" << maxVal << "). Intenta de nuevo: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return v;
}


static std::string pedirTexto(const std::string& aviso) {
    std::string s;
    std::cout << aviso;
    while (s.empty()) std::getline(std::cin, s);
    return s;
}


static TonoCarta elegirTono(CaraBaraja cara) {
    std::cout << "\n  Selecciona el tono:\n";
    if (cara == CaraBaraja::LUMINOSA) {
        std::cout << "  (1) Carmesi  (2) Esmeralda  (3) Zafiro  (4) Dorado\n";
        std::cout << "  Opcion >> ";
        int op = pedirEntero(1, 4);
        switch (op) {
            case 1: return TonoCarta::CARMESI;
            case 2: return TonoCarta::ESMERALDA;
            case 3: return TonoCarta::ZAFIRO;
            default: return TonoCarta::DORADO;
        }
    } else {
        std::cout << "  (1) Fucsia  (2) Aguamarina  (3) Coral  (4) Indigo\n";
        std::cout << "  Opcion >> ";
        int op = pedirEntero(1, 4);
        switch (op) {
            case 1: return TonoCarta::FUCSIA;
            case 2: return TonoCarta::AGUAMARINA;
            case 3: return TonoCarta::CORAL;
            default: return TonoCarta::INDIGO;
        }
    }
}


static int primerFichaValida(const Contendiente* c,
                              const Ficha* enMesa,
                              const ContextoPartida& ctx) {
    for (int i = 0; i < c->fichasEnMano(); ++i) {
        const Ficha* f = c->verFicha(i);
        if (!f) continue;
        if (ctx.acumRobo > 0 && ctx.config.apilar) {
            if (f->getEfecto() == enMesa->getEfecto() ||
                f->getEfecto() == EfectoCarta::ROBO_CUATRO)
                return i;
            continue;
        }
        if (f->esValida(enMesa)) return i;
    }
    return -1;
}

static std::string jugadorRestante(RuedaTurnos* rueda) {
    Contendiente* c = rueda->getActual();
    return c ? c->getAlias() : "Desconocido";
}

static int construirLista(RuedaTurnos* rueda, const Contendiente* lista[],
                           int maxC, const Contendiente* actual, int& idxActivo) {
    int total = 0;
    idxActivo = 0;
    RuedaTurnos::Ranura* ini = rueda->getRanuraActual();
    RuedaTurnos::Ranura* it  = ini;
    do {
        lista[total] = it->contendiente;
        if (it->contendiente == actual) idxActivo = total;
        ++total;
        it = it->adelante;
    } while (it != ini && total < maxC);
    return total;
}

// Efecto SPY: muestra la mano del rival por 3 segundos
static void resolverMostrarMano(ContextoPartida& ctx,
                                 const Contendiente* lista[], int total,
                                 int idxActivo) {
    ctx.pendienteMostrarMano = false;
    int idxRival = -1;

    if (ctx.rueda->totalJugadores() == 2) {
        // Con 2 jugadores el rival es el unico otro
        for (int i = 0; i < total; ++i) {
            if (i != idxActivo && lista[i] && !lista[i]->eliminado()) {
                idxRival = i; break;
            }
        }
    } else {
        // Con 3+ jugadores, el jugador activo elige
        idxRival = Pantalla::elegirRival(lista, total, idxActivo);
    }

    if (idxRival < 0) return;
    const Contendiente* rival = lista[idxRival];
    Pantalla::mostrarManoTemporal(rival->getMano(), rival->getAlias(), 3);
}

// Efecto SWP: roba una carta (aleatoria o elegida) de un rival
static void resolverIntercambio(ContextoPartida& ctx,
                                 const Contendiente* lista[], int total,
                                 int idxActivo) {
    ctx.pendienteIntercambio = false;
    Contendiente* activo = ctx.rueda->getActual();
    int idxRival = -1;

    if (ctx.rueda->totalJugadores() == 2) {
        for (int i = 0; i < total; ++i) {
            if (i != idxActivo && lista[i] && !lista[i]->eliminado()) {
                idxRival = i; break;
            }
        }
    } else {
        idxRival = Pantalla::elegirRival(lista, total, idxActivo);
    }

    if (idxRival < 0 || !activo) return;
    Contendiente* rival = const_cast<Contendiente*>(lista[idxRival]);
    if (rival->fichasEnMano() == 0) {
        Pantalla::alertaError("El rival no tiene fichas.");
        return;
    }

    // El rival elige si dar una carta aleatoria o elegirla el mismo
    std::cout << "\n" << Paleta::CIAN << Paleta::NEGRITA
              << "  " << rival->getAlias() << ": elige como ceder la carta:\n"
              << Paleta::RESET;
    std::cout << "  (1) Aleatoria   (2) Yo la elijo\n";
    std::cout << "  Opcion >> ";
    int modo = pedirEntero(1, 2);

    int idx = 0;
    if (modo == 2) {
        Pantalla::mostrarManoCompleta(rival->getMano(), rival->getAlias());
        std::cout << "  " << rival->getAlias()
                  << ": indice de la ficha a ceder [0-"
                  << (rival->fichasEnMano() - 1) << "]: ";
        idx = pedirEntero(0, rival->fichasEnMano() - 1);
    } else {
        idx = rand() % rival->fichasEnMano();
    }

    Ficha* cedida = rival->lanzarFicha(idx);
    if (cedida) {
        activo->recibirFicha(cedida);
        std::cout << Paleta::VERDE << Paleta::NEGRITA
                  << "  " << activo->getAlias()
                  << " recibio: " << cedida->obtenerSimbolo()
                  << " de " << rival->getAlias() << "\n"
                  << Paleta::RESET;
    }
    Pantalla::esperarEnter();
}


static void ejecutarTurno(ContextoPartida& ctx) {
    Contendiente* c      = ctx.rueda->getActual();
    Ficha*        enMesa = ctx.baraja->fichaEnMesa();

    const int MAX_C = 20;
    const Contendiente* lista[MAX_C];
    int total, idxActivo;
    total = construirLista(ctx.rueda, lista, MAX_C, c, idxActivo);

    Pantalla::mostrarArena(ctx, lista, total, idxActivo,
                            ctx.baraja->fichasDisponibles(), enMesa);


    if (c->tieneBarrera() && ctx.acumRobo > 0) {
        std::cout << Paleta::VERDE << Paleta::NEGRITA
                  << "  [BARRERA] " << c->getAlias()
                  << " anula el robo acumulado!\n" << Paleta::RESET;
        c->activarBarrera(false);
        ctx.acumRobo = 0;
        ctx.rueda->avanzar();
        return;
    }


    if (ctx.acumRobo > 0 && ctx.config.apilar) {
        if (primerFichaValida(c, enMesa, ctx) < 0) {
            std::cout << Paleta::ROJO
                      << "  Sin opciones. Robas " << ctx.acumRobo
                      << " fichas.\n" << Paleta::RESET;
            for (int i = 0; i < ctx.acumRobo; ++i)
                c->recibirFicha(ctx.baraja->tomarFicha());
            ctx.acumRobo = 0;
            ctx.rueda->avanzar();
            return;
        }
    }

    Pantalla::mostrarMenuAccion(c, ctx.numeroTurno);

    std::string entrada;
    std::getline(std::cin, entrada);


    if (entrada == "Q" || entrada == "q") {
        std::string aliasAbandona = c->getAlias();
        c->retirar();
        ctx.rueda->retirarActual();
        if (ctx.rueda->totalJugadores() == 1) {
            std::string cam = jugadorRestante(ctx.rueda);
            Pantalla::alertaAbandono(aliasAbandona, cam);
            ctx.partidaFin = true;
            ctx.campeon    = cam;
        } else if (ctx.rueda->totalJugadores() == 0) {
            ctx.partidaFin = true;
        }
        return;
    }


    if (entrada == "T" || entrada == "t") {
        if (!ctx.config.roboIlimitado) {
            Ficha* f = ctx.baraja->tomarFicha();
            if (f) {
                c->recibirFicha(f);
                std::cout << "  Tomaste: " << f->obtenerSimbolo() << "\n";
            }
            ctx.rueda->avanzar();
        } else {
            bool puedo = false;
            do {
                Ficha* f = ctx.baraja->tomarFicha();
                if (!f) break;
                c->recibirFicha(f);
                std::cout << "  Tomaste: " << f->obtenerSimbolo() << "\n";
                if (f->esValida(ctx.baraja->fichaEnMesa())) {
                    puedo = true; break;
                }
            } while (true);
            if (!puedo) ctx.rueda->avanzar();
        }
        return;
    }

    if (entrada == "U" || entrada == "u") {
        c->marcarUNO(true);
        Pantalla::alertaUNO(c->getAlias());
        return;
    }

    if (entrada == "V" || entrada == "v") {
        Pantalla::mostrarManoCompleta(c->getMano(), c->getAlias());
        Pantalla::esperarEnter();
        return;
    }

    try {
        int idx = std::stoi(entrada);
        if (idx < 0 || idx >= c->fichasEnMano()) {
            Pantalla::alertaError("Indice fuera de rango.");
            return;
        }
        Ficha* f = c->verFicha(idx);
        if (!f) { Pantalla::alertaError("Ficha no encontrada."); return; }

        bool valida = true;
        if (ctx.acumRobo > 0 && ctx.config.apilar) {
            valida = (f->getEfecto() == enMesa->getEfecto() ||
                      f->getEfecto() == EfectoCarta::ROBO_CUATRO);
        } else {
            valida = f->esValida(enMesa);
        }
        if (!valida) {
            Pantalla::alertaError("Esta ficha no es valida ahora.");
            return;
        }

        if (c->fichasEnMano() == 1 &&
            f->getTono() == TonoCarta::OBSIDIANA &&
            !ctx.config.permitirObs) {
            Pantalla::alertaError("No puedes ganar con Obsidiana. Toma una ficha.");
            Ficha* rob = ctx.baraja->tomarFicha();
            if (rob) c->recibirFicha(rob);
            ctx.rueda->avanzar();
            return;
        }

        Ficha* lanzada = c->lanzarFicha(idx);

        if (lanzada->getCategoria() == CategoriaCarta::LIBRE) {
            TonoCarta elegido = elegirTono(ctx.caraActiva);
            lanzada->asignarTono(elegido);
            ctx.tonoActivo = elegido;
        } else {
            ctx.tonoActivo = lanzada->getTono();
        }

        ctx.baraja->descartarFicha(lanzada);
        lanzada->ejecutarEfecto(ctx);


        if (ctx.pendienteMostrarMano) {
            total = construirLista(ctx.rueda, lista, MAX_C, c, idxActivo);
            resolverMostrarMano(ctx, lista, total, idxActivo);
        }
        if (ctx.pendienteIntercambio) {
            total = construirLista(ctx.rueda, lista, MAX_C, c, idxActivo);
            resolverIntercambio(ctx, lista, total, idxActivo);
        }

        // Verificar campeon
        if (c->sinFichas()) {
            ctx.partidaFin = true;
            ctx.campeon    = c->getAlias();
            return;
        }

        if (!ctx.turnoRepetido)
            ctx.rueda->avanzar();
        else
            ctx.turnoRepetido = false;

    } catch (...) {
        Pantalla::alertaError("Entrada no reconocida.");
    }
}

// Iniciar partida
static void iniciarPartida(ConfigPartida& cfg) {
    Pantalla::limpiar();
    Pantalla::encabezado("NUEVA PARTIDA");

    std::cout << "  Numero de contendientes y/o jugadores (min 2): ";
    int n = pedirEntero(2, 20);

    Contendiente** jugadores = new Contendiente*[n];
    for (int i = 0; i < n; ++i) {
        std::string alias = pedirTexto("  Alias del contendiente y/o jugador"
                                       + std::to_string(i + 1) + ": ");
        jugadores[i] = new Contendiente(alias);
    }

    Baraja* baraja = new Baraja();
    baraja->preparar(n, cfg);

    RuedaTurnos* rueda = new RuedaTurnos();
    for (int i = 0; i < n; ++i) rueda->inscribir(jugadores[i]);

    for (int i = 0; i < n; ++i)
        for (int k = 0; k < 7; ++k)
            jugadores[i]->recibirFicha(baraja->tomarFicha());

    Ficha* primera = baraja->tomarFicha();
    while (primera && primera->getCategoria() == CategoriaCarta::LIBRE) {
        baraja->descartarFicha(primera);
        primera = baraja->tomarFicha();
    }
    if (primera) baraja->descartarFicha(primera);

    ContextoPartida ctx;
    ctx.rueda      = rueda;
    ctx.baraja     = baraja;
    ctx.config     = cfg;
    ctx.tonoActivo = primera ? primera->getTono() : TonoCarta::CARMESI;
    ctx.caraActiva = CaraBaraja::LUMINOSA;

    while (!ctx.partidaFin && rueda->totalJugadores() > 1) {
        ++ctx.numeroTurno;
        ejecutarTurno(ctx);
    }

    if (!ctx.campeon.empty())
        Pantalla::alertaCampeon(ctx.campeon);
    else
        std::cout << Paleta::AMARILLO << "\n  Partida finalizada.\n" << Paleta::RESET;

    Pantalla::esperarEnter();

    rueda->limpiar();
    delete rueda;
    delete baraja;
    for (int i = 0; i < n; ++i) delete jugadores[i];
    delete[] jugadores;
}


static void ajustarConfig(ConfigPartida& cfg) {
    bool volver = false;
    while (!volver) {
        Pantalla::mostrarMenuConfig(cfg);
        int op = pedirEntero(0, 7);
        switch (op) {
            case 1: cfg.apilar        = !cfg.apilar;        break;
            case 2: cfg.retarLibre    = !cfg.retarLibre;    break;
            case 3: cfg.roboIlimitado = !cfg.roboIlimitado; break;
            case 4: cfg.obligarUNO    = !cfg.obligarUNO;    break;
            case 5: cfg.permitirObs   = !cfg.permitirObs;   break;
            case 6: cfg.modoFlip      = !cfg.modoFlip;      break;
            case 7:
                if (cfg.guardarEn("config_arena.txt"))
                    std::cout << Paleta::VERDE
                              << "  Configuracion guardada en config_arena.txt\n"
                              << Paleta::RESET;
                Pantalla::esperarEnter();
                break;
            case 0: volver = true; break;
            default: break;
        }
    }
}

// ── main ──────────────────────────────────────────────────────────────────────
int main() {
    ConfigPartida cfg;
    bool corriendo = true;

    while (corriendo) {
        Pantalla::mostrarMenuPrincipal();
        int op = pedirEntero(0, 4);
        switch (op) {
            case 1: iniciarPartida(cfg);       break;
            case 2: ajustarConfig(cfg);        break;
            case 3: Pantalla::demoFichas();    break;
            case 4:
                if (cfg.cargarDe("config_arena.txt"))
                    std::cout << Paleta::VERDE << "\n  Config cargada.\n" << Paleta::RESET;
                else
                    Pantalla::alertaError("No se encontro config_arena.txt");
                Pantalla::esperarEnter();
                break;
            case 0: corriendo = false; break;
            default: break;
        }
    }

    std::cout << Paleta::CIAN << "\n  Hasta la proxima\n\n" << Paleta::RESET;
    return 0;
}
