cmake_minimum_required(VERSION 4.1)


project(Practica1EDD)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/TADs
    ${CMAKE_SOURCE_DIR}/Modelo
)

set(GAME_SOURCES
    src/main.cpp
    src/Modelo/Baraja.cpp
    src/Modelo/ConfigPartida.cpp
    src/Modelo/Contendiente.cpp
    src/Modelo/FichaEspecial.cpp
    src/Modelo/FichaLibre.cpp
    src/Modelo/FichaNumeral.cpp
    src/Modelo/FichaPoderosa.cpp
    src/Modelo/FichaVolteo.cpp
    src/Modelo/Pantalla.cpp
    src/Modelo/RuedaTurnos.cpp
)

add_executable(Practica1EDD ${GAME_SOURCES})

target_include_directories(Practica1EDD PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/TADs
    ${CMAKE_SOURCE_DIR}/Modelo
)

set(TEST_SOURCES
    tests/test_pila.cpp
    src/Modelo/Baraja.cpp
    src/Modelo/ConfigPartida.cpp
    src/Modelo/Contendiente.cpp
    src/Modelo/FichaEspecial.cpp
    src/Modelo/FichaLibre.cpp
    src/Modelo/FichaNumeral.cpp
    src/Modelo/FichaPoderosa.cpp
    src/Modelo/FichaVolteo.cpp
    src/Modelo/Pantalla.cpp
    src/Modelo/RuedaTurnos.cpp
)

add_executable(test_pila ${TEST_SOURCES})

target_include_directories(test_pila PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/TADs
    ${CMAKE_SOURCE_DIR}/Modelo
)
