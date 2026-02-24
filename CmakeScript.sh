#!/bin/bash
# ─────────────────────────────────────────────────────────────────────────────
# CmakeScript.sh – Practica1EDD 2026
# Script de compilacion con CMake
# Laboratorio EDD - USAC CUNOC
# ─────────────────────────────────────────────────────────────────────────────

echo "======================================="
echo "   COMPILADOR - PRACTICA1EDD 2026"
echo "   Laboratorio EDD - USAC CUNOC"
echo "======================================="

[ ! -d "build" ] && mkdir build
[ ! -d "bin"   ] && mkdir bin

echo "Configurando con CMake 4.1..."
cmake -B build -S .
if [ $? -ne 0 ]; then
    echo "ERROR: Fallo la configuracion de CMake."
    exit 1
fi

echo "Compilando..."
cmake --build build
if [ $? -ne 0 ]; then
    echo "ERROR: Fallo la compilacion."
    exit 1
fi

echo ""
echo "======================================="
echo "  Compilacion exitosa!"
echo "======================================="
echo ""
echo "  ./bin/Practica1EDD   -> juego principal"
echo "  ./bin/test_pila      -> pruebas unitarias"
echo ""
