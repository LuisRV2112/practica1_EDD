
#include "../../Modelo/Baraja.h"
#include "../../Modelo/FichaNumeral.h"
#include "../../Modelo/FichaPoderosa.h"
#include "../../Modelo/FichaLibre.h"
#include "../../Modelo/FichaVolteo.h"
#include "../../Modelo/FichaEspecial.h"
#include <cstdlib>
#include <ctime>

Baraja::~Baraja() {
    while (!pilaReserva_.estaVacia()) {
        delete pilaReserva_.verTope();
        pilaReserva_.sacar();
    }
    while (!pilaUsadas_.estaVacia()) {
        delete pilaUsadas_.verTope();
        pilaUsadas_.sacar();
    }
}

void Baraja::armarCaraLuminosa() {
    TonoCarta tonos[] = {
        TonoCarta::CARMESI, TonoCarta::ESMERALDA,
        TonoCarta::ZAFIRO,  TonoCarta::DORADO
    };
    for (auto& t : tonos) {
        pilaReserva_.apilar(new FichaNumeral(t, 0, CaraBaraja::LUMINOSA));
        for (int d = 1; d <= 9; ++d) {
            pilaReserva_.apilar(new FichaNumeral(t, d, CaraBaraja::LUMINOSA));
            pilaReserva_.apilar(new FichaNumeral(t, d, CaraBaraja::LUMINOSA));
        }
        for (int k = 0; k < 2; ++k) {
            pilaReserva_.apilar(new FichaPoderosa(t, EfectoCarta::BLOQUEO,  CaraBaraja::LUMINOSA));
            pilaReserva_.apilar(new FichaPoderosa(t, EfectoCarta::GIRO,     CaraBaraja::LUMINOSA));
            pilaReserva_.apilar(new FichaPoderosa(t, EfectoCarta::ROBO_DOS, CaraBaraja::LUMINOSA));
        }
        // Cartas personalizadas
        pilaReserva_.apilar(new FichaMostrarMano(t,       CaraBaraja::LUMINOSA));
        pilaReserva_.apilar(new FichaIntercambiarCarta(t, CaraBaraja::LUMINOSA));
    }
    for (int k = 0; k < 4; ++k) {
        pilaReserva_.apilar(new FichaLibre(false, CaraBaraja::LUMINOSA));
        pilaReserva_.apilar(new FichaLibre(true,  CaraBaraja::LUMINOSA));
    }
}

// Junta las fichas del lado sombrio (UNO Flip) + 2 personalizadas por color
void Baraja::armarCaraSombria() {
    TonoCarta sombrioS[] = {
        TonoCarta::FUCSIA, TonoCarta::AGUAMARINA,
        TonoCarta::CORAL,  TonoCarta::INDIGO
    };
    for (auto& t : sombrioS) {
        pilaReserva_.apilar(new FichaNumeral(t, 0, CaraBaraja::SOMBRIA));
        for (int d = 1; d <= 9; ++d) {
            pilaReserva_.apilar(new FichaNumeral(t, d, CaraBaraja::SOMBRIA));
            pilaReserva_.apilar(new FichaNumeral(t, d, CaraBaraja::SOMBRIA));
        }
        for (int k = 0; k < 2; ++k) {
            pilaReserva_.apilar(new FichaPoderosa(t, EfectoCarta::BLOQUEO_TOTAL, CaraBaraja::SOMBRIA));
            pilaReserva_.apilar(new FichaPoderosa(t, EfectoCarta::GIRO,          CaraBaraja::SOMBRIA));
            pilaReserva_.apilar(new FichaPoderosa(t, EfectoCarta::ROBO_TRES,     CaraBaraja::SOMBRIA));
        }
        pilaReserva_.apilar(new FichaVolteo(t, CaraBaraja::SOMBRIA));
        pilaReserva_.apilar(new FichaVolteo(t, CaraBaraja::SOMBRIA));
        pilaReserva_.apilar(new FichaMostrarMano(t,       CaraBaraja::SOMBRIA));
        pilaReserva_.apilar(new FichaIntercambiarCarta(t, CaraBaraja::SOMBRIA));
    }
    for (int k = 0; k < 4; ++k) {
        pilaReserva_.apilar(new FichaLibre(false, CaraBaraja::SOMBRIA));
        pilaReserva_.apilar(new FichaPoderosa(TonoCarta::OBSIDIANA,
                                              EfectoCarta::ROBO_SEIS,
                                              CaraBaraja::SOMBRIA));
    }
}

void Baraja::preparar(int nContendientes, const ConfigPartida& cfg) {
    int nMazos = (nContendientes - 1) / 6 + 1;
    for (int m = 0; m < nMazos; ++m) {
        armarCaraLuminosa();
        if (cfg.modoFlip) armarCaraSombria();
    }
    mezclar();
}


void Baraja::mezclar() {
    int n = pilaReserva_.totalElementos();
    if (n <= 1) return;
    Ficha** arr = new Ficha*[n];
    pilaReserva_.volcarEnArreglo(arr);
    srand(static_cast<unsigned>(time(nullptr)));
    for (int i = n - 1; i > 0; --i) {
        int j      = rand() % (i + 1);
        Ficha* tmp = arr[i];
        arr[i]     = arr[j];
        arr[j]     = tmp;
    }
    pilaReserva_.cargarDesdeArreglo(arr, n);
    delete[] arr;
}

Ficha* Baraja::tomarFicha() {
    if (pilaReserva_.estaVacia()) reciclarUsadas();
    if (pilaReserva_.estaVacia()) return nullptr;
    Ficha* f = pilaReserva_.verTope();
    pilaReserva_.sacar();
    return f;
}

void Baraja::descartarFicha(Ficha* f) {
    if (f) pilaUsadas_.apilar(f);
}

Ficha* Baraja::fichaEnMesa() const {
    return pilaUsadas_.estaVacia() ? nullptr : pilaUsadas_.verTope();
}

void Baraja::reciclarUsadas() {
    if (pilaUsadas_.estaVacia()) return;
    Ficha* cima = pilaUsadas_.verTope();
    pilaUsadas_.sacar();
    while (!pilaUsadas_.estaVacia()) {
        pilaReserva_.apilar(pilaUsadas_.verTope());
        pilaUsadas_.sacar();
    }
    mezclar();
    pilaUsadas_.apilar(cima);
}
