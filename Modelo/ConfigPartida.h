#pragma once
/**
 * @file ConfigPartida.h
 * @brief Flags que controlan las reglas opcionales; serializable a .txt.
 * Practica1EDD - Laboratorio EDD USAC CUNOC 2026
 */
#include <string>
#include <fstream>
#include <iostream>

struct ConfigPartida {
    bool apilar         = false; // acumulacion de +2/+4
    bool retarLibre     = false; // reto al +4
    bool roboIlimitado  = false; // robar hasta poder jugar
    bool obligarUNO     = true;  // gritar UNO al quedar con 1
    bool permitirObs    = false; // ganar con Obsidiana
    bool modoFlip       = false; // activar cara sombria

    void mostrar() const;

    bool guardarEn(const std::string& ruta) const {
        std::ofstream arch(ruta);
        if (!arch) return false;
        arch << "apilar="        << apilar        << "\n"
             << "retarLibre="    << retarLibre    << "\n"
             << "roboIlimitado=" << roboIlimitado << "\n"
             << "obligarUNO="    << obligarUNO    << "\n"
             << "permitirObs="   << permitirObs   << "\n"
             << "modoFlip="      << modoFlip      << "\n";
        return true;
    }

    bool cargarDe(const std::string& ruta) {
        std::ifstream arch(ruta);
        if (!arch) return false;
        std::string linea;
        while (std::getline(arch, linea)) {
            auto sep = linea.find('=');
            if (sep == std::string::npos) continue;
            std::string clave = linea.substr(0, sep);
            int val = std::stoi(linea.substr(sep + 1));
            if      (clave == "apilar")        apilar        = val;
            else if (clave == "retarLibre")    retarLibre    = val;
            else if (clave == "roboIlimitado") roboIlimitado = val;
            else if (clave == "obligarUNO")    obligarUNO    = val;
            else if (clave == "permitirObs")   permitirObs   = val;
            else if (clave == "modoFlip")      modoFlip      = val;
        }
        return true;
    }
};
