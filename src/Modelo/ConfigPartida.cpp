#include "../../Modelo/ConfigPartida.h"
#include "../../Modelo/Paleta.h"
#include <iostream>

void ConfigPartida::mostrar() const {
    auto si_no = [](bool v) -> std::string {
        return v ? (std::string(Paleta::VERDE) + "ACTIVO" + Paleta::RESET)
                 : (std::string(Paleta::ROJO)  + "INACT." + Paleta::RESET);
    };
    std::cout << Paleta::NEGRITA << "  > Configuracion actual:\n" << Paleta::RESET;
    std::cout << "    [1] Apilar robos (+2/+4):       " << si_no(apilar)        << "\n";
    std::cout << "    [2] Reto a ficha libre (+4):    " << si_no(retarLibre)    << "\n";
    std::cout << "    [3] Robo ilimitado (modo B):    " << si_no(roboIlimitado) << "\n";
    std::cout << "    [4] Obligar grito UNO:          " << si_no(obligarUNO)    << "\n";
    std::cout << "    [5] Ganar con Obsidiana:        " << si_no(permitirObs)   << "\n";
    std::cout << "    [6] Modo Flip (cara sombria):   " << si_no(modoFlip)      << "\n";
}
